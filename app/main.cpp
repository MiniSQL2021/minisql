#include "Interpreter.hpp"

#include <iostream>

int main() {
    std::string str;
    while (std::getline(std::cin, str)) {
        Interpreter::parse(str);
    }

    return 0;
}