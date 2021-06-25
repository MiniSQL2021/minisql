#pragma once

#include <set>

#include "../interpreter/Interpreter.hpp"
#include "../buffer-manager/buffer_manager.h"
#include "../catalog-manager/Catalog_Manager.h"
#include "../record-manager/RecordManager.h"
#include "../index-manager/Index.h"

#include "helper/API_Util.hpp"
#include "helper/Condition.hpp"
#include "helper/Interval.hpp"
#include "helper/PointInterval.hpp"
#include "Adapter.hpp"

class API {
public:
    API(Interpreter &interpreter, CatalogManager &catalogManager,
        RecordManager &recordManager, BufferManager &bufferManager) :
            interpreter(interpreter), catalogManager(catalogManager),
            recordManager(recordManager), bufferManager(bufferManager) { bootstrap(); };

    void bootstrap();

    void listen();

    void registerEvents();

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
    BufferManager &bufferManager;

    static std::vector<int> getAllIndexedAttributeIndex(const TableInfo &table);

    void createIndex(TableInfo &table, Index &index, int attributeIndex, const std::string &indexName);

    void dropIndex(TableInfo &table, int attributeIndex);

    static void checkTableSchema(const CreateTableQuery &query);

    static void checkConditionList(TableInfo &table, std::vector<ComparisonCondition> &conditions);

    bool isValueExists(TableInfo &table, Index &index, int attributeIndex, const Literal &value);

    void checkInsertingValues(TableInfo &table, Index &index, std::vector<Literal> &literals);

    static std::vector<int> searchWithIndex(Index &index, const std::string &filePath, const RangeCondition &condition);

    std::vector<int> searchGreaterThanWithRecord(TableInfo &table, int attributeIndex, const LiteralIntervalBound &lhs);

    std::vector<int> searchLessThanWithRecord(TableInfo &table, int attributeIndex, const LiteralIntervalBound &rhs);

    std::vector<int> searchWithRecord(TableInfo &table, int attributeIndex, const RangeCondition &condition);

    std::vector<int> selectTuples(TableInfo &table, const std::vector<ComparisonCondition> &conditions);

    static void intersectWithSet(std::set<int> &set, const std::vector<int> &locations, bool &isFirstCondition);

    static void intersectWithSet(std::set<int> &set, int location, bool &isFirstCondition);

    static void removeFromSet(std::set<int> &set, int location, bool &isFirstCondition);

    static std::string toString(AttributeType type);
};
