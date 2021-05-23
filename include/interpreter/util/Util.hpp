#pragma once

#include <iostream>

#include "Literal.hpp"
#include "BinaryOperator.hpp"

namespace util {
    template<typename Derived, typename Base, typename Del>
    static std::unique_ptr<Derived, Del>
    dynamic_unique_ptr_cast(std::unique_ptr<Base, Del> &p) {
        if (auto *result = dynamic_cast<Derived *>(p.get())) {
            p.release();
            return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
        }
        return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
    }

    static std::string literalTypeString(const LiteralType &type) {
        switch (type) {
            case LiteralType::Int:
                return "int";
            case LiteralType::Float:
                return "float";
            case LiteralType::String:
                return "string";
        }
    }

    static std::string binaryOperatorString(const BinaryOpearator &binaryOperator) {
        switch (binaryOperator) {
            case BinaryOpearator::Equal:
                return "=";
            case BinaryOpearator::NotEqual:
                return "!=";
            case BinaryOpearator::LessThan:
                return "<";
            case BinaryOpearator::LessThanOrEqual:
                return "≤";
            case BinaryOpearator::GreaterThan:
                return ">";
            case BinaryOpearator::GreaterThanOrEqual:
                return "≥";
        }
    }

    static void printSelectQuery(SelectQuery *query) {
        std::cout << "SELECT from " << query->tableName;
        if (!query->conditions.empty()) std::cout << " WHERE " << std::endl;
        for (const auto &condition: query->conditions)
            std::cout << condition.columnName << util::binaryOperatorString(condition.binaryOperator)
                      << condition.value.toString() << ", ";
        std::cout << std::endl;
    }

    static void printDeleteQuery(DeleteQuery *query) {
        std::cout << "DELETE from " << query->tableName;
        if (!query->conditions.empty()) std::cout << " WHERE " << std::endl;
        for (const auto &condition: query->conditions)
            std::cout << condition.columnName << util::binaryOperatorString(condition.binaryOperator)
                      << condition.value.toString() << ", ";
        std::cout << std::endl;
    }

    static void printInsertQuery(InsertQuery *query) {
        std::cout << "INSERT to " << query->tableName << " VALUES (" << std::endl;
        for (const auto &literal: query->values)
            std::cout << literal.toString() << " ";
        std::cout << ")" << std::endl;
    }

    static void printCreateTableQuery(CreateTableQuery *query) {
        std::cout << "CREATE TABLE " << query->tableName << " (" << std::endl;
        for (const auto &column: query->columns) {
            std::cout << column.name << " " << util::literalTypeString(column.type);
            if (column.maxLength) std::cout << "(" << *column.maxLength << ")";
            std::cout << " unique=" << column.unique
                      << std::endl;
        }
        std::cout << ")" << std::endl;
    }

    static void printDropTableQuery(DropTableQuery *query) {
        std::cout << "DROP TABLE " << query->tableName << std::endl;
    }

    static void printCreateIndexQuery(CreateIndexQuery *query) {
        std::cout << "CREATE INDEX " << query->indexName << " on " << query->tableName << "(" << query->columnName
                  << ")" << std::endl;
    }

    static void printDropIndexQuery(DropIndexQuery *query) {
        std::cout << "DROP INDEX " << query->indexName << std::endl;
    }

    static void printExecuteFileQuery(ExecuteFileQuery *query) {
        std::cout << "EXECUTE FILE " << query->path << std::endl;
    }

    static void printQuitQuery(QuitQuery *query) {
        std::cout << "QUIT" << std::endl;
    }

    static void printQuery(Query *query) {
        switch (query->type) {
            case QueryType::CreateTable:
                printCreateTableQuery(dynamic_cast<CreateTableQuery *>(query));
                break;
            case QueryType::DropTable:
                printDropTableQuery(dynamic_cast<DropTableQuery *>(query));
                break;
            case QueryType::CreateIndex:
                printCreateIndexQuery(dynamic_cast<CreateIndexQuery *>(query));
                break;
            case QueryType::DropIndex:
                printDropIndexQuery(dynamic_cast<DropIndexQuery *>(query));
                break;
            case QueryType::Select:
                printSelectQuery(dynamic_cast<SelectQuery *>(query));
                break;
            case QueryType::Insert:
                printInsertQuery(dynamic_cast<InsertQuery *>(query));
                break;
            case QueryType::Delete:
                printDeleteQuery(dynamic_cast<DeleteQuery *>(query));
                break;
            case QueryType::Quit:
                printQuitQuery(dynamic_cast<QuitQuery *>(query));
                break;
            case QueryType::ExecuteFile:
                printExecuteFileQuery(dynamic_cast<ExecuteFileQuery *>(query));
                break;
        }
    }
}