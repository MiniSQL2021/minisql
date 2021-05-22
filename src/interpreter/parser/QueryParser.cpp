#include "QueryParser.hpp"
#include "Query.hpp"

Query QueryParser::parse(SQLParser::QueryContext *ctx) {
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
        if (ctx->commands()->quitCommand()) return parseQuitCommand(ctx->commands()->quitCommand());
        if (ctx->commands()->executeFileCommand())
            return parseExecuteFileCommand(ctx->commands()->executeFileCommand());
        throw std::logic_error("Unexpected command");
    }
}
