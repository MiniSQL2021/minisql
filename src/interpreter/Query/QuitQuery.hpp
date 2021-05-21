#pragma once

#include "Query.hpp"

class QuitQuery : public Query {
  public:
    QuitQuery() : Query(QueryType::Quit){};
};