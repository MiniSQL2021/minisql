#include <iostream>

#include "API.hpp"

void API::listen() {
    interpreter.onCreateTableQuery([](QueryPointer<CreateTableQuery> query) {
        std::cout << query->tableName << std::endl;
    });
    interpreter.listen();
}