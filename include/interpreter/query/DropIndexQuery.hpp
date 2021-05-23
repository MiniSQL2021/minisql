#pragma once

#include <string>
#include <utility>

#include "Query.hpp"

struct DropIndexQuery : public Query {
    const std::string indexName;

    explicit DropIndexQuery(std::string indexName) : Query(QueryType::DropIndex), indexName(std::move(indexName)) {};
};