#pragma once

#include <string>

#include "Interpreter.hpp"
#include "QueryParser.hpp"
#include "SQLLexer.h"
#include "SQLParser.h"
#include "Util.hpp"

class Interpreter {
    antlr4::ANTLRInputStream input;
    SQLLexer lexer;
    antlr4::CommonTokenStream tokens;
    SQLParser parser;

public:
    explicit Interpreter(std::istream &stream) : input(stream), lexer(&input), tokens(&lexer), parser(&tokens) {};

    void parse();
};