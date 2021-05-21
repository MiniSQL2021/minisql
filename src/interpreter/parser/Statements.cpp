#include "Queries.hpp"
#include "QueryParser.hpp"

CreateTableQuery
QueryParser::parseCreateTableStatement(SQLParser::CreateTableStatementContext *ctx) {
    return CreateTableQuery(parseIdentifier(ctx->tableName),
                            parseColumnElementList(ctx->columnElementList()),
                            parsePrimaryKeyConstraint(ctx->primaryKeyConstraint()));
}

DropTableQuery QueryParser::parseDropTableStatement(SQLParser::DropTableStatementContext *ctx) {
    return DropTableQuery(parseIdentifier(ctx->tableName));
}

CreateIndexQuery
QueryParser::parseCreateIndexStatement(SQLParser::CreateIndexStatementContext *ctx) {
    return CreateIndexQuery(parseIdentifier(ctx->indexName), parseIdentifier(ctx->tableName),
                            parseIdentifier(ctx->columnName));
}

DropIndexQuery QueryParser::parseDropIndexStatement(SQLParser::DropIndexStatementContext *ctx) {
    return DropIndexQuery(parseIdentifier(ctx->indexName));
}

SelectQuery QueryParser::parseSelectStatement(SQLParser::SelectStatementContext *ctx) {
    return SelectQuery(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

InsertQuery QueryParser::parseInsertStatement(SQLParser::InsertStatementContext *ctx) {
    return InsertQuery(parseIdentifier(ctx->tableName), parseAttributeList(ctx->attributeList()));
}

DeleteQuery QueryParser::parseDeleteStatement(SQLParser::DeleteStatementContext *ctx) {
    return DeleteQuery(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

QuitQuery QueryParser::parseQuitCommand(SQLParser::QuitCommandContext *ctx) { return QuitQuery(); }

ExecuteFileQuery QueryParser::parseExecuteFileCommand(SQLParser::ExecuteFileCommandContext *ctx) {
    return ExecuteFileQuery(ctx->filePath()->getText());
}