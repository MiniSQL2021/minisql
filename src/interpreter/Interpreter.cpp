#include <iostream>

#include "Interpreter.hpp"
#include "QueryParser.hpp"
#include "SQLLexer.h"
#include "SQLParser.h"
#include "Util.hpp"
#include "SyntaxErrorListener.hpp"


std::unique_ptr<Query> Interpreter::parse(std::istream &stream) {
    antlr4::ANTLRInputStream input(stream);
    SQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SQLParser parser(&tokens);

    SyntaxErrorListener errorListener;
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);
    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);

    SQLParser::QueryContext *tree = parser.query();
    return QueryParser::parse(tree);
}

std::unique_ptr<Query> Interpreter::parse(const std::string &string) {
    std::stringstream stream(string);
    return parse(stream);
}
