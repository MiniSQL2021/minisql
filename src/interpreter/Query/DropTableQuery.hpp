#pragma once

#include <string>

#include "Query.hpp"

class DropTableQuery : Query {
    const std::string tableName;

  public:
    DropTableQuery(std::string tableName) : Query(QueryType::DropTable), tableName(tableName){};
};