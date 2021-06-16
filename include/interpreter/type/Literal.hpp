#pragma once

#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <sstream>

using LiteralVariant = std::variant<int, float, std::string>;

enum class LiteralType {
    Int, Float, String
};

class Literal {
    const LiteralVariant value;

    template<typename T>
    [[nodiscard]] std::optional<T> getValue() const {
        return std::holds_alternative<T>(value) ? std::optional<T>(std::get<T>(value)) : std::nullopt;
    }

public:
    explicit Literal(int value) : value(value) {};

    explicit Literal(float value) : value(value) {};

    explicit Literal(std::string value) : value(std::move(value)) {};

    [[nodiscard]] LiteralType type() const {
        if (std::holds_alternative<int>(value)) return LiteralType::Int;
        if (std::holds_alternative<float>(value)) return LiteralType::Float;
        if (std::holds_alternative<std::string>(value)) return LiteralType::String;
        throw std::logic_error("Unexpected type of Literal");
    }

    [[nodiscard]] std::optional<int> intValue() const { return getValue<int>(); }

    [[nodiscard]] std::optional<float> floatValue() const { return getValue<float>(); }

    [[nodiscard]] std::optional<std::string> stringValue() const { return getValue<std::string>(); }

    [[nodiscard]] std::string toString() const {
        std::stringstream stream;
        switch (type()) {
            case LiteralType::Int:
                stream << "int(" << intValue().value();
                break;
            case LiteralType::Float:
                stream << "float(" << floatValue().value();
                break;
            case LiteralType::String:
                stream << "string(" << stringValue().value();
                break;
        }
        stream << ")";
        return stream.str();
    }

    constexpr bool operator==(const Literal &that) const { return this->value == that.value; }

    constexpr bool operator!=(const Literal &that) const { return this->value != that.value; }

    constexpr bool operator<(const Literal &that) const { return this->value < that.value; }

    constexpr bool operator>(const Literal &that) const { return this->value > that.value; }

    constexpr bool operator<=(const Literal &that) const { return this->value <= that.value; }

    constexpr bool operator>=(const Literal &that) const { return this->value <= that.value; }
};
