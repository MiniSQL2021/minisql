#pragma once

#include <memory>

#include "Query.hpp"

struct Interpreter {
    static std::unique_ptr<Query> parse(std::istream &stream);

    static std::unique_ptr<Query> parse(const std::string &string);
};