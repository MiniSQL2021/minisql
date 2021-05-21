#pragma once

#include "Column.hpp"
#include "Query.hpp"

class CreateTableQuery : Query {
    const std::string tableName;
    const std::vector<Column> columns;
    const std::string primaryKey;

  public:
    CreateTableQuery(std::string tableName, std::vector<Column> columns, std::string primaryKey)
        : Query(QueryType::CreateTable), tableName(tableName), columns(columns),
          primaryKey(primaryKey){};
};
