#pragma once

#include <string>
#include <vector>

#include "ComparisonCondition.hpp"
#include "Query.hpp"

class DeleteQuery : Query {
    const std::string tableName;
    const std::vector<ComparisonCondition> conditions;

  public:
    DeleteQuery(std::string tableName, std::vector<ComparisonCondition> conditions)
        : Query(QueryType::Delete), tableName(tableName), conditions(conditions){};
};