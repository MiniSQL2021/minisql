#include "Interpreter.hpp"

#include <iostream>

int main() {
    Interpreter interpreter(std::cin);
    interpreter.parse();

    return 0;
}