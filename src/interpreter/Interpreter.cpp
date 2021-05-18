#include "Interpreter.hpp"
#include "antlr/SQLLexer.h"
#include "antlr/SQLParser.h"
#include "antlr/SQLVisitor.h"
// #include "antlr4-runtime.h"

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

    std::cout << tree->toStringTree(true) << std::endl;
}