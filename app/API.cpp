#include "API.hpp"
#include "Adapter.h"
#include "Util.h"

// TODO: Exception handling
// TODO: Measure duration of each operations
// TODO: Do performance optimization for each submodule's function invocations

void API::handleCreateTableQuery(QueryPointer<CreateTableQuery> query) {
    TableInfo table = Adapter::toTableInfo(*query);
    if (catalogManager.checkTable(table.TableName)) {
        // Table already exists
    }

    recordManager.createTable(table.TableName, table);
    catalogManager.createTable(table);
}

void API::handleDropTableQuery(QueryPointer<DropTableQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }

    // Delete all indices of attributes in the table
    TableInfo table = catalogManager.getTableInfo(tableName);
    for (const auto &attributeName:getAllIndexedAttributeName(table)) {
        dropIndex(table, Adapter::unsafeCStyleString(attributeName));
    }

    recordManager.deleteTable(tableName);
    catalogManager.dropTable(tableName);
}

void API::handleCreateIndexQuery(QueryPointer<CreateIndexQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    char *attributeName = Adapter::unsafeCStyleString(query->columnName);
    char *indexName = Adapter::unsafeCStyleString(query->indexName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }
    if (!catalogManager.checkAttr(tableName, attributeName)) {
        // Attribute doesn't exist
    }
    if (!catalogManager.checkUnique(tableName, attributeName)) {
        // Attribute is not unique
    }
    // Problem: checkIndex's parameters represent what?
    if (catalogManager.checkIndex(tableName/*, attributeName*/)) {
        // Index already exists
    }
    TableInfo table = catalogManager.getTableInfo(tableName);
    Attribute attribute = Adapter::toAttribute(table, attributeName);
    Index index(query->tableName, attribute);
    index.createIndex(Adapter::getIndexFilePath(query->tableName, query->columnName),
                      Adapter::toDataType(attribute.type));

    catalogManager.createIndex(tableName, attributeName, indexName);
}

void API::handleDropIndexQuery(QueryPointer<DropIndexQuery> query) {
    char *indexName = Adapter::unsafeCStyleString(query->indexName);
    // Problem: Pass name of index to 1) check if exists, 2) delete it
    if (catalogManager.checkIndex(indexName)) {
        // Index doesn't exists
    }
    dropIndex(indexName);
}

void API::handleSelectQuery(QueryPointer<SelectQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }
    TableInfo table = catalogManager.getTableInfo(tableName);
    if (!isConditionListValid(table, query->conditions)) {
        // Some attribute in the input doesn't exist, or the type doesn't match the actual type
    }

    std::vector<Tuple> tuples;
    if (query->conditions.empty()) {
        tuples = recordManager.nonconditionSelect(tableName, table);
    } else {
        auto locations = selectTuples(table, query->conditions);
        // Problem: RecordManager should provide a method to retrieve records by locations
    }
    Util::printTable(tuples, table);
}

void API::handleDeleteQuery(QueryPointer<DeleteQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }
    TableInfo table = catalogManager.getTableInfo(tableName);
    if (!isConditionListValid(table, query->conditions)) {
        // Some attribute in the input doesn't exist, or the type doesn't match the actual type
    }

    if (query->conditions.empty()) {
        // Problem: IndexManager should provide a method to delete all the records
        recordManager.deleteAllrecord(tableName);
    } else {
        auto locations = selectTuples(table, query->conditions);
        // (Retrieve tuples)
        std::vector<Tuple> tuples;

        // Delete all the selected records from all indices in the table
        for (const auto &attributeName: getAllIndexedAttributeName(table)) {
            Index index(query->tableName, Adapter::toAttribute(table, attributeName));
            int attributeIndex = catalogManager.getAttrNo(tableName, Adapter::unsafeCStyleString(attributeName));
            for (const auto &tuple : tuples)
                index.deleteIndexByKey("", Adapter::toData(tuple.attr[attributeIndex]));
        }

        // Problem: RecordManager should provide a method to delete records by locations
    }
}

void API::handleInsertQuery(QueryPointer<InsertQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }

    TableInfo table = *catalogManager.getTableInfo(tableName);
    // Check if valid
    if (query->values.size() != table.attrNum) {
        // The number of attributes doesn't match
    }
    if (!isInsertingValueValid(table, query->values)) {
        // Some attribute in the input doesn't match the actual type, or conflicts in uniqueness
    }

    // Problem: RecordManager should return a location after insertion
    int location;
    recordManager.insertRecord(tableName, Adapter::toTuple(query->values), table);

    // Update indices
    for (auto attributeIter = query->values.cbegin(); attributeIter < query->values.cend(); attributeIter++) {
        int attributeIndex = static_cast<int>(attributeIter - query->values.cbegin());
        if (table.hasIndex[attributeIndex]) {
            Attribute attribute = Adapter::toAttribute(table, attributeIndex);
            Index index(query->tableName, attribute);
            index.insertIndex(Adapter::getIndexFilePath(query->tableName, table.attrName[attributeIndex]),
                              Adapter::toData(*attributeIter), location);
        }
    }
}

void API::listen() {
    interpreter.onCreateTableQuery([this](auto query) { handleCreateTableQuery(std::move(query)); });
    interpreter.onDropTableQuery([this](auto query) { handleDropTableQuery(std::move(query)); });
    interpreter.onCreateIndexQuery([this](auto query) { handleCreateIndexQuery(std::move(query)); });
    interpreter.onDropIndexQuery([this](auto query) { handleDropIndexQuery(std::move(query)); });
    interpreter.onSelectQuery([this](auto query) { handleSelectQuery(std::move(query)); });
    interpreter.onInsertQuery([this](auto query) { handleInsertQuery(std::move(query)); });
    interpreter.onDeleteQuery([this](auto query) { handleDeleteQuery(std::move(query)); });
    interpreter.listen();
}
