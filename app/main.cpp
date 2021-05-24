#include <iostream>

#include "Interpreter.hpp"
#include "Util.hpp"

int main() {
    Interpreter interpreter;
    interpreter.onCreateTableQuery([](CreateTableQueryPointer query) {
        util::printQuery(query.get());
    });
    interpreter.onDropTableQuery([](DropTableQueryPointer query) {
        util::printQuery(query.get());
    });
    interpreter.onCreateIndexQuery([](CreateIndexQueryPointer query) {
        util::printQuery(query.get());
    });
    interpreter.onDropIndexQuery([](DropIndexQueryPointer query) {
        util::printQuery(query.get());
    });
    interpreter.onSelectQuery([](SelectQueryPointer query) {
        util::printQuery(query.get());
    });
    interpreter.onInsertQuery([](InsertQueryPointer query) {
        util::printQuery(query.get());
    });
    interpreter.onDeleteQuery([](DeleteQueryPointer query) {
        util::printQuery(query.get());
    });

    interpreter.listen();

    return 0;
}