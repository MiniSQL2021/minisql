#pragma once

#include "Interpreter.hpp"

class API {
public:
    API() : interpreter(Interpreter()) {};

    void listen();

private:
    Interpreter interpreter;
};