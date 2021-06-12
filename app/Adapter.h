#pragma once

#include <string>

#include "Interpreter.hpp"
#include "RecordManager.h"
#include "CatalogManager.h"
#include "Index.h"

namespace Adapter {
    char *toCStyleString(const std::string &str);

    AttributeType toAttributeType(LiteralType type);

    attrStruct toAttrStruct(const Column &column);

    tableInfo toTableInfo(const CreateTableQuery &query);

    Attribute toAttribute(const Literal &literal);

    Data toData(const Literal &literal);

    std::tuple<Data, Data> toDataRange(const ComparisonCondition &condition);

    char *toOperatorString(BinaryOpearator op);
}