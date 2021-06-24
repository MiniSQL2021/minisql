#include "type/ComparisonCondition.hpp"
#include "parser/Parser.hpp"

std::vector<ComparisonCondition> Parser::parseWhereClause(SQLParser::WhereClauseContext *ctx) {
    return ctx != nullptr ? parseConditionList(ctx->conditionList()) : std::vector<ComparisonCondition>();
}
