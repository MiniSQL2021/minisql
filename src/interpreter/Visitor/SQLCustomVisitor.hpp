#pragma once

#include <string>

#include "Column.hpp"
#include "ComparisonCondition.hpp"
#include "Queries.hpp"
#include "Query.hpp"
#include "SQLBaseVisitor.h"

class SQLCustomVisitor : public SQLBaseVisitor {
  public:
    Query parseQuery(SQLParser::QueryContext *ctx);

    CreateTableQuery parseCreateTableStatement(SQLParser::CreateTableStatementContext *ctx);
    DropTableQuery parseDropTableStatement(SQLParser::DropTableStatementContext *ctx);
    CreateIndexQuery parseCreateIndexStatement(SQLParser::CreateIndexStatementContext *ctx);
    DropIndexQuery parseDropIndexStatement(SQLParser::DropIndexStatementContext *ctx);
    SelectQuery parseSelectStatement(SQLParser::SelectStatementContext *ctx);
    InsertQuery parseInsertStatement(SQLParser::InsertStatementContext *ctx);
    DeleteQuery parseDeleteStatement(SQLParser::DeleteStatementContext *ctx);

    QuitQuery parseQuitCommand(SQLParser::QuitCommandContext *ctx);
    ExecuteFileQuery parseExecuteFileCommand(SQLParser::ExecuteFileCommandContext *ctx);

    // MARK: - Clause
    std::vector<ComparisonCondition> parseWhereClause(SQLParser::WhereClauseContext *ctx);

    // MARK: - Secondary expression
    Column parseColumnElement(SQLParser::ColumnElementContext *ctx);
    std::vector<Column> parseColumnElementList(SQLParser::ColumnElementListContext *ctx);

    std::string parsePrimaryKeyConstraint(SQLParser::PrimaryKeyConstraintContext *ctx);

    ComparisonCondition parseCondition(SQLParser::ConditionContext *ctx);
    std::vector<ComparisonCondition> parseConditionList(SQLParser::ConditionListContext *ctx);

    std::vector<Literal> parseAttributeList(SQLParser::AttributeListContext *ctx);

    // MARK: - Small Parts
    std::string parseIdentifier(SQLParser::IdentifierContext *ctx);

    Literal parseLiteral(SQLParser::LiteralContext *ctx);
    std::string parseString(SQLParser::StringContext *ctx);

    BinaryOpearator parseBinaryOperator(SQLParser::BinaryOperatorContext *ctx);
};