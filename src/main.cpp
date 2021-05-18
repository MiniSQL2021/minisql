#include "interpreter/Interpreter.hpp"

#include <iostream>
#include <string>

int main() {
    std::string string;
    std::getline(std::cin, string);

    Interpreter interpreter;
    interpreter.parse(string);

    return 0;
}