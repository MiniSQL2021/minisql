#pragma once

#include <sstream>
#include <utility>

#include "antlr4-runtime.h"

struct SyntaxError : public std::exception {
    const size_t line, pos;
    const std::string msg;
    const bool hitEOF;

    SyntaxError(size_t line, size_t pos, antlr4::Token *token, std::string msg) :
            line(line), pos(pos), msg(std::move(msg)), hitEOF(token->getType() == antlr4::Token::EOF) {};

    [[nodiscard]] std::string message() const {
        std::stringstream stream;
        stream << "Syntax error at line " << line << " pos " << pos << ": " << msg;
        return stream.str();
    }
};

class SyntaxErrorListener : public antlr4::BaseErrorListener {
    void
    syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                const std::string &msg, std::exception_ptr e) override {
        throw SyntaxError(line, charPositionInLine, offendingSymbol, msg);
    }
};
