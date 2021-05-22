#pragma once

#include "Column.hpp"
#include "Query.hpp"

struct CreateTableQuery : public Query {
    const std::string tableName;
    const std::vector<Column> columns;
    const std::string primaryKey;

    CreateTableQuery(std::string tableName, std::vector<Column> columns, std::string primaryKey)
        : Query(QueryType::CreateTable), tableName(tableName), columns(columns),
          primaryKey(primaryKey){};
};
