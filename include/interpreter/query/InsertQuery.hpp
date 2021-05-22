#pragma once

#include <string>
#include <vector>

#include "ComparisonCondition.hpp"
#include "Literal.hpp"
#include "Query.hpp"

struct InsertQuery : public Query {
    const std::string tableName;
    const std::vector<Literal> values;

    InsertQuery(std::string tableName, std::vector<Literal> values)
        : Query(QueryType::Insert), tableName(tableName), values(values){};
};