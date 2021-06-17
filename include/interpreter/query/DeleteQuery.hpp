#pragma once

#include <string>
#include <utility>
#include <vector>

#include "../type/ComparisonCondition.hpp"
#include "Query.hpp"

struct DeleteQuery : public Query {
    const std::string tableName;
    const std::vector<ComparisonCondition> conditions;

    DeleteQuery(std::string tableName, std::vector<ComparisonCondition> conditions) : Query(QueryType::Delete),
                                                                                      tableName(std::move(tableName)),
                                                                                      conditions(
                                                                                              std::move(conditions)) {};
};
