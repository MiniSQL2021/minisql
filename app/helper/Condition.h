#pragma once

#include <utility>
#include <map>
#include <vector>
#include <variant>

#include "Interval.h"
#include "PointInterval.h"
#include "Literal.hpp"
#include "ComparisonCondition.hpp"

using LiteralIntervalBound = IntervalBound<Literal>;

using RangeCondition = Interval<Literal>;
using PointCondition = PointInterval<Literal>;

using PointSet = std::set<Literal>;
using RangeConditionList = std::vector<RangeCondition>;

using Condition = std::variant<RangeCondition, PointCondition>;
using ConditionList = std::vector<Condition>;
using ConditionListMap = std::map<std::string, std::optional<ConditionList>>;

RangeCondition toRangeCondition(const ComparisonCondition &condition);

std::optional<ConditionList>
combineRangeAndPoint(const PointSet &equals, const PointSet &notEquals, const RangeConditionList &intervals);

ConditionListMap combineConditions(const std::vector<ComparisonCondition> &conditions);
