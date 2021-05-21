#pragma once

#include <string>

#include "Query.hpp"

class DropTableQuery : public Query {
    const std::string tableName;

  public:
    DropTableQuery(std::string tableName) : Query(QueryType::DropTable), tableName(tableName){};
};