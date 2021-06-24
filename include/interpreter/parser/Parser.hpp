#pragma once

#include <string>

#include "../type/Column.hpp"
#include "../type/ComparisonCondition.hpp"
#include "../query/Queries.hpp"
#include "../query/Query.hpp"
#include "../antlr/SQLParser.h"

struct Parser {
    static std::vector<std::unique_ptr<Query>> parse(SQLParser::FileContext *ctx);

    static std::unique_ptr<Query> parseQuery(SQLParser::QueryContext *ctx);

    static std::unique_ptr<CreateTableQuery> parseCreateTableStatement(SQLParser::CreateTableStatementContext *ctx);

    static std::unique_ptr<DropTableQuery> parseDropTableStatement(SQLParser::DropTableStatementContext *ctx);

    static std::unique_ptr<CreateIndexQuery> parseCreateIndexStatement(SQLParser::CreateIndexStatementContext *ctx);

    static std::unique_ptr<DropIndexQuery> parseDropIndexStatement(SQLParser::DropIndexStatementContext *ctx);

    static std::unique_ptr<SelectQuery> parseSelectStatement(SQLParser::SelectStatementContext *ctx);

    static std::unique_ptr<InsertQuery> parseInsertStatement(SQLParser::InsertStatementContext *ctx);

    static std::unique_ptr<DeleteQuery> parseDeleteStatement(SQLParser::DeleteStatementContext *ctx);

    static std::unique_ptr<ExecuteFileQuery> parseExecuteFileCommand(SQLParser::ExecuteFileCommandContext *ctx);

    // MARK: - Clause
    static std::vector<ComparisonCondition> parseWhereClause(SQLParser::WhereClauseContext *ctx);

    // MARK: - Secondary expression
    static Column parseColumnElement(SQLParser::ColumnElementContext *ctx);

    static std::vector<Column> parseColumnElementList(SQLParser::ColumnElementListContext *ctx);

    static std::string parsePrimaryKeyConstraint(SQLParser::PrimaryKeyConstraintContext *ctx);

    static ComparisonCondition parseCondition(SQLParser::ConditionContext *ctx);

    static std::vector<ComparisonCondition> parseConditionList(SQLParser::ConditionListContext *ctx);

    static std::vector<Literal> parseAttributeList(SQLParser::AttributeListContext *ctx);

    // MARK: - Small Parts
    static std::string parseIdentifier(SQLParser::IdentifierContext *ctx);

    static Literal parseLiteral(SQLParser::LiteralContext *ctx);

    static std::string parseString(SQLParser::StringContext *ctx);

    static BinaryOpearator parseBinaryOperator(SQLParser::BinaryOperatorContext *ctx);
};
