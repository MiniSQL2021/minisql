#include "API.hpp"
#include "Adapter.hpp"
#include "API_Util.hpp"

std::vector<int> API::getAllIndexedAttributeIndex(const TableInfo &table) {
    std::vector<int> result;
    for (int i = 0; i < table.attrNum; i++)
        if (table.hasIndex[i]) result.push_back(i);
    return result;
}

void API::dropIndex(TableInfo &table, int attributeIndex) {
    // Assume the index exists
    auto attribute = Adapter::toAttribute(table, attributeIndex);
    auto attributeName = table.attrName[attributeIndex];
    Index index(table.TableName, table, bufferManager);
    index.dropIndex(Adapter::getIndexFilePath(table.TableName, attributeName),
                    Adapter::toDataType(attribute.type));
}

// Check 1) if some attribute name in the condition list doesn't exist
//       2) if type of some value in the condition list doesn't match the actual type
bool API::isConditionListValid(TableInfo &table, const std::vector<ComparisonCondition> &conditions) {
    return std::all_of(conditions.begin(), conditions.end(), [&](auto condition) {
        try {
            int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(condition.columnName));
            if (Adapter::toAttributeType(condition.value.type()) != table.attrType[attributeIndex]) return false;
            return true;
        } catch (const attr_does_not_exist &error) {
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
            !recordManager.checkUnique(table.TableName, attributeIndex,
                                       Adapter::toAttribute(*attributeIter), table))
            return false;
    }
    return true;
}

// MARK: Local helper functions

void intersectWithSet(std::set<int> &set, const std::vector<int> &locations, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        set = std::set<int>(locations.cbegin(), locations.cend());
    } else set = API_Util::intersect(set, locations);
}

void intersectWithSet(std::set<int> &set, int location, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        set = std::set<int>{location};
    } else if (!set.contains(location)) set.clear();
}

void removeFromSet(std::set<int> &set, int location, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        set = std::set<int>{};
    } else set.erase(location);
}

std::vector<int> API::selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions) {
    std::set<int> set;
    bool isFirstCondition = true;

    auto conditionListMap = combineConditions(conditions);

    for (const auto &[name, conditionList]: conditionListMap) {
        if (!conditionList) return {};    // Empty range
        int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(name));

        if (table.hasIndex[attributeIndex]) {

            Index index(table.TableName, table, bufferManager);
            auto filePath = Adapter::getIndexFilePath(table.TableName, name);

            for (const auto &condition : *conditionList) {
                if (auto pointCondition = std::get_if<PointCondition>(&condition)) {
                    int location = index.findIndex(filePath, Adapter::toData(pointCondition->value));

                    if (pointCondition->isEqual()) intersectWithSet(set, location, isFirstCondition);
                    else removeFromSet(set, location, isFirstCondition);
                } else if (auto rangeCondition = std::get_if<RangeCondition>(&condition)) {
                    auto locations = searchWithIndex(index, filePath, *rangeCondition);
                    intersectWithSet(set, locations, isFirstCondition);
                }
                if (set.empty()) return {};
            }

        } else {

            for (const auto &condition : *conditionList) {
                if (auto pointCondition = std::get_if<PointCondition>(&condition)) {
                    std::string operatorString = pointCondition->isEqual() ? "==" : "!=";
                    auto locations = recordManager.conditionSelect(
                            table.TableName, attributeIndex,
                            Adapter::unsafeCStyleString(operatorString),
                            Adapter::toAttribute(pointCondition->value), table);
                    intersectWithSet(set, locations, isFirstCondition);
                } else if (auto rangeCondition = std::get_if<RangeCondition>(&condition)) {
                    auto locations = searchWithRecord(table, attributeIndex, *rangeCondition);
                    intersectWithSet(set, locations, isFirstCondition);
                }
                if (set.empty()) return {};
            }

        }
    }

    return {set.cbegin(), set.cend()};
}

std::vector<int> API::searchWithIndex(Index &index, const std::string &filePath, const RangeCondition &condition) {
    if (condition.lhs.isRegular() && condition.rhs.isRegular()) {
        return index.searchRange(filePath,
                                 Adapter::toData(*condition.lhs.value), Adapter::toData(*condition.rhs.value),
                                 (condition.rhs.isClose() << 1) + condition.lhs.isClose());
    } else if (condition.lhs.isNegativeInfinity() && condition.rhs.isRegular()) {
        return index.searchRange1(filePath,
                                  Adapter::toData(*condition.rhs.value), condition.rhs.isClose());
    } else if (condition.lhs.isRegular() && condition.rhs.isPositiveInfinity()) {
        return index.searchRange2(filePath,
                                  Adapter::toData(*condition.lhs.value), condition.lhs.isClose());
    }
}

std::vector<int> API::searchWithRecord(TableInfo &table, int attributeIndex, const RangeCondition &condition) {
    if (condition.lhs.isRegular() && condition.rhs.isRegular()) {
        auto set = API_Util::intersect(searchLessThanWithRecord(table, attributeIndex, condition.rhs),
                                       searchGreaterThanWithRecord(table, attributeIndex, condition.lhs));
        return {set.cbegin(), set.cend()};
    } else if (condition.lhs.isNegativeInfinity() && condition.rhs.isRegular()) {
        return searchLessThanWithRecord(table, attributeIndex, condition.rhs);
    } else if (condition.lhs.isRegular() && condition.rhs.isPositiveInfinity()) {
        return searchGreaterThanWithRecord(table, attributeIndex, condition.lhs);
    }
}

std::vector<int> API::searchLessThanWithRecord(TableInfo &table, int attributeIndex, const LiteralIntervalBound &rhs) {
    std::string operatorString = rhs.isClose() ? "<=" : "<";
    return recordManager.conditionSelect(table.TableName, attributeIndex, Adapter::unsafeCStyleString(operatorString),
                                         Adapter::toAttribute(*rhs.value), table);
}

std::vector<int>
API::searchGreaterThanWithRecord(TableInfo &table, int attributeIndex, const LiteralIntervalBound &lhs) {
    std::string operatorString = lhs.isClose() ? ">=" : ">";
    return recordManager.conditionSelect(table.TableName, attributeIndex, Adapter::unsafeCStyleString(operatorString),
                                         Adapter::toAttribute(*lhs.value), table);
}

// For testing
void API::directlyInput(const std::string &query) {
    std::stringstream ss(query);
    interpreter.parse(ss);
}
