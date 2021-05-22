#pragma once

#include <string>

#include "Query.hpp"

struct CreateIndexQuery : public Query {
    const std::string indexName;
    const std::string tableName;
    const std::string columnName;

    CreateIndexQuery(std::string indexName, std::string tableName, std::string columnName)
        : Query(QueryType::CreateIndex), indexName(indexName), tableName(tableName),
          columnName(columnName){};
};