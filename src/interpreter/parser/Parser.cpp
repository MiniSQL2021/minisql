#include <memory>

#include "parser/Parser.hpp"
#include "query/Query.hpp"

std::vector<std::unique_ptr<Query>> Parser::parse(SQLParser::FileContext *ctx) {
    std::vector<std::unique_ptr<Query>> result;
    std::transform(ctx->queries.cbegin(), ctx->queries.cend(), std::back_inserter(result),
                   [&](SQLParser::QueryContext *ctx) {
                       return parseQuery(ctx);
                   });
    return result;
}

std::unique_ptr<Query> Parser::parseQuery(SQLParser::QueryContext *ctx) {
    if (ctx->statement()) {
        if (ctx->statement()->createTableStatement())
            return parseCreateTableStatement(ctx->statement()->createTableStatement());
        if (ctx->statement()->dropTableStatement())
            return parseDropTableStatement(ctx->statement()->dropTableStatement());

        if (ctx->statement()->createIndexStatement())
            return parseCreateIndexStatement(ctx->statement()->createIndexStatement());
        if (ctx->statement()->dropIndexStatement())
            return parseDropIndexStatement(ctx->statement()->dropIndexStatement());

        if (ctx->statement()->selectStatement())
            return parseSelectStatement(ctx->statement()->selectStatement());
        if (ctx->statement()->insertStatement())
            return parseInsertStatement(ctx->statement()->insertStatement());
        if (ctx->statement()->deleteStatement())
            return parseDeleteStatement(ctx->statement()->deleteStatement());
        throw std::logic_error("Unexpected statement");
    } else {
        if (ctx->commands()->quitCommand()) return std::make_unique<QuitQuery>();
        if (ctx->commands()->executeFileCommand())
            return parseExecuteFileCommand(ctx->commands()->executeFileCommand());
        throw std::logic_error("Unexpected command");
    }
}
