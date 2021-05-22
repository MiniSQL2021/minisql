#pragma once

#include <string>

#include "Query.hpp"

struct DropTableQuery : public Query {
    const std::string tableName;

    DropTableQuery(std::string tableName) : Query(QueryType::DropTable), tableName(tableName){};
};