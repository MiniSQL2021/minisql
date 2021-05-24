#pragma once

#include "Queries.hpp"
#include "Literal.hpp"
#include "BinaryOperator.hpp"

namespace util {
    template<typename Derived, typename Base, typename Del>
    std::unique_ptr<Derived, Del>
    dynamic_unique_ptr_cast(std::unique_ptr<Base, Del> &p);

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