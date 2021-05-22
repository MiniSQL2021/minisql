#pragma once

#include <string>

#include "Query.hpp"

struct DropIndexQuery : public Query {
    const std::string indexName;

    DropIndexQuery(std::string indexName) : Query(QueryType::DropIndex), indexName(indexName){};
};