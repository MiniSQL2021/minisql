#pragma once

#include <string>
#include <utility>

#include "Query.hpp"

struct ExecuteFileQuery : public Query {
    const std::string path;

    explicit ExecuteFileQuery(std::string path) : Query(QueryType::ExecuteFile), path(std::move(path)) {};
};