#pragma once

#include <string>
#include <vector>

#include "ComparisonCondition.hpp"
#include "Literal.hpp"
#include "Query.hpp"

class InsertQuery : Query {
    const std::string tableName;
    const std::vector<Literal> values;

  public:
    InsertQuery(std::string tableName, std::vector<Literal> values)
        : Query(QueryType::Insert), tableName(tableName), values(values){};
};