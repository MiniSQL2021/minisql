#include "API.hpp"
#include "Adapter.h"

std::vector<std::string> API::getAllIndexedAttributeName(const TableInfo &table) {
    std::vector<std::string> result;
    for (int i = 0; i < table.attrNum; i++)
        if (table.hasIndex[i]) result.emplace_back(table.attrName[i]);
    return result;
}

void API::dropIndex(TableInfo &table, const std::string &attributeName) {
    // Assume the index exists
    Attribute attribute = Adapter::toAttribute(table, attributeName);
    Index index(table.TableName, attribute);
    // Problem: Path? Type?
    index.dropIndex(Adapter::getIndexFilePath(table.TableName, attributeName), Adapter::toDataType(attribute.type));
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

// Check 1) if some attribute name in the condition list doesn't exist
//       2) if type of some value in the condition list doesn't match the actual type
bool API::isConditionListValid(TableInfo &table, const std::vector<ComparisonCondition> &conditions) {
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

// Check 1) if type of some value in the value list doesn't match the actual type
//       2) if some value of unique attribute conflicts with existing values
bool API::isInsertingValueValid(TableInfo &table, const std::vector<Literal> &values) {
    for (auto attributeIter = values.cbegin(); attributeIter < values.cend(); attributeIter++) {
        int attributeIndex = static_cast<int>(attributeIter - values.cbegin());
        if (Adapter::toAttributeType(attributeIter->type()) != table.attrType[attributeIndex])
            return false;
        // Problem: Should pass value of the attribute to verify if it's not unique
        if (table.attrUnique[attributeIndex] &&
            !recordManager.checkUnique(table.TableName, attributeIndex, Tuple(), table))
            return false;
    }
    return true;
}

std::vector<int> API::selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions) {
    std::set<int> locationSet;
    bool firstCondition = true;
    for (const auto &condition: conditions) {
        int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(condition.columnName));
        if (table.hasIndex[attributeIndex]) {
            Index index(table.TableName, Adapter::toAttribute(table, condition.columnName));
            if (condition.binaryOperator == BinaryOpearator::Equal ||
                condition.binaryOperator == BinaryOpearator::NotEqual) {
                int location = index.findIndex(Adapter::getIndexFilePath(table.TableName, condition.columnName),
                                               Adapter::toData(condition.value));
                if (firstCondition) {
                    firstCondition = false;
                    locationSet = {location};
                } else
                    locationSet = intersect(locationSet, {location});
            } else {
                auto[leftValue, rightValue] = Adapter::toDataRange(condition);
                std::vector<int> locations;
                // Problem: Handle equal or not equal
                index.searchRange(Adapter::getIndexFilePath(table.TableName, condition.columnName), leftValue,
                                  rightValue, locations);
                if (firstCondition) {
                    firstCondition = false;
                    locationSet = {locations.cbegin(), locations.cend()};
                } else
                    locationSet = intersect(locationSet, locations);
            }
        } else {
            char *operatorString = Adapter::toOperatorString(condition.binaryOperator);
            Attribute value = Adapter::toAttribute(condition.value);
            auto locations = recordManager.conditionSelect(table.TableName, attributeIndex, operatorString, value,
                                                           table);
            if (firstCondition) {
                firstCondition = false;
                locationSet = {locations.cbegin(), locations.cend()};
            } else
                locationSet = intersect(locationSet, locations);
            delete operatorString;
        }
    }
    return std::vector<int>(locationSet.cbegin(), locationSet.cend());
}

std::set<int> API::intersect(const std::set<int> &destination, const std::vector<int> &source) {
    std::set<int> result;
    std::vector<int> sortedSource = source;
    std::sort(sortedSource.begin(), sortedSource.end());
    std::set_intersection(sortedSource.cbegin(), sortedSource.cend(), destination.cbegin(), destination.cend(),
                          std::inserter(result, result.begin()));
    return result;
}


