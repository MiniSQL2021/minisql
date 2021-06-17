#include "type/ComparisonCondition.hpp"
#include "parser/QueryParser.hpp"

std::vector<ComparisonCondition> QueryParser::parseWhereClause(SQLParser::WhereClauseContext *ctx) {
    return ctx != nullptr ? parseConditionList(ctx->conditionList()) : std::vector<ComparisonCondition>();
}
