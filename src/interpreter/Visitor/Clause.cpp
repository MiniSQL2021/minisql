#include "ComparisonCondition.hpp"
#include "SQLCustomVisitor.hpp"

std::vector<ComparisonCondition>
SQLCustomVisitor::parseWhereClause(SQLParser::WhereClauseContext *ctx) {
    return !!ctx ? parseConditionList(ctx->conditionList()) : std::vector<ComparisonCondition>();
}