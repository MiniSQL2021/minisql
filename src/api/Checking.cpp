#include "API.hpp"
#include "InvalidQueryException.hpp"

#include <unordered_set>

void API::checkTableSchema(const CreateTableQuery &query) {
    if (query.tableName.length() > 24)
        throw InvalidQueryException("Table name must be no more than 24 characters");
    if (query.columns.size() > 32)
        throw InvalidQueryException("The number of attributes must be no more than 32");

    std::unordered_set<std::string> set;
    for (const auto &column : query.columns) {
        if (set.contains(column.name))
            throw InvalidQueryException("Attribute `" + column.name + "` appears more than once");
        else if (column.name.length() > 24)
            throw InvalidQueryException(
                    "Attribute name of `" + column.name + "` must be no more than 24 characters");
        else if (column.type == LiteralType::String && (*column.maxLength < 1 || *column.maxLength > 255))
            throw InvalidQueryException(
                    "Max length of CHAR attribute `" + column.name + "` must fall between 1 and 255");
        set.insert(column.name);
    }
    if (!set.contains(query.primaryKey))
        throw InvalidQueryException(
                "Primary key `" + query.primaryKey + "` doesn't appear in attribute list");
}

// Check 1) if some attribute name in the condition list doesn't exist
//       2) if type of some value in the condition list doesn't match the actual type
// Side effect: if it's the case when input is int and expected is float, convert this condition
// Throw: InvalidQueryException
void API::checkConditionList(TableInfo &table, std::vector<ComparisonCondition> &conditions) {
    for (auto condition = conditions.begin(); condition < conditions.end(); condition++) {
        try {
            int attributeIndex = table.searchAttr(Adapter::unsafeCStyleString(condition->columnName));
            auto inputType = Adapter::toAttributeType(condition->value.type());
            auto expectedType = table.attrType[attributeIndex];
            if (inputType != expectedType) {
                if (inputType == AttributeType::INT && expectedType == AttributeType::FLOAT) {
                    Literal floatLiteral(static_cast<float>(*condition->value.intValue()));
                    ComparisonCondition newCondition(condition->columnName, condition->binaryOperator, floatLiteral);
                    *condition = std::move(newCondition);
                } else
                    throw InvalidQueryException(
                            "Attribute `" + condition->columnName + "` expects " + toString(expectedType) +
                            ", but received " + toString(inputType));
            }
        } catch (const attr_does_not_exist &error) {
            throw InvalidQueryException("Attribute `" + condition->columnName + "` doesn't exists");
        }
    }
}

bool API::isValueExists(TableInfo &table, Index &index, int attributeIndex, const Literal &value) {
    if (table.hasIndex[attributeIndex])
        return index.findIndex(Adapter::getIndexFilePath(table.TableName, table.attrName[attributeIndex]),
                               Adapter::toData(value)) != -1;
    else
        return !recordManager.checkUnique(
                table.TableName, attributeIndex, Adapter::toAttribute(value), table);
}

// Check 1) if type of some value in the value list doesn't match the actual type
//       2) if some value of unique attribute conflicts with existing values
// Side effect: if it's the case when input is int and expected is float, convert this literal
// Throw: InvalidQueryException
void API::checkInsertingValues(TableInfo &table, Index &index, std::vector<Literal> &literals) {
    for (auto value = literals.begin(); value < literals.end(); value++) {
        int attributeIndex = static_cast<int>(value - literals.cbegin());
        auto inputType = Adapter::toAttributeType(value->type());
        auto expectedType = table.attrType[attributeIndex];
        if (inputType != expectedType) {
            if (inputType == AttributeType::INT && expectedType == AttributeType::FLOAT) {
                Literal floatLiteral(static_cast<float>(*value->intValue()));
                *value = std::move(floatLiteral);
            } else
                throw InvalidQueryException(
                        "Attribute `" + std::string(table.attrName[attributeIndex]) + "` expects " +
                        toString(expectedType) + ", but received " + toString(inputType));
        }
        if (expectedType == AttributeType::CHAR && value->stringValue()->size() > table.attrLength[attributeIndex])
            throw InvalidQueryException(
                    "Value `" + value->toString() + "` on `" + table.attrName[attributeIndex] +
                    "` is longer than its max length " + std::to_string(table.attrLength[attributeIndex]));
        if (table.attrUnique[attributeIndex] && isValueExists(table, index, attributeIndex, *value))
            throw InvalidQueryException(
                    "Value `" + value->toString() + "` already exists in the unique attribute `" +
                    table.TableName + "." + table.attrName[attributeIndex] + "`");
    }
}
