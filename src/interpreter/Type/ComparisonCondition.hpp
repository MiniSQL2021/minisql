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
    ComparisonCondition(std::string columnName, BinaryOpearator binaryOperator, Literal value)
        : columnName(columnName), binaryOperator(binaryOperator), value(value){};
};