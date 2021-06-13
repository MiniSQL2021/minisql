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

    std::vector<std::string> getAllIndexedAttributeName(const std::string &tableName);

    void dropIndex(const std::string &tableName, const std::string &attributeName);

    void dropIndex(const std::string &indexName);

    bool isConditionListValid(const std::string &tableName, const std::vector<ComparisonCondition> &conditions);

    std::vector<int> selectTuples(const std::string &tableName, const std::vector<ComparisonCondition> &conditions);
};
