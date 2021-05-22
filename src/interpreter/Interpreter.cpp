#include "Interpreter.hpp"
#include "QueryParser.hpp"
#include "SQLLexer.h"
#include "SQLParser.h"
#include "Util.hpp"

#include <iostream>
#include <string>

void Interpreter::parse(const std::string &string) {
    std::stringstream stream(string);

    antlr4::ANTLRInputStream input(stream);
    SQLLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    SQLParser parser(&tokens);

    SQLParser::QueryContext *tree = parser.query();
    auto result = QueryParser::parse(tree);

    if (auto selectQuery = Util::dynamic_unique_ptr_cast<SelectQuery>(std::move(result))) {
        std::cout << selectQuery->tableName << std::endl;
    }
}