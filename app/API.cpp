#include <iostream>

#include "API.hpp"
#include "Adapter.h"
#include "Util.h"

// TODO: Exception handling
// TODO: Measure duration of each operations
// TODO: Do performance optimization for each submodule's function invocations

void API::handleCreateTableQuery(QueryPointer<CreateTableQuery> query) {
    tableInfo table = Adapter::toTableInfo(*query);
    // Problem: Handle exception that the table already exists
    // Problem: Why bother pass name of table?
    recordManager.createTable(table.TableName, table);
    catalogManager.createTable(table);

    // Problem: Delete char* strings in tableInfo and attrStruct inside?
}

void API::handleDropTableQuery(QueryPointer<DropTableQuery> query) {
    char *tableName = Adapter::toCStyleString(query->tableName);

    // Problem: Handle exception that the table doesn't exist
    recordManager.deleteTable(tableName);
    catalogManager.dropTable(tableName);
    // Problem: Also need to delete index if exists?

    // Problem: Whose responsibility to delete char* strings?
    delete tableName;
}

void API::handleCreateIndexQuery(QueryPointer<CreateIndexQuery> query) {
    char *tableName = Adapter::toCStyleString(query->tableName);
    char *columnName = Adapter::toCStyleString(query->columnName);
    char *indexName = Adapter::toCStyleString(query->indexName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }
    if (!catalogManager.checkAttr(tableName, columnName)) {
        // Attribute doesn't exist
    }
    if (!catalogManager.checkUnique(tableName, columnName)) {
        // Attribute is not unique
    }
    // Problem: checkIndex's parameters represent what?
    if (catalogManager.checkIndex(tableName/*, columnName*/)) {
        // Index already exists
    }

    // Problem: Index's ctor needs 'Attribute'? Where to get?
    Index index(query->tableName, Attribute());
    // Problem: createIndex needs file path? type?
    index.createIndex("", 0);

    // Problem: Pass name of index to create index to catalog
    catalogManager.editIndex(tableName, columnName, 1); // '1' represents 'to create'

    delete tableName;
    delete columnName;
    delete indexName;
}

void API::handleDropIndexQuery(QueryPointer<DropIndexQuery> query) {
    char *indexName = Adapter::toCStyleString(query->indexName);
    // Problem: Pass name of index to 1) check if exists, 2) delete it
    if (catalogManager.checkIndex(indexName)) {
        // Index doesn't exists
    }

    // Problem: Need to instantiate Index?
    // Index index(*, *);
    // Problem: Pass name of index to dropIndex
    // index.dropIndex(query->indexName);

    // Problem: Pass name of index to delete index from catalog
    catalogManager.editIndex(indexName, nullptr, 0); // '0' represents 'to delete'

    delete indexName;
}

void API::handleSelectQuery(QueryPointer<SelectQuery> query) {
    char *tableName = Adapter::toCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }

    // Check 1) if some attribute name in the condition list doesn't exist
    //       2) if type of some value in the condition list doesn't match the actual type
    bool conditionListIsValid = true;
    for (const auto &condition: query->conditions) {
        char *attributeName = Adapter::toCStyleString(condition.columnName);
        bool columnExists = catalogManager.checkAttr(tableName, attributeName);
        // Problem: Why return a pointer to AttributeType?
        AttributeType actualType = *catalogManager.getAttrType(tableName, attributeName);
        AttributeType inputType = Adapter::toAttributeType(condition.value.type());
        delete attributeName;
        if (!columnExists || inputType != actualType) {
            conditionListIsValid = false;
            break;
        }
    }
    if (!conditionListIsValid) {
        // Some attribute in the input doesn't exist, or the type doesn't match the actual type
    }

    // Problem: Why return pointer to tableInfo?
    tableInfo table = *catalogManager.getTableInfo(tableName);

    if (query->conditions.empty()) {
        std::vector<Tuple> tuples;
        recordManager.nonconditionSelect(tableName, nullptr, table);
        //
        Util::printTable(tuples, table);
        delete tableName;
        return;
    }

    // Problem: RecordManager::conditionSelect, should returns std::vector
    // Problem: RecordManager::conditionSelect, comparison involved with multiple conditions
    // Problem: Index, should returns array of locations
    // Problem: Should get a series of arrays of locations of all the expected tuples,
    //          do intersection, and then get data
    for (const auto &condition: query->conditions) {
        bool hasIndex = catalogManager.checkIndex(tableName/*, columnName*/);
        if (hasIndex) {
            // Problem: Attribute?
            Index index(query->tableName, Attribute());
            if (condition.binaryOperator == BinaryOpearator::Equal ||
                condition.binaryOperator == BinaryOpearator::NotEqual) {
                // Problem: Path?
                int location = index.findIndex("", Adapter::toData(condition.value));
                //
            } else {
                auto[leftValue, rightValue] = Adapter::toDataRange(condition);
                std::vector<int> locations;
                // Problem: Handle equal or not equal
                index.searchRange("", leftValue, rightValue, locations);
                //
            }
        } else {
            recordManager.conditionSelect(tableName,
                                          catalogManager.getAttrNo(tableName,
                                                                   Adapter::toCStyleString(condition.columnName)),
                                          Adapter::toOperatorString(condition.binaryOperator),
                                          Adapter::toAttribute(condition.value),
                                          table,
                                          nullptr);
            //
        }
    }
    //

    delete tableName;
}

void API::handleInsertQuery(QueryPointer<InsertQuery> query) {

}

void API::handleDeleteQuery(QueryPointer<DeleteQuery> query) {

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
