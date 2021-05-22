#pragma once

#include <string>

#include "Query.hpp"

struct ExecuteFileQuery : public Query {
    const std::string path;

    ExecuteFileQuery(std::string path) : Query(QueryType::ExecuteFile), path(path){};
};