#pragma once

#include "Queries.hpp"

template<typename T>
using QueryPointer = std::unique_ptr<T, std::default_delete<Query>>;
template<typename T>
using QueryHandler = std::function<void(QueryPointer<T>)>;


class Interpreter {
public:
    void listen();

    void onCreateTableQuery(QueryHandler<CreateTableQuery> handler) { createTableQueryHandler = std::move(handler); }

    void onDropTableQuery(QueryHandler<DropTableQuery> handler) { dropTableQueryHandler = std::move(handler); }

    void onCreateIndexQuery(QueryHandler<CreateIndexQuery> handler) { createIndexQueryHandler = std::move(handler); }

    void onDropIndexQuery(QueryHandler<DropIndexQuery> handler) { dropIndexQueryHandler = std::move(handler); }

    void onSelectQuery(QueryHandler<SelectQuery> handler) { selectQueryHandler = std::move(handler); }

    void onInsertQuery(QueryHandler<InsertQuery> handler) { insertQueryHandler = std::move(handler); }

    void onDeleteQuery(QueryHandler<DeleteQuery> handler) { deleteQueryHandler = std::move(handler); }

private:
    QueryHandler<CreateTableQuery> createTableQueryHandler;
    QueryHandler<DropTableQuery> dropTableQueryHandler;
    QueryHandler<CreateIndexQuery> createIndexQueryHandler;
    QueryHandler<DropIndexQuery> dropIndexQueryHandler;
    QueryHandler<SelectQuery> selectQueryHandler;
    QueryHandler<InsertQuery> insertQueryHandler;
    QueryHandler<DeleteQuery> deleteQueryHandler;

    void parse(std::istream &stream);

    void handleQuery(std::unique_ptr<Query> query);

    void processFile(const std::string &path);
};