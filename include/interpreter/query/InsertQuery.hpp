#pragma once

#include <string>
#include <utility>
#include <vector>

#include "../type/ComparisonCondition.hpp"
#include "../type/Literal.hpp"
#include "Query.hpp"

struct InsertQuery : public Query {
    const std::string tableName;
    const std::vector<Literal> values;

    InsertQuery(std::string tableName, std::vector<Literal> values) : Query(QueryType::Insert),
                                                                      tableName(std::move(tableName)),
                                                                      values(std::move(values)) {};
};
