#include "type/Column.hpp"
#include "type/ComparisonCondition.hpp"
#include "parser/Parser.hpp"

Column Parser::parseColumnElement(SQLParser::ColumnElementContext *ctx) {
    std::string columnName = parseIdentifier(ctx->columnName);

    LiteralType type;
    if (ctx->dataType()->charType()) {
        type = LiteralType::String;
        int maxLength = std::stoi(ctx->dataType()->charType()->INT_NUMBER()->getText());
        return Column(columnName, type, maxLength, ctx->unique != nullptr);
    }
    if (ctx->dataType()->intType()) type = LiteralType::Int;
    if (ctx->dataType()->floatType()) type = LiteralType::Float;

    return Column(columnName, type, ctx->unique != nullptr);
}

std::vector<Column> Parser::parseColumnElementList(SQLParser::ColumnElementListContext *ctx) {
    std::vector<Column> result;
    for (auto columnCtx : ctx->elements) result.push_back(parseColumnElement(columnCtx));
    return result;
}

std::string Parser::parsePrimaryKeyConstraint(SQLParser::PrimaryKeyConstraintContext *ctx) {
    return parseIdentifier(ctx->columnName);
}

ComparisonCondition Parser::parseCondition(SQLParser::ConditionContext *ctx) {
    return ComparisonCondition(parseIdentifier(ctx->columnName),
                               parseBinaryOperator(ctx->binaryOperator()),
                               parseLiteral(ctx->literal()));
}

std::vector<ComparisonCondition>
Parser::parseConditionList(SQLParser::ConditionListContext *ctx) {
    std::vector<ComparisonCondition> result;
    for (auto conditionCtx : ctx->conditions) result.push_back(parseCondition(conditionCtx));
    return result;
}

std::vector<Literal> Parser::parseAttributeList(SQLParser::AttributeListContext *ctx) {
    std::vector<Literal> result;
    for (auto literalCtx : ctx->attributes) result.push_back(parseLiteral(literalCtx));
    return result;
}
