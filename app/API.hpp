#pragma once

#include "Interpreter.hpp"
#include "RecordManager.h"
#include "CatalogManager.h"
#include "Index.h"

class API {
    Interpreter interpreter;
    RecordManager recordManager;
    CatalogManager catalogManager;

public:
    API() : interpreter(Interpreter()) {};

    void listen();

    void handleCreateTableQuery(QueryPointer<CreateTableQuery> query);
};