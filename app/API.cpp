#include <iostream>

#include "API.hpp"
#include "Util.h"

void API::listen() {
    interpreter.onCreateTableQuery([this](auto query) { handleCreateTableQuery(std::move(query)); });
    interpreter.onDropTableQuery([this](auto query) { handleDropTableQuery(std::move(query)); });
    interpreter.onCreateIndexQuery([this](auto query) { handleCreateIndexQuery(std::move(query)); });
    interpreter.onDropIndexQuery([this](auto query) { handleDropIndexQuery(std::move(query)); });
    interpreter.onSelectQuery([this](auto query) { handleSelectQuery(std::move(query)); });
    interpreter.onInsertQuery([this](auto query) { handleInsertQuery(std::move(query)); });
    interpreter.onDeleteQuery([this](auto query) { handleDeleteQuery(std::move(query)); });
    interpreter.listen();
}

attrStruct adaptToAttrStruct(const Column &column) {
    AttributeType type;
    switch (column.type) {
        case LiteralType::Int:
            type = AttributeType::INT;
            break;
        case LiteralType::Float:
            type = AttributeType::FLOAT;
            break;
        case LiteralType::String:
            type = AttributeType::CHAR;
            break;
    }

    attrStruct result{};
    result.attrName = Util::toCStyleString(column.name);    // Warning: Need to copy from std::string to char *
    result.attrType = type;
    result.attrUnique = column.unique;
    if (int maxLength = *column.maxLength) result.attrlength = maxLength;
    result.hasIndex = false;

    return result;
}

tableInfo adaptToTableInfo(const CreateTableQuery &query) {
    tableInfo result;
    auto columnCount = query.columns.size();

    auto *attributes = new attrStruct[columnCount];
    for (int i = 0; i < columnCount; i++) attributes[i] = adaptToAttrStruct(query.columns[i]);

    result.setTableInfo(Util::toCStyleString(query.tableName),
                        Util::toCStyleString(query.primaryKey),
                        true,
                        static_cast<int>(columnCount),
                        attributes);
    return result;
}

void API::handleCreateTableQuery(QueryPointer<CreateTableQuery> query) {
    tableInfo table = adaptToTableInfo(*query);
    catalogManager.createTable(table);
}

void API::handleDropTableQuery(QueryPointer<DropTableQuery> query) {

}

void API::handleCreateIndexQuery(QueryPointer<CreateIndexQuery> query) {

}

void API::handleDropIndexQuery(QueryPointer<DropIndexQuery> query) {

}

void API::handleSelectQuery(QueryPointer<SelectQuery> query) {

}

void API::handleInsertQuery(QueryPointer<InsertQuery> query) {

}

void API::handleDeleteQuery(QueryPointer<DeleteQuery> query) {

}


