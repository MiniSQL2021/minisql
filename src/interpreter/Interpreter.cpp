#include "Interpreter.hpp"

void printSelectQuery(SelectQuery *query) {
    std::cout << "SELECT from " << query->tableName << " WHERE " << std::endl;
    for (const auto &condition: query->conditions)
        std::cout << condition.columnName << util::binaryOperatorString(condition.binaryOperator)
                  << condition.value.toString() << " and ";
    std::cout << std::endl;
}

void printDeleteQuery(DeleteQuery *query) {
    std::cout << "DELETE from " << query->tableName << " WHERE " << std::endl;
    for (const auto &condition: query->conditions)
        std::cout << condition.columnName << util::binaryOperatorString(condition.binaryOperator)
                  << condition.value.toString() << " and ";
    std::cout << std::endl;
}

void printInsertQuery(InsertQuery *query) {
    std::cout << "INSERT to " << query->tableName << " VALUES (" << std::endl;
    for (const auto &literal: query->values)
        std::cout << literal.toString() << " ";
    std::cout << ")" << std::endl;
}

void printCreateTableQuery(CreateTableQuery *query) {
    std::cout << "CREATE TABLE " << query->tableName << " (" << std::endl;
    for (const auto &column: query->columns) {
        std::cout << column.name << " " << util::literalTypeString(column.type);
        if (column.maxLength) std::cout << "(" << *column.maxLength << ")";
        std::cout << " unique=" << column.unique
                  << std::endl;
    }
    std::cout << ")" << std::endl;
}

void printDropTableQuery(DropTableQuery *query) {
    std::cout << "DROP TABLE " << query->tableName << std::endl;
}

void printCreateIndexQuery(CreateIndexQuery *query) {
    std::cout << "CREATE INDEX " << query->indexName << " on " << query->tableName << "(" << query->columnName
              << ")" << std::endl;
}

void printDropIndexQuery(DropIndexQuery *query) {
    std::cout << "DROP INDEX " << query->indexName << std::endl;
}

void printExecuteFileQuery(ExecuteFileQuery *query) {
    std::cout << "EXECUTE FILE " << query->path << std::endl;
}

void printQuitQuery(QuitQuery *query) {
    std::cout << "QUIT" << std::endl;
}

void printQuery(Query *query) {
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


void Interpreter::parse() {
    SQLParser::QueryContext *tree = parser.query();
    auto result = QueryParser::parse(tree);
    printQuery(result.get());
}