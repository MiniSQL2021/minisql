#include "API.hpp"
#include "Adapter.h"

std::vector<std::string> API::getAllIndexedAttributeName(const tableInfo &table) {
    std::vector<std::string> result;
    for (int i = 0; i < table.attrNum; i++)
        if (table.hasIndex[i]) result.emplace_back(table.attrName[i]);
    return result;
}

void API::dropIndex(tableInfo &table, const std::string &attributeName) {
    // Assume the index exists
    Index index(table.TableName, Adapter::toAttribute(table, attributeName));
    // Problem: Path? Type?
    index.dropIndex("", 0);
    catalogManager.editIndex(table.TableName, Adapter::unsafeCStyleString(attributeName),
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

bool API::isConditionListValid(tableInfo &table, const std::vector<ComparisonCondition> &conditions) {
    // Check 1) if some attribute name in the condition list doesn't exist
    //       2) if type of some value in the condition list doesn't match the actual type
    return std::all_of(conditions.begin(), conditions.end(), [table](auto condition) {
        try {
            int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(condition.columnName));
            if (Adapter::toAttributeType(condition.value.type()) != table.attrType[attributeIndex])
                return false;
            return true;
        } catch (...) {    // Problem: Exception undefined
            return false;
        }
    });
}

std::vector<int> API::selectTuples(tableInfo &table, const std::vector<ComparisonCondition> &conditions) {
    // Problem: RecordManager::conditionSelect should returns array of locations
    // Problem: IndexManager should returns array of locations
    // Problem: Should get a series of arrays of locations of all the expected tuples,
    //          an then do intersection

    // TODO: Intersection
    std::vector<int> result;
    bool firstCondition = true;
    for (const auto &condition: conditions) {
        int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(condition.columnName));
        if (table.hasIndex[attributeIndex]) {
            Index index(table.TableName, Adapter::toAttribute(table, condition.columnName));
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
            recordManager.conditionSelect(table.TableName, attributeIndex, operatorString, value, table, nullptr);
            //
            delete operatorString;
        }
    }
    return result;
}
