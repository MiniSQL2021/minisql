#pragma once

#include <string>

#include "Query.hpp"

class DropIndexQuery : public Query {
    const std::string indexName;

  public:
    DropIndexQuery(std::string indexName) : Query(QueryType::DropIndex), indexName(indexName){};
};