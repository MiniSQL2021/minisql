#pragma once

#include <string>

#include "Query.hpp"

class ExecuteFileQuery : public Query {
    const std::string path;

  public:
    ExecuteFileQuery(std::string path) : Query(QueryType::ExecuteFile), path(path){};
};