#pragma once

#include "../query/Queries.hpp"
#include "../type/Literal.hpp"
#include "../type/BinaryOperator.hpp"

namespace util {
    std::string literalTypeString(const LiteralType &type);

    std::string binaryOperatorString(const BinaryOpearator &binaryOperator);

    void printSelectQuery(SelectQuery *query);

    void printDeleteQuery(DeleteQuery *query);

    void printInsertQuery(InsertQuery *query);

    void printCreateTableQuery(CreateTableQuery *query);

    void printDropTableQuery(DropTableQuery *query);

    void printCreateIndexQuery(CreateIndexQuery *query);

    void printDropIndexQuery(DropIndexQuery *query);

    void printExecuteFileQuery(ExecuteFileQuery *query);

    void printQuitQuery(QuitQuery *query);

    void printQuery(Query *query);
}
