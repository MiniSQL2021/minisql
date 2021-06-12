#include <iostream>

#include "API.hpp"

void API::listen() {
    interpreter.onCreateTableQuery([](QueryPointer<CreateTableQuery> query) {
        std::cout << query->tableName << std::endl;
    });
    interpreter.listen();
}

attrStruct adaptToAttrStruct(const Column &column) {
    // Warning: Need to copy from std::string to char *
    char *name = new char[column.name.length() + 1];
    strcpy(name, column.name.c_str());

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
    result.attrName = name;
    result.attrType = type;
    result.attrUnique = column.unique;
    if (int maxLength = *column.maxLength) result.attrlength = maxLength;
    result.hasIndex = false;

    return result;
}

tableInfo adaptToTableInfo(const CreateTableQuery &query) {

}

void API::handleCreateTableQuery(QueryPointer<CreateTableQuery> query) {

}
