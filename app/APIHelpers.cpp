#include "API.hpp"
#include "Adapter.h"
#include "Util.h"

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
    index.dropIndex(Adapter::getIndexFilePath(table.TableName, attributeName), Adapter::toDataType(attribute.type));
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
        if (table.attrUnique[attributeIndex] &&
            !recordManager.checkUnique(table.TableName, attributeIndex, Adapter::toAttribute(*attributeIter), table))
            return false;
    }
    return true;
}

void updateLocationSet(std::set<int> &set, int location, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        set = {location};
    } else
        set = Util::intersect(set, {location});
}

void updateLocationSet(std::set<int> &set, const std::vector<int> &locations, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        set = {locations.cbegin(), locations.cend()};
    } else
        set = Util::intersect(set, locations);
}

std::vector<int> API::selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions) {
    std::set<int> locationSet;
    bool isFirstCondition = true;

    for (const auto &condition: conditions) {
        int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(condition.columnName));

        if (table.hasIndex[attributeIndex]) {
            Index index(table.TableName, Adapter::toAttribute(table, condition.columnName));
            if (condition.binaryOperator == BinaryOpearator::Equal ||
                condition.binaryOperator == BinaryOpearator::NotEqual) {
                int location = index.findIndex(Adapter::getIndexFilePath(table.TableName, condition.columnName),
                                               Adapter::toData(condition.value));
                updateLocationSet(locationSet, location, isFirstCondition);
                if (locationSet.empty()) return {};
            } else {
                auto[leftValue, rightValue] = Adapter::toDataRange(condition);
                std::vector<int> locations;
                // Problem: Handle equal or not equal
                index.searchRange(Adapter::getIndexFilePath(table.TableName, condition.columnName), leftValue,
                                  rightValue, locations);
                updateLocationSet(locationSet, locations, isFirstCondition);
                if (locationSet.empty()) return {};
            }
        } else {
            char *operatorString = Adapter::toOperatorString(condition.binaryOperator);
            Attribute value = Adapter::toAttribute(condition.value);
            auto locations = recordManager.conditionSelect(table.TableName, attributeIndex, operatorString, value,
                                                           table);
            delete operatorString;
            updateLocationSet(locationSet, locations, isFirstCondition);
            if (locationSet.empty()) return {};
        }
    }
    return {locationSet.cbegin(), locationSet.cend()};
}
