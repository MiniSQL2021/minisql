#pragma once

#include <optional>
#include <string>
#include <variant>

#include "BinaryOperator.hpp"
#include "Literal.hpp"

class ComparisonCondition {
    const std::string columnName;
    const BinaryOpearator binaryOperator;
    const Literal value;

  public:
    ComparisonCondition(std::string columnName, BinaryOpearator binaryOperator, int value)
        : columnName(columnName), binaryOperator(binaryOperator), value(value){};
    ComparisonCondition(std::string columnName, BinaryOpearator binaryOperator, float value)
        : columnName(columnName), binaryOperator(binaryOperator), value(value){};
    ComparisonCondition(std::string columnName, BinaryOpearator binaryOperator, std::string value)
        : columnName(columnName), binaryOperator(binaryOperator), value(value){};
};