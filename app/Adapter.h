#pragma once

#include <string>

#include "Interpreter.hpp"
#include "RecordManager.h"
#include "CatalogManager.h"
#include "Index.h"

namespace Adapter {
    char *unsafeCStyleString(const std::string &str);

    char *dynamicCStyleString(const std::string &str);

    AttributeType toAttributeType(LiteralType type);

    attrStruct toAttrStruct(const Column &column);

    tableInfo toTableInfo(const CreateTableQuery &query);

    Attribute toAttribute(const Literal &literal);

    Attribute toAttribute(tableInfo &table, const std::string &attributeName);

    Attribute toAttribute(tableInfo &table, int attributeIndex);

    Data toData(const Literal &literal);

    Data toData(const Attribute &attribute);

    std::tuple<Data, Data> toDataRange(const ComparisonCondition &condition);

    char *toOperatorString(BinaryOpearator op);

    Tuple toTuple(const std::vector<Literal> &literals);
}
