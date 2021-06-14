#include "Adapter.h"
#include "Util.h"

// Warning: Erasing type-safety guard of const-ness
// Need to guarantee that the string is not deallocated when using
char *Adapter::unsafeCStyleString(const string &str) {
    return const_cast<char *>(str.c_str());
}

// Need to be deallocated after used
char *Adapter::dynamicCStyleString(const std::string &str) {
    char *result = new char[str.size() + 1];
    strcpy(result, str.c_str());
    return result;
}

AttributeType Adapter::toAttributeType(LiteralType type) {
    switch (type) {
        case LiteralType::Int:
            return AttributeType::INT;
        case LiteralType::Float:
            return AttributeType::FLOAT;
        case LiteralType::String:
            return AttributeType::CHAR;
    }
}

attrStruct Adapter::toAttrStruct(const Column &column) {
    attrStruct result{};
    result.attrName = dynamicCStyleString(column.name);
    result.attrType = toAttributeType(column.type);
    result.attrUnique = column.unique;
    if (auto maxLength = column.maxLength) result.attrlength = *maxLength;
    result.hasIndex = false;

    return result;
}

TableInfo Adapter::toTableInfo(const CreateTableQuery &query) {
    TableInfo result;
    std::vector<attrStruct> attributes;
    for (const auto &column : query.columns) attributes.push_back(toAttrStruct(column));

    result.setTableInfo(Adapter::unsafeCStyleString(query.tableName), Adapter::unsafeCStyleString(query.primaryKey),
                        true, static_cast<int>(query.columns.size()), attributes.data());

    for (const auto &attribute : attributes) {
        delete attribute.attrName;
        delete attribute.indexname;
    }

    return result;
}

// Convert Literal to Attribute, for passing data
Attribute Adapter::toAttribute(const Literal &literal) {
    Attribute result;
    if (auto intValue = literal.intValue()) {
        result.intData = *intValue;
        result.type = AttributeType::INT;
    } else if (auto floatValue = literal.floatValue()) {
        result.floatData = *floatValue;
        result.type = AttributeType::FLOAT;
    } else if (auto stringValue = literal.stringValue()) {
        strcpy(result.charData, stringValue->c_str());
        result.type = AttributeType::CHAR;
    }
    return result;
}

// Get info of an attribute
Attribute Adapter::toAttribute(TableInfo &table, const std::string &attributeName) {
    Attribute result;
    int attributeIndex = table.searchAttr(unsafeCStyleString(attributeName));
    result.type = table.attrType[attributeIndex];
    result.dataLength = table.attrLength[attributeIndex];
    return result;
}

// Get info of an attribute by index
Attribute Adapter::toAttribute(TableInfo &table, int attributeIndex) {
    Attribute result;
    result.type = table.attrType[attributeIndex];
    result.dataLength = table.attrLength[attributeIndex];
    return result;
}

Data Adapter::toData(const Literal &literal) {
    Data result;
    // Problem: What does 'int type' represents?
    if (auto intValue = literal.intValue()) {
        result.datai = *intValue;
        // result.type =
    } else if (auto floatValue = literal.floatValue()) {
        result.dataf = *floatValue;
        // result.type =
    } else if (auto stringValue = literal.stringValue()) {
        result.datas = *stringValue;
        // result.type =
    }
    return result;
}

Data Adapter::toData(const Attribute &attribute) {
    Data result;
    // Problem: What does 'int type' represents?
    switch (attribute.type) {
        case AttributeType::INT:
            result.datai = attribute.intData;
            break;
        case AttributeType::FLOAT:
            result.dataf = attribute.floatData;
            break;
        case AttributeType::CHAR:
            result.datas = std::string(attribute.charData);
            break;
        case AttributeType::UNDEFINE:
            break;
    }
    return result;
}

std::tuple<Data, Data> Adapter::toDataRange(const ComparisonCondition &condition) {
    switch (condition.binaryOperator) {
        case BinaryOpearator::LessThan:
        case BinaryOpearator::LessThanOrEqual:
            // Problem: Another data appears empty?
            return make_tuple(Data(), toData(condition.value));
        case BinaryOpearator::GreaterThan:
        case BinaryOpearator::GreaterThanOrEqual:
            return make_tuple(toData(condition.value), Data());
        default:
            // Assert unreachable branch
            return make_tuple(Data(), Data());
    }
}

char *Adapter::toOperatorString(BinaryOpearator op) {
    std::string str;
    switch (op) {
        case BinaryOpearator::Equal:
            str = "==";
            break;
        case BinaryOpearator::NotEqual:
            str = "!=";
            break;
        case BinaryOpearator::LessThan:
            str = "<";
            break;
        case BinaryOpearator::GreaterThan:
            str = ">";
            break;
        case BinaryOpearator::LessThanOrEqual:
            str = "<=";
            break;
        case BinaryOpearator::GreaterThanOrEqual:
            str = ">=";
            break;
    }
    return dynamicCStyleString(str);
}

Tuple Adapter::toTuple(const std::vector<Literal> &literals) {
    // Problem: insertAttr, rowData of Attribute?
    //          Should provide proper ctor of Attribute and Tuple
    std::vector<Attribute> attributes;
    for (const auto &literal : literals) attributes.push_back(toAttribute(literal));
    Tuple result;
    result.insertAttr(static_cast<int>(attributes.size()), attributes.data());
    return result;
}
