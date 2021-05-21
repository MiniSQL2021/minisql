#include "Interpreter.hpp"
#include "SQLLexer.h"
#include "SQLParser.h"
#include "SQLVisitor.h"

#include <iostream>
#include <sstream>
#include <string>

void Interpreter::parse(std::string string) {
    std::stringstream stream(string);

    antlr4::ANTLRInputStream input(stream);
    SQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SQLParser parser(&tokens);

    SQLParser::QueryContext *tree = parser.query();
}