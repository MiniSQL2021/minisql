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
