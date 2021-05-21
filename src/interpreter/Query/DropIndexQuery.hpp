#pragma once

#include <string>

#include "Query.hpp"

class DropIndexQuery : Query {
    const std::string indexName;

  public:
    DropIndexQuery(std::string indexName) : Query(QueryType::DropIndex), indexName(indexName){};
};