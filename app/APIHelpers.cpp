#include "API.hpp"
#include "Adapter.h"

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
