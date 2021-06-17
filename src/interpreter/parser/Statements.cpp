#include "query/Queries.hpp"
#include "parser/QueryParser.hpp"

std::unique_ptr<CreateTableQuery>
QueryParser::parseCreateTableStatement(SQLParser::CreateTableStatementContext *ctx) {
    return std::make_unique<CreateTableQuery>(parseIdentifier(ctx->tableName),
                                              parseColumnElementList(ctx->columnElementList()),
                                              parsePrimaryKeyConstraint(ctx->primaryKeyConstraint()));
}

std::unique_ptr<DropTableQuery> QueryParser::parseDropTableStatement(SQLParser::DropTableStatementContext *ctx) {
    return std::make_unique<DropTableQuery>(parseIdentifier(ctx->tableName));
}

std::unique_ptr<CreateIndexQuery>
QueryParser::parseCreateIndexStatement(SQLParser::CreateIndexStatementContext *ctx) {
    return std::make_unique<CreateIndexQuery>(parseIdentifier(ctx->indexName), parseIdentifier(ctx->tableName),
                                              parseIdentifier(ctx->columnName));
}

std::unique_ptr<DropIndexQuery> QueryParser::parseDropIndexStatement(SQLParser::DropIndexStatementContext *ctx) {
    return std::make_unique<DropIndexQuery>(parseIdentifier(ctx->indexName));
}

std::unique_ptr<SelectQuery> QueryParser::parseSelectStatement(SQLParser::SelectStatementContext *ctx) {
    return std::make_unique<SelectQuery>(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

std::unique_ptr<InsertQuery> QueryParser::parseInsertStatement(SQLParser::InsertStatementContext *ctx) {
    return std::make_unique<InsertQuery>(parseIdentifier(ctx->tableName), parseAttributeList(ctx->attributeList()));
}

std::unique_ptr<DeleteQuery> QueryParser::parseDeleteStatement(SQLParser::DeleteStatementContext *ctx) {
    return std::make_unique<DeleteQuery>(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

std::unique_ptr<ExecuteFileQuery> QueryParser::parseExecuteFileCommand(SQLParser::ExecuteFileCommandContext *ctx) {
    return std::make_unique<ExecuteFileQuery>(parseString(ctx->filePath));
}
