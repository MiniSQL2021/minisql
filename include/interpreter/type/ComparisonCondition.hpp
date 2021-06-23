#pragma once

#include <optional>
#include <string>
#include <utility>
#include <variant>

#include "BinaryOperator.hpp"
#include "Literal.hpp"

struct ComparisonCondition {
    std::string columnName;
    BinaryOpearator binaryOperator;
    Literal value;

    ComparisonCondition(std::string columnName, BinaryOpearator binaryOperator, Literal value)
            : columnName(std::move(columnName)), binaryOperator(binaryOperator), value(std::move(value)) {};

    ComparisonCondition(const ComparisonCondition &other) = default;

    ComparisonCondition &operator=(const ComparisonCondition &other) = default;

    ComparisonCondition(ComparisonCondition &&other) noexcept = default;

    ComparisonCondition &operator=(ComparisonCondition &&other) noexcept = default;
};