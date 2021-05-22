#include "BinaryOperator.hpp"
#include "Literal.hpp"
#include "QueryParser.hpp"

std::string QueryParser::parseIdentifier(SQLParser::IdentifierContext *ctx) {
    if (ctx->IDENTIFIER()) return ctx->IDENTIFIER()->getText();
    else {
        std::string backtickQuotedString = ctx->BACKTICK_QUOTED_ID()->getText();
        return backtickQuotedString.substr(1, backtickQuotedString.length() - 2);
    }
}

Literal QueryParser::parseLiteral(SQLParser::LiteralContext *ctx) {
    if (ctx->string()) return Literal(parseString(ctx->string()));
    if (ctx->number()->INT_NUMBER())
        return Literal(std::stoi(ctx->number()->INT_NUMBER()->getText()));
    if (ctx->number()->DECIMAL_NUMBER())
        return Literal(std::stof(ctx->number()->DECIMAL_NUMBER()->getText()));
    if (ctx->number()->FLOAT_NUMBER())
        return Literal(std::stof(ctx->number()->FLOAT_NUMBER()->getText()));
    throw std::logic_error("Unexpected Literal");
}

std::string QueryParser::parseString(SQLParser::StringContext *ctx) {
    std::string text = ctx->SINGLE_QUOTED_STRING() ? ctx->SINGLE_QUOTED_STRING()->getText()
                                                   : ctx->DOUBLE_QUOTED_STRING()->getText();
    return text.substr(1, text.length() - 2);
}

BinaryOpearator QueryParser::parseBinaryOperator(SQLParser::BinaryOperatorContext *ctx) {
    if (ctx->EQUAL()) return BinaryOpearator::Equal;
    if (ctx->NOT_EQUAL()) return BinaryOpearator::NotEqual;
    if (ctx->LESS_THAN()) return BinaryOpearator::LessThan;
    if (ctx->GREATER_THAN()) return BinaryOpearator::GreaterThan;
    if (ctx->LESS_THAN_OR_EQUAL()) return BinaryOpearator::LessThanOrEqual;
    if (ctx->GREATER_THAN_OR_EQUAL()) return BinaryOpearator::GreaterThanOrEqual;
    throw std::logic_error("Unexpected BinaryOperator");
}