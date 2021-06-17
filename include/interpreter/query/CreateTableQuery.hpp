#pragma once

#include "../type/Column.hpp"
#include "Query.hpp"

#include <utility>

struct CreateTableQuery : public Query {
    const std::string tableName;
    const std::vector<Column> columns;
    const std::string primaryKey;

    CreateTableQuery(std::string tableName, std::vector<Column> columns, std::string primaryKey) : Query(
            QueryType::CreateTable), tableName(std::move(tableName)), columns(std::move(columns)), primaryKey(
            std::move(primaryKey)) {};
};
