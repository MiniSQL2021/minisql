#include "Queries.hpp"
#include "SQLCustomVisitor.hpp"

CreateTableQuery
SQLCustomVisitor::parseCreateTableStatement(SQLParser::CreateTableStatementContext *ctx) {
    return CreateTableQuery(parseIdentifier(ctx->tableName),
                            parseColumnElementList(ctx->columnElementList()),
                            parsePrimaryKeyConstraint(ctx->primaryKeyConstraint()));
}

DropTableQuery
SQLCustomVisitor::parseDropTableStatement(SQLParser::DropTableStatementContext *ctx) {
    return DropTableQuery(parseIdentifier(ctx->tableName));
}

CreateIndexQuery
SQLCustomVisitor::parseCreateIndexStatement(SQLParser::CreateIndexStatementContext *ctx) {
    return CreateIndexQuery(parseIdentifier(ctx->indexName), parseIdentifier(ctx->tableName),
                            parseIdentifier(ctx->columnName));
}

DropIndexQuery
SQLCustomVisitor::parseDropIndexStatement(SQLParser::DropIndexStatementContext *ctx) {
    return DropIndexQuery(parseIdentifier(ctx->indexName));
}

SelectQuery SQLCustomVisitor::parseSelectStatement(SQLParser::SelectStatementContext *ctx) {
    return SelectQuery(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

InsertQuery SQLCustomVisitor::parseInsertStatement(SQLParser::InsertStatementContext *ctx) {
    return InsertQuery(parseIdentifier(ctx->tableName), parseAttributeList(ctx->attributeList()));
}

DeleteQuery SQLCustomVisitor::parseDeleteStatement(SQLParser::DeleteStatementContext *ctx) {
    return DeleteQuery(parseIdentifier(ctx->tableName), parseWhereClause(ctx->whereClause()));
}

QuitQuery SQLCustomVisitor::parseQuitCommand(SQLParser::QuitCommandContext *ctx) {
    return QuitQuery();
}

ExecuteFileQuery
SQLCustomVisitor::parseExecuteFileCommand(SQLParser::ExecuteFileCommandContext *ctx) {
    return ExecuteFileQuery(ctx->filePath()->getText());
}