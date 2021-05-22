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

struct Query {
    const QueryType type;

    Query(QueryType type) : type(type){};
    virtual ~Query(){};
};