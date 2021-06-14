#include "API.hpp"

int main() {
    Interpreter interpreter;
    BufferManager bufferManager;
    CatalogManager catalogManager(bufferManager);
    RecordManager recordManager(bufferManager);

    API api(interpreter, bufferManager, catalogManager, recordManager);
    api.listen();
    return 0;
}
