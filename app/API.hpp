#pragma once

#include <utility>

#include "Interpreter.hpp"
#include "buffer_manager.h"
#include "Catalog_Manager.h"
#include "RecordManager.h"
#include "Index.h"

class API {
public:
    API(Interpreter interpreter, const BufferManager &bufferManager, const CatalogManager &catalogManager,
        const RecordManager &recordManager) : interpreter(std::move(interpreter)), catalogManager(bufferManager),
                                              recordManager(BufferManager()) {};

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
    CatalogManager catalogManager;
    RecordManager recordManager;

    static std::vector<std::string> getAllIndexedAttributeName(const TableInfo &table);

    void dropIndex(TableInfo &table, const std::string &attributeName);

    void dropIndex(const std::string &indexName);

    static bool isConditionListValid(TableInfo &table, const std::vector<ComparisonCondition> &conditions);

    bool isInsertingValueValid(TableInfo &table, const std::vector<Literal> &literals);

    std::vector<int> selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions);
};
