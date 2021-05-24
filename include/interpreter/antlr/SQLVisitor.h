
// Generated from SQL.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"
#include "SQLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SQLParser.
 */
class  SQLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SQLParser.
   */
    virtual antlrcpp::Any visitQuery(SQLParser::QueryContext *context) = 0;

    virtual antlrcpp::Any visitStatement(SQLParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitCommands(SQLParser::CommandsContext *context) = 0;

    virtual antlrcpp::Any visitCreateTableStatement(SQLParser::CreateTableStatementContext *context) = 0;

    virtual antlrcpp::Any visitDropTableStatement(SQLParser::DropTableStatementContext *context) = 0;

    virtual antlrcpp::Any visitCreateIndexStatement(SQLParser::CreateIndexStatementContext *context) = 0;

    virtual antlrcpp::Any visitDropIndexStatement(SQLParser::DropIndexStatementContext *context) = 0;

    virtual antlrcpp::Any visitSelectStatement(SQLParser::SelectStatementContext *context) = 0;

    virtual antlrcpp::Any visitInsertStatement(SQLParser::InsertStatementContext *context) = 0;

    virtual antlrcpp::Any visitDeleteStatement(SQLParser::DeleteStatementContext *context) = 0;

    virtual antlrcpp::Any visitWhereClause(SQLParser::WhereClauseContext *context) = 0;

    virtual antlrcpp::Any visitColumnElement(SQLParser::ColumnElementContext *context) = 0;

    virtual antlrcpp::Any visitColumnElementList(SQLParser::ColumnElementListContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryKeyConstraint(SQLParser::PrimaryKeyConstraintContext *context) = 0;

    virtual antlrcpp::Any visitCondition(SQLParser::ConditionContext *context) = 0;

    virtual antlrcpp::Any visitConditionList(SQLParser::ConditionListContext *context) = 0;

    virtual antlrcpp::Any visitAttributeList(SQLParser::AttributeListContext *context) = 0;

    virtual antlrcpp::Any visitIdentifier(SQLParser::IdentifierContext *context) = 0;

    virtual antlrcpp::Any visitDataType(SQLParser::DataTypeContext *context) = 0;

    virtual antlrcpp::Any visitIntType(SQLParser::IntTypeContext *context) = 0;

    virtual antlrcpp::Any visitFloatType(SQLParser::FloatTypeContext *context) = 0;

    virtual antlrcpp::Any visitCharType(SQLParser::CharTypeContext *context) = 0;

    virtual antlrcpp::Any visitLiteral(SQLParser::LiteralContext *context) = 0;

    virtual antlrcpp::Any visitString(SQLParser::StringContext *context) = 0;

    virtual antlrcpp::Any visitNumber(SQLParser::NumberContext *context) = 0;

    virtual antlrcpp::Any visitBinaryOperator(SQLParser::BinaryOperatorContext *context) = 0;

    virtual antlrcpp::Any visitQuitCommand(SQLParser::QuitCommandContext *context) = 0;

    virtual antlrcpp::Any visitExecuteFileCommand(SQLParser::ExecuteFileCommandContext *context) = 0;


};

