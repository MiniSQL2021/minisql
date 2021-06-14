#pragma once

#include "Interpreter.hpp"
#include "RecordManager.h"
#include "Catalog_Manager.h"
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

    static std::vector<std::string> getAllIndexedAttributeName(const TableInfo &table);

    void dropIndex(TableInfo &table, const std::string &attributeName);

    void dropIndex(const std::string &indexName);

    static bool isConditionListValid(TableInfo &table, const std::vector<ComparisonCondition> &conditions);

    bool isInsertingValueValid(TableInfo &table, const std::vector<Literal> &literals);

    std::vector<int> selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions);
};
