#pragma once

#include <string>
#include <utility>

#include "Query.hpp"

struct DropTableQuery : public Query {
    const std::string tableName;

    explicit DropTableQuery(std::string tableName) : Query(QueryType::DropTable), tableName(std::move(tableName)){};
};