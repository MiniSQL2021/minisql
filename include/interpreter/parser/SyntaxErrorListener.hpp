#pragma once

#include <sstream>
#include <utility>

#include "antlr4-runtime.h"

class QueryParserSyntaxError : public std::exception {
    std::string message;

public:
    QueryParserSyntaxError(size_t line, size_t position, const std::string &msg) {
        std::stringstream stream;
        stream << "Syntax error at line " << line << ", pos " << position << ": " << msg;
        message = stream.str();
    }

    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }
};

class SyntaxErrorListener : public antlr4::BaseErrorListener {
    void
    syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                const std::string &msg, std::exception_ptr e) override {
        throw QueryParserSyntaxError(line, charPositionInLine, msg);
    }
};
