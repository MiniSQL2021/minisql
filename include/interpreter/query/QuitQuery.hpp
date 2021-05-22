#pragma once

#include "Query.hpp"

struct QuitQuery : public Query {
    QuitQuery() : Query(QueryType::Quit){};
};