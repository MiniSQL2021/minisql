#pragma once

#include <set>

#include "Interpreter.hpp"
#include "buffer_manager.h"
#include "Catalog_Manager.h"
#include "RecordManager.h"
#include "Index.h"
#include "Condition.h"

class API {
public:
    API(Interpreter &interpreter, BufferManager &bufferManager, CatalogManager &catalogManager,
        RecordManager &recordManager) : interpreter(interpreter), catalogManager(catalogManager),
                                        recordManager(recordManager) {};

    void listen();

    void handleCreateTableQuery(QueryPointer<CreateTableQuery> query);

    void handleDropTableQuery(QueryPointer<DropTableQuery> query);

    void handleCreateIndexQuery(QueryPointer<CreateIndexQuery> query);

    void handleDropIndexQuery(QueryPointer<DropIndexQuery> query);

    void handleSelectQuery(QueryPointer<SelectQuery> query);

    void handleInsertQuery(QueryPointer<InsertQuery> query);

    void handleDeleteQuery(QueryPointer<DeleteQuery> query);

private:
    Interpreter &interpreter;
    CatalogManager &catalogManager;
    RecordManager &recordManager;

    static std::vector<std::string> getAllIndexedAttributeName(const TableInfo &table);

    static void dropIndex(TableInfo &table, const std::string &attributeName);

    static bool isConditionListValid(TableInfo &table, const std::vector<ComparisonCondition> &conditions);

    bool isInsertingValueValid(TableInfo &table, const std::vector<Literal> &literals);

    static std::vector<int> searchWithIndex(Index &index, const std::string &filePath, const RangeCondition &condition);

    std::vector<int> searchGreaterThanWithRecord(TableInfo &table, int attributeIndex, const LiteralIntervalBound &lhs);

    std::vector<int> searchLessThanWithRecord(TableInfo &table, int attributeIndex, const LiteralIntervalBound &rhs);

    std::vector<int> searchWithRecord(TableInfo &table, int attributeIndex, const RangeCondition &condition);

    std::vector<int> selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions);
};
