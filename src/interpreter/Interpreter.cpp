#include <iostream>

#include "Interpreter.hpp"
#include "QueryParser.hpp"
#include "SQLLexer.h"
#include "SQLParser.h"
#include "Util.hpp"
#include "SyntaxErrorListener.hpp"


void Interpreter::parse(const std::string &string) {
    std::stringstream stream(string);

    antlr4::ANTLRInputStream input(stream);
    SQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SQLParser parser(&tokens);

    SyntaxErrorListener errorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    try {
        SQLParser::QueryContext *tree = parser.query();
        auto result = QueryParser::parse(tree);
        util::printQuery(result.get());
    } catch (QueryParserSyntaxError &error) {
        std::cout << error.what() << std::endl;
    } catch (...) {
        std::cout << "Unexpected error" << std::endl;
    }
}
