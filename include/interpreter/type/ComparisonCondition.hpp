#pragma once

#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "BinaryOperator.hpp"
#include "Literal.hpp"

struct ComparisonCondition {
    const std::string columnName;
    const BinaryOpearator binaryOperator;
    const Literal value;

    ComparisonCondition(std::string columnName, BinaryOpearator binaryOperator, Literal value)
            : columnName(std::move(columnName)), binaryOperator(binaryOperator), value(std::move(value)) {};
};