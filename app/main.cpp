#include "Interpreter.hpp"

#include <iostream>

int main() {
    std::string str;
    std::getline(std::cin, str);

    Interpreter interpreter;
    interpreter.parse(str);

    return 0;
}