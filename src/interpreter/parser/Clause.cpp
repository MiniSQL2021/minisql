#include "ComparisonCondition.hpp"
#include "QueryParser.hpp"

std::vector<ComparisonCondition> QueryParser::parseWhereClause(SQLParser::WhereClauseContext *ctx) {
    return !!ctx ? parseConditionList(ctx->conditionList()) : std::vector<ComparisonCondition>();
}