#pragma once

#include "Interpreter.hpp"
#include "RecordManager.h"
#include "CatalogManager.h"
#include "Index.h"

class API {
public:
    API() : interpreter(Interpreter()) {};

    void listen();

    void handleCreateTableQuery(QueryPointer<CreateTableQuery> query);

    void handleDropTableQuery(QueryPointer<DropTableQuery> query);

    void handleCreateIndexQuery(QueryPointer<CreateIndexQuery> query);

    void handleDropIndexQuery(QueryPointer<DropIndexQuery> query);

    void handleSelectQuery(QueryPointer<SelectQuery> query);

    void handleInsertQuery(QueryPointer<InsertQuery> query);

    void handleDeleteQuery(QueryPointer<DeleteQuery> query);

private:
    Interpreter interpreter;
    RecordManager recordManager;
    CatalogManager catalogManager;

    static std::vector<std::string> getAllIndexedAttributeName(const tableInfo &table);

    void dropIndex(tableInfo &table, const std::string &attributeName);

    void dropIndex(const std::string &indexName);

    static bool isConditionListValid(tableInfo &table, const std::vector<ComparisonCondition> &conditions);

    std::vector<int> selectTuples(tableInfo &table, const std::vector<ComparisonCondition> &conditions);
};
