#pragma once

#include <optional>
#include <stdexcept>
#include <string>
#include <variant>

using LiteralVariant = std::variant<int, float, std::string>;

enum class LiteralType { Int, Float, String };

class Literal {
    LiteralVariant value;

    template <typename T> std::optional<T> getValue() {
        return std::holds_alternative<T>(value) ? std::optional<T>(std::get<T>(value))
                                                : std::nullopt;
    }

  public:
    Literal(int value) : value(value){};
    Literal(float value) : value(value){};
    Literal(std::string value) : value(value){};

    LiteralType type() {
        if (std::holds_alternative<int>(value)) return LiteralType::Int;
        if (std::holds_alternative<float>(value)) return LiteralType::Float;
        if (std::holds_alternative<std::string>(value)) return LiteralType::String;
        throw std::logic_error("Unexpected type of Literal");
    }

    std::optional<int> intValue() { return getValue<int>(); }
    std::optional<float> floatValue() { return getValue<float>(); }
    std::optional<std::string> stringValue() { return getValue<std::string>(); }
};