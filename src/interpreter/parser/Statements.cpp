#include "query/Queries.hpp"
#include "parser/Parser.hpp"

std::unique_ptr<CreateTableQuery>
Parser::parseCreateTableStatement(SQLParser::CreateTableStatementContext *ctx) {
    return std::make_unique<CreateTableQuery>(parseIdentifier(ctx->tableName),
                                              parseColumnElementList(ctx->columnElementList()),
                                              parsePrimaryKeyConstraint(ctx->primaryKeyConstraint()));
}

std::unique_ptr<DropTableQuery> Parser::parseDropTableStatement(SQLParser::DropTableStatementContext *ctx) {
    return std::make_unique<DropTableQuery>(parseIdentifier(ctx->tableName));
}

std::unique_ptr<CreateIndexQuery>
Parser::parseCreateIndexStatement(SQLParser::CreateIndexStatementContext *ctx) {
    return std::make_unique<CreateIndexQuery>(parseIdentifier(ctx->indexName), parseIdentifier(ctx->tableName),
                                              parseIdentifier(ctx->columnName));
}

std::unique_ptr<DropIndexQuery> Parser::parseDropIndexStatement(SQLParser::DropIndexStatementContext *ctx) {
    return std::make_unique<DropIndexQuery>(parseIdentifier(ctx->indexName));
}

std::unique_ptr<SelectQuery> Parser::parseSelectStatement(SQLParser::SelectStatementContext *ctx) {
    return std::make_unique<SelectQuery>(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

std::unique_ptr<InsertQuery> Parser::parseInsertStatement(SQLParser::InsertStatementContext *ctx) {
    return std::make_unique<InsertQuery>(parseIdentifier(ctx->tableName), parseAttributeList(ctx->attributeList()));
}

std::unique_ptr<DeleteQuery> Parser::parseDeleteStatement(SQLParser::DeleteStatementContext *ctx) {
    return std::make_unique<DeleteQuery>(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

std::unique_ptr<ExecuteFileQuery> Parser::parseExecuteFileCommand(SQLParser::ExecuteFileCommandContext *ctx) {
    return std::make_unique<ExecuteFileQuery>(parseString(ctx->filePath));
}
