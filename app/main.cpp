#include "Interpreter.hpp"
#include "Util.hpp"

int main() {
    Interpreter interpreter;

    interpreter.onCreateTableQuery([](QueryPointer<CreateTableQuery> query) {
        util::printQuery(query.get());
    });
    interpreter.onDropTableQuery([](QueryPointer<DropTableQuery> query) {
        util::printQuery(query.get());
    });
    interpreter.onCreateIndexQuery([](QueryPointer<CreateIndexQuery> query) {
        util::printQuery(query.get());
    });
    interpreter.onDropIndexQuery([](QueryPointer<DropIndexQuery> query) {
        util::printQuery(query.get());
    });
    interpreter.onSelectQuery([](QueryPointer<SelectQuery> query) {
        util::printQuery(query.get());
    });
    interpreter.onInsertQuery([](QueryPointer<InsertQuery> query) {
        util::printQuery(query.get());
    });
    interpreter.onDeleteQuery([](QueryPointer<DeleteQuery> query) {
        util::printQuery(query.get());
    });

    interpreter.listen();

    return 0;
}