#include "Column.hpp"
#include "ComparisonCondition.hpp"
#include "QueryParser.hpp"

Column QueryParser::parseColumnElement(SQLParser::ColumnElementContext *ctx) {
    std::string columnName = parseIdentifier(ctx->columnName);

    LiteralType type;
    std::optional<int> maxLength;
    if (ctx->dataType()->intType()) type = LiteralType::Int;
    if (ctx->dataType()->floatType()) type = LiteralType::Float;
    if (ctx->dataType()->charType()) {
        type = LiteralType::String;
        maxLength = std::stoi(ctx->dataType()->charType()->INT_NUMBER()->getText());
    }

    return Column(columnName, type, !!ctx->unique);
}

std::vector<Column> QueryParser::parseColumnElementList(SQLParser::ColumnElementListContext *ctx) {
    std::vector<Column> result;
    for (auto columnCtx : ctx->elements) result.push_back(parseColumnElement(columnCtx));
    return result;
}

std::string QueryParser::parsePrimaryKeyConstraint(SQLParser::PrimaryKeyConstraintContext *ctx) {
    return parseIdentifier(ctx->columnName);
}

ComparisonCondition QueryParser::parseCondition(SQLParser::ConditionContext *ctx) {
    return ComparisonCondition(parseIdentifier(ctx->columnName),
                               parseBinaryOperator(ctx->binaryOperator()),
                               parseLiteral(ctx->literal()));
}

std::vector<ComparisonCondition>
QueryParser::parseConditionList(SQLParser::ConditionListContext *ctx) {
    std::vector<ComparisonCondition> result;
    for (auto conditionCtx : ctx->conditions) result.push_back(parseCondition(conditionCtx));
    return result;
}

std::vector<Literal> QueryParser::parseAttributeList(SQLParser::AttributeListContext *ctx) {
    std::vector<Literal> result;
    for (auto literalCtx : ctx->attributes) result.push_back(parseLiteral(literalCtx));
    return result;
}