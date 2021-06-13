#include <iostream>

#include "API.hpp"
#include "Adapter.h"
#include "Util.h"

// TODO: Exception handling
// TODO: Measure duration of each operations
// TODO: Do performance optimization for each submodule's function invocations

void API::handleCreateTableQuery(QueryPointer<CreateTableQuery> query) {
    tableInfo table = Adapter::toTableInfo(*query);
    if (catalogManager.checkTable(table.TableName)) {
        // Table already exists
    }

    // Problem: Why bother pass name of table?
    recordManager.createTable(table.TableName, table);
    catalogManager.createTable(table);
}

void API::handleDropTableQuery(QueryPointer<DropTableQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }

    // Delete all indices of attributes in the table
    for (const auto &attributeName:getAllIndexedAttributeName(query->tableName)) {
        dropIndex(tableName, Adapter::unsafeCStyleString(attributeName));
    }

    recordManager.deleteTable(tableName);
    catalogManager.dropTable(tableName);
}

void API::handleCreateIndexQuery(QueryPointer<CreateIndexQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    char *columnName = Adapter::unsafeCStyleString(query->columnName);
    char *indexName = Adapter::unsafeCStyleString(query->indexName);
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
    if (!isConditionListValid(tableName, query->conditions)) {
        // Some attribute in the input doesn't exist, or the type doesn't match the actual type
    }

    tableInfo table = *catalogManager.getTableInfo(tableName);

    std::vector<Tuple> tuples;
    if (query->conditions.empty()) {
        // Problem: Should return an array of tuples
        recordManager.nonconditionSelect(tableName, nullptr, table);
    } else {
        auto locations = selectTuples(tableName, query->conditions);
        // Problem: RecordManager should provide a method to retrieve records by locations
    }
    Util::printTable(tuples, table);
}

void API::handleDeleteQuery(QueryPointer<DeleteQuery> query) {
    char *tableName = Adapter::unsafeCStyleString(query->tableName);
    if (!catalogManager.checkTable(tableName)) {
        // Table doesn't exist
    }
    if (!isConditionListValid(tableName, query->conditions)) {
        // Some attribute in the input doesn't exist, or the type doesn't match the actual type
    }

    if (query->conditions.empty()) {
        // Problem: IndexManager should provide a method to delete all the records
        // Problem: RecordManager should provide a method to delete all the records
    } else {
        auto locations = selectTuples(tableName, query->conditions);
        // (Retrieve tuples)
        std::vector<Tuple> tuples;
        // Delete all the selected records from all indices in the table
        tableInfo table = *catalogManager.getTableInfo(tableName);
        for (const auto &attributeName: getAllIndexedAttributeName(query->tableName)) {
            Index index(query->tableName, Adapter::toAttribute(table, attributeName));
            int attributeIndex = catalogManager.getAttrNo(tableName, Adapter::unsafeCStyleString(attributeName));
            for (const auto &tuple : tuples)
                index.deleteIndexByKey("", Adapter::toData(tuple.attr[attributeIndex]));
        }

        // Problem: RecordManager should provide a method to delete records by locations
    }
}

void API::handleInsertQuery(QueryPointer<InsertQuery> query) {

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

std::vector<std::string> API::getAllIndexedAttributeName(const std::string &tableName) {
    tableInfo table = *catalogManager.getTableInfo(Adapter::unsafeCStyleString(tableName));
    std::vector<std::string> result;
    for (int i = 0; i < table.attrNum; i++)
        if (table.hasIndex[i]) result.emplace_back(table.attrName[i]);
    return result;
}

void API::dropIndex(const std::string &tableName, const std::string &attributeName) {
    // Assume the index exists
    tableInfo table = *catalogManager.getTableInfo(Adapter::unsafeCStyleString(tableName));
    Index index(tableName, Adapter::toAttribute(table, attributeName));
    // Problem: Path? Type?
    index.dropIndex("", 0);
    catalogManager.editIndex(Adapter::unsafeCStyleString(tableName), Adapter::unsafeCStyleString(attributeName),
                             0);  // '0' represents 'to delete'
}

void API::dropIndex(const std::string &indexName) {
    // Assume the index exists
    // Problem: Should get names of table and attribute
    std::string tableName;
    std::string attributeName;
    // Problem: CatalogManager should provide a method to get name of table and attribute by name of index
    Index index(tableName, Attribute());
    // Problem: Path? Type?
    index.dropIndex("", 0);
    catalogManager.editIndex(Adapter::unsafeCStyleString(tableName), Adapter::unsafeCStyleString(attributeName),
                             0);  // '0' represents 'to delete'
}

bool API::isConditionListValid(const std::string &tableName, const std::vector<ComparisonCondition> &conditions) {
    // Check 1) if some attribute name in the condition list doesn't exist
    //       2) if type of some value in the condition list doesn't match the actual type
    char *tableNameString = Adapter::unsafeCStyleString(tableName);
    return std::all_of(conditions.begin(), conditions.end(), [this, tableNameString](auto condition) {
        char *attributeNameString = Adapter::unsafeCStyleString(condition.columnName);
        bool columnExists = catalogManager.checkAttr(tableNameString, attributeNameString);
        // Problem: Why return a pointer to AttributeType?
        AttributeType actualType = *catalogManager.getAttrType(tableNameString, attributeNameString);
        AttributeType inputType = Adapter::toAttributeType(condition.value.type());
        if (!columnExists || inputType != actualType) return false;
    });
}

std::vector<int> API::selectTuples(const std::string &tableName, const std::vector<ComparisonCondition> &conditions) {
    // Problem: RecordManager::conditionSelect should returns array of locations
    // Problem: IndexManager should returns array of locations
    // Problem: Should get a series of arrays of locations of all the expected tuples,
    //          an then do intersection
    char *tableNameString = Adapter::unsafeCStyleString(tableName);
    tableInfo table = *catalogManager.getTableInfo(Adapter::unsafeCStyleString(tableName));

    std::vector<int> result;
    bool firstCondition = true;
    for (const auto &condition: conditions) {
        char *attributeNameString = Adapter::unsafeCStyleString(condition.columnName);
        if (catalogManager.checkIndex(tableNameString/*, attributeNameString*/)) {
            Index index(tableName, Adapter::toAttribute(table, condition.columnName));
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
            char *operatorString = Adapter::toOperatorString(condition.binaryOperator);
            Attribute value = Adapter::toAttribute(condition.value);
            recordManager.conditionSelect(tableNameString,
                                          catalogManager.getAttrNo(tableNameString, attributeNameString),
                                          operatorString, value, table, nullptr);
            //
            delete operatorString;
        }
    }
    return result;
}
