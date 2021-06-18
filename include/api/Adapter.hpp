#pragma once

#include <string>

#include "../interpreter/Interpreter.hpp"
#include "../catalog-manager/Catalog_Manager.h"
#include "../record-manager/RecordManager.h"
#include "../index-manager/Index.h"
//#include "../index-manager/IndexMock.h"

namespace Adapter {
    char *unsafeCStyleString(const std::string &str);

    char *dynamicCStyleString(const std::string &str);

    AttributeType toAttributeType(LiteralType type);

    attrStruct toAttrStruct(const Column &column);

    TableInfo toTableInfo(const CreateTableQuery &query);

    Attribute toAttribute(const Literal &literal);

    Attribute toAttribute(TableInfo &table, const std::string &attributeName);

    Attribute toAttribute(TableInfo &table, int attributeIndex);

    Data toData(const Literal &literal);

    Data toData(const Attribute &attribute);

    Tuple toTuple(TableInfo &table, const std::vector<Literal> &literals);

    std::string getIndexFilePath(const std::string &tableName, const std::string &attributeName);

    int toDataType(AttributeType type);
}
