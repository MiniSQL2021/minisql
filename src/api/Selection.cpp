#include "API.hpp"

std::vector<int> API::selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions) {
    std::set<int> set;
    bool isFirstCondition = true;

    auto conditionListMap = combineConditions(conditions);
    Index index(table.TableName, table, bufferManager);
    for (const auto &[name, conditionList]: conditionListMap) {
        if (!conditionList) return {};    // Empty range
        int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(name));

        if (table.hasIndex[attributeIndex]) {

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
    } else return {};    // Assume unreachable
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
    } else return {};    // Assume unreachable
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

void API::intersectWithSet(std::set<int> &set, const std::vector<int> &locations, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        set = std::set<int>(locations.cbegin(), locations.cend());
    } else set = API_Util::intersect(set, locations);
}

void API::intersectWithSet(std::set<int> &set, int location, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        if (location != -1) set = std::set<int>{location};
    } else if (set.find(location) == set.end())
        set.clear();
}

void API::removeFromSet(std::set<int> &set, int location, bool &isFirstCondition) {
    if (isFirstCondition) {
        isFirstCondition = false;
        set = std::set<int>{};
    } else set.erase(location);
}
