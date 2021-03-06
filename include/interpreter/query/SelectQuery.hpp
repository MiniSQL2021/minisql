#pragma once

#include <string>
#include <utility>
#include <vector>

#include "../type/ComparisonCondition.hpp"
#include "Query.hpp"

struct SelectQuery : public Query {
    const std::string tableName;
    std::vector<ComparisonCondition> conditions;

    SelectQuery(std::string tableName, std::vector<ComparisonCondition> conditions) : Query(QueryType::Select),
                                                                                      tableName(std::move(tableName)),
                                                                                      conditions(
                                                                                              std::move(conditions)) {};
};
