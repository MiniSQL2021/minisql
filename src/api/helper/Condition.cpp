#include <set>
#include <iostream>

#include "Condition.hpp"

RangeCondition toRangeCondition(const ComparisonCondition &condition) {
    switch (condition.binaryOperator) {
        case BinaryOpearator::LessThan:
            return RangeCondition(LiteralIntervalBound::negativeInfinity(),
                                  LiteralIntervalBound(condition.value, BoundType::Open));
        case BinaryOpearator::GreaterThan:
            return RangeCondition(LiteralIntervalBound(condition.value, BoundType::Open),
                                  LiteralIntervalBound::positiveInfinity());
        case BinaryOpearator::LessThanOrEqual:
            return RangeCondition(LiteralIntervalBound::negativeInfinity(),
                                  LiteralIntervalBound(condition.value, BoundType::Close));
        case BinaryOpearator::GreaterThanOrEqual:
            return RangeCondition(LiteralIntervalBound(condition.value, BoundType::Close),
                                  LiteralIntervalBound::positiveInfinity());
        default:
            // Assume unreachable
            return RangeCondition(LiteralIntervalBound::negativeInfinity(), LiteralIntervalBound::positiveInfinity());
    }
}

std::optional<ConditionList>
combineRangeAndPoint(const PointSet &equals, const PointSet &notEquals, const RangeConditionList &intervals) {
    // Ensure 1) equals don't conflict with each other
    //        2) and equals don't conflict with any notEqual
    if (equals.size() > 1 ||
        (equals.size() == 1 && notEquals.find(*equals.begin()) != notEquals.end()))
        return std::nullopt;
    if (intervals.empty()) {
        if (equals.size() == 1)
            return ConditionList{PointCondition::equal(*equals.begin())};    // notEquals take no effect
        else {
            ConditionList result;
            for (const auto &value : notEquals) result.push_back(PointCondition::notEqual(value));
            return result;
        }
    } else {
        if (auto range = RangeCondition::intersect(intervals)) {
            if (!equals.empty() && !range->contains(*equals.begin()))
                return std::nullopt;    // equal is out of the range
            else {
                ConditionList result;
                if (auto singleValue = range->toSingleValue()) {
                    // Interval only contains one single value
                    if (notEquals.find(*singleValue) != notEquals.end()) return std::nullopt;
                    else return ConditionList{PointCondition::equal(*singleValue)};
                } else result.push_back(*range);
                for (const auto &value : notEquals)
                    if (range->contains(value))    // Only when notEqual falls in the range will it take effect
                        result.push_back(PointCondition::notEqual(value));
                return result;
            }
        } else return std::nullopt;
    }
}

ConditionListMap combineConditions(const std::vector<ComparisonCondition> &conditions) {
    // Collect all column names and init maps
    std::set<std::string> columnNames;
    std::map<std::string, RangeConditionList> intervals;
    std::map<std::string, PointSet> equals;
    std::map<std::string, PointSet> notEquals;
    for (const auto &condition : conditions) columnNames.insert(condition.columnName);
    for (const auto &name: columnNames) {
        intervals.insert({name, {}});
        equals.insert({name, {}});
        notEquals.insert({name, {}});
    }

    // Group conditions by column name
    for (const auto &condition : conditions) {
        if (condition.binaryOperator == BinaryOpearator::Equal)
            equals[condition.columnName].insert(condition.value);
        else if (condition.binaryOperator == BinaryOpearator::NotEqual)
            notEquals[condition.columnName].insert(condition.value);
        else
            intervals[condition.columnName].push_back(toRangeCondition(condition));
    }

    ConditionListMap result;
    for (const auto &name : columnNames)
        result[name] = combineRangeAndPoint(equals[name], notEquals[name], intervals[name]);
    return result;
}
