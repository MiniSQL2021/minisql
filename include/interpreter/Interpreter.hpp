#pragma once

#include "Queries.hpp"

template<typename T>
using QueryPointer = std::unique_ptr<T, std::default_delete<Query>>;

template<typename T>
using QueryHandler = std::function<void(QueryPointer<T>)>;

using CreateTableQueryPointer = QueryPointer<CreateTableQuery>;
using DropTableQueryPointer = QueryPointer<DropTableQuery>;
using CreateIndexQueryPointer = QueryPointer<CreateIndexQuery>;
using DropIndexQueryPointer = QueryPointer<DropIndexQuery>;
using SelectQueryPointer = QueryPointer<SelectQuery>;
using InsertQueryPointer = QueryPointer<InsertQuery>;
using DeleteQueryPointer = QueryPointer<DeleteQuery>;

using CreateTableQueryHandler = QueryHandler<CreateTableQuery>;
using DropTableQueryHandler = QueryHandler<DropTableQuery>;
using CreateIndexQueryHandler = QueryHandler<CreateIndexQuery>;
using DropIndexQueryHandler = QueryHandler<DropIndexQuery>;
using SelectQueryHandler = QueryHandler<SelectQuery>;
using InsertQueryHandler = QueryHandler<InsertQuery>;
using DeleteQueryHandler = QueryHandler<DeleteQuery>;

class Interpreter {
public:
    void listen();

    void onCreateTableQuery(CreateTableQueryHandler handler) { createTableQueryHandler = std::move(handler); }

    void onDropTableQuery(DropTableQueryHandler handler) { dropTableQueryHandler = std::move(handler); }

    void onCreateIndexQuery(CreateIndexQueryHandler handler) { createIndexQueryHandler = std::move(handler); }

    void onDropIndexQuery(DropIndexQueryHandler handler) { dropIndexQueryHandler = std::move(handler); }

    void onSelectQuery(SelectQueryHandler handler) { selectQueryHandler = std::move(handler); }

    void onInsertQuery(InsertQueryHandler handler) { insertQueryHandler = std::move(handler); }

    void onDeleteQuery(DeleteQueryHandler handler) { deleteQueryHandler = std::move(handler); }

private:
    CreateTableQueryHandler createTableQueryHandler;
    DropTableQueryHandler dropTableQueryHandler;
    CreateIndexQueryHandler createIndexQueryHandler;
    DropIndexQueryHandler dropIndexQueryHandler;
    SelectQueryHandler selectQueryHandler;
    InsertQueryHandler insertQueryHandler;
    DeleteQueryHandler deleteQueryHandler;

    static std::unique_ptr<Query> parse(std::istream &stream);

    static std::unique_ptr<Query> parse(const std::string &string);

    void handleQuery(std::unique_ptr<Query> query);

    void processFile(const std::string &path);
};