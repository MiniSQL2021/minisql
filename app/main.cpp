#include <iostream>

#include "Interpreter.hpp"
#include "SyntaxErrorListener.hpp"
#include "Util.hpp"

int main() {
    std::string line, buffer;

    while (std::getline(std::cin, line)) {
        try {
            buffer += ' ';
            buffer.append(line);
            buffer += ' ';
            auto query = Interpreter::parse(buffer);
            util::printQuery(query.get());
            buffer.clear();
        } catch (const SyntaxError &error) {
            if (!error.hitEOF) {
                std::cout << error.message() << std::endl;
                buffer.clear();
            }
        }
    }

    return 0;
}