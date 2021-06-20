#include "API.hpp"
#include "Adapter.hpp"
#include "API_Util.hpp"

void API::handleCreateTableQuery(QueryPointer<CreateTableQuery> query) {
    auto table = Adapter::toTableInfo(*query);
    if (catalogManager.checkTable(table.TableName)) {
        API_Util::printError("Table already exists");
        return;
    }

    recordManager.createTable(table.TableName, table);
    catalogManager.createTable(table);
}

void API::handleDropTableQuery(QueryPointer<DropTableQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        API_Util::printError("Table doesn't exist");
        return;
    }

    // Delete all indices of attributes in the table
    auto table = catalogManager.getTableInfo(tableName);
    for (const auto &attributeIndex:getAllIndexedAttributeIndex(table)) {
        dropIndex(table, attributeIndex);
    }

    recordManager.deleteTable(tableName);
    catalogManager.dropTable(tableName);
}

void API::handleCreateIndexQuery(QueryPointer<CreateIndexQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    char *attributeName = Adapter::unsafeCStyleString(query->columnName);
    char *indexName = Adapter::unsafeCStyleString(query->indexName);
    if (!catalogManager.checkTable(tableName)) {
        API_Util::printError("Table doesn't exist");
        return;
    }
    if (!catalogManager.checkAttr(tableName, attributeName)) {
        API_Util::printError("Attribute doesn't exist");
        return;
    }
    if (!catalogManager.checkUnique(tableName, attributeName)) {
        API_Util::printError("Attribute is not unique");
        return;
    }
    if (catalogManager.checkIndex(tableName, attributeName)) {
        API_Util::printError("Index already exists");
        return;
    }
    auto table = catalogManager.getTableInfo(tableName);
    auto attributeIndex = table.searchAttr(attributeName);
    auto attribute = Adapter::toAttribute(table, attributeIndex);

    Index index(query->tableName, table, bufferManager);
    index.createIndexWithDatas(Adapter::getIndexFilePath(query->tableName, query->columnName),
                               Adapter::toDataType(attribute.type), attributeIndex,
                               recordManager.nonConditionSelect(tableName, table));

    catalogManager.createIndex(tableName, attributeName, indexName);
}

void API::handleDropIndexQuery(QueryPointer<DropIndexQuery> query) {
    try {
        char *indexName = Adapter::unsafeCStyleString(query->indexName);
        auto[tableName, attributeName] = catalogManager.searchIndex(indexName);

        auto table = catalogManager.getTableInfo(tableName);
        auto attribute = Adapter::toAttribute(table, attributeName);
        Index index(tableName, table, bufferManager);
        index.dropIndex(Adapter::getIndexFilePath(tableName, attributeName),
                        Adapter::toDataType(attribute.type));

        catalogManager.deleteIndex(indexName);
    } catch (const index_does_not_exist &error) {
        API_Util::printError("Index doesn't exists");
    }
}

void API::handleSelectQuery(QueryPointer<SelectQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        API_Util::printError("Table doesn't exist");
        return;
    }
    auto table = catalogManager.getTableInfo(tableName);
    if (!isConditionListValid(table, query->conditions)) {
        API_Util::printError("Some attribute in the input doesn't exist, or the type doesn't match the actual type");
        return;
    }

    std::vector<Tuple> tuples;
    if (query->conditions.empty())
        tuples = recordManager.nonConditionSelect(tableName, table);
    else {
        auto locations = selectTuples(table, query->conditions);
        tuples = recordManager.searchTuple(tableName, table, locations);
    }
    // TODO: Skip deleted tuples
    API_Util::printTable(tuples, table);
}

void API::handleDeleteQuery(QueryPointer<DeleteQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        API_Util::printError("Table doesn't exist");
        return;
    }
    auto table = catalogManager.getTableInfo(tableName);
    if (!isConditionListValid(table, query->conditions)) {
        API_Util::printError("Some attribute in the input doesn't exist, or the type doesn't match the actual type");
        return;
    }

    if (query->conditions.empty()) {
        // Delete all the records from all the indices in the table
        for (const auto &attributeIndex: getAllIndexedAttributeIndex(table)) {
            auto attribute = Adapter::toAttribute(table, attributeIndex);
            auto attributeName = table.attrName[attributeIndex];
            Index index(query->tableName, table, bufferManager);
            index.clearIndex(Adapter::getIndexFilePath(query->tableName, attributeName),
                             Adapter::toDataType(attribute.type));
        }

        recordManager.deleteAllRecord(tableName, table);
    } else {
        auto locations = selectTuples(table, query->conditions);
        auto tuples = recordManager.searchTuple(tableName, table, locations);

        // Delete all the selected records from all the indices in the table
        for (const auto &attributeIndex: getAllIndexedAttributeIndex(table)) {
            auto attributeName = table.attrName[attributeIndex];
            Index index(query->tableName, table, bufferManager);
            for (const auto &tuple : tuples)
                index.deleteIndexByKey(Adapter::getIndexFilePath(query->tableName, attributeName),
                                       Adapter::toData(tuple.attr[attributeIndex]));
        }

        recordManager.deleteRecord(tableName, locations, table);
    }
}

void API::handleInsertQuery(QueryPointer<InsertQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        API_Util::printError("Table doesn't exist");
        return;
    }
    auto table = catalogManager.getTableInfo(tableName);
    // Check if valid
    if (query->values.size() != table.attrNum) {
        API_Util::printError("The number of attributes doesn't match");
        return;
    }
    if (!isInsertingValueValid(table, query->values)) {
        API_Util::printError("Some attribute in the input doesn't match the actual type, or conflicts in uniqueness");
        return;
    }

    int location = recordManager.insertRecord(tableName, Adapter::toTuple(table, query->values), table);

    // Update indices
    for (int attributeIndex = 0; attributeIndex < table.attrNum; attributeIndex++) {
        if (table.hasIndex[attributeIndex]) {
            auto attribute = Adapter::toAttribute(table, attributeIndex);
            Index index(query->tableName, table, bufferManager);
            index.insertIndex(Adapter::getIndexFilePath(query->tableName, table.attrName[attributeIndex]),
                              Adapter::toData(query->values[attributeIndex]), location);
        }
    }
}

// For convenience to testing
void API::registerEvents() {
    interpreter.onCreateTableQuery([this](auto query) { handleCreateTableQuery(std::move(query)); });
    interpreter.onDropTableQuery([this](auto query) { handleDropTableQuery(std::move(query)); });
    interpreter.onCreateIndexQuery([this](auto query) { handleCreateIndexQuery(std::move(query)); });
    interpreter.onDropIndexQuery([this](auto query) { handleDropIndexQuery(std::move(query)); });
    interpreter.onSelectQuery([this](auto query) { handleSelectQuery(std::move(query)); });
    interpreter.onInsertQuery([this](auto query) { handleInsertQuery(std::move(query)); });
    interpreter.onDeleteQuery([this](auto query) { handleDeleteQuery(std::move(query)); });
}

// Register events and listen on stdin
void API::listen() {
    registerEvents();
    interpreter.listen();
}
