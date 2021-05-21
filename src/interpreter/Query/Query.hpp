#pragma once

enum class QueryType {
    CreateTable,
    DropTable,
    CreateIndex,
    DropIndex,
    Select,
    Insert,
    Delete,
    Quit,
    ExecuteFile
};

class Query {
    const QueryType type;

  public:
    Query(QueryType type) : type(type){};
    virtual ~Query(){};
};