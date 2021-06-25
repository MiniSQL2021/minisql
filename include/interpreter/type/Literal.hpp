#pragma once

#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <string>

using LiteralVariant = std::variant<int, float, std::string>;

enum class LiteralType {
    Int, Float, String
};

class Literal {
    LiteralVariant value;

    template<typename T>
    [[nodiscard]] std::optional<T> getValue() const {
        return std::holds_alternative<T>(value) ? std::optional<T>(std::get<T>(value)) : std::nullopt;
    }

public:
    explicit Literal(int value) : value(value) {};

    explicit Literal(float value) : value(value) {};

    explicit Literal(std::string value) : value(std::move(value)) {};

    // Copy ctor
    Literal(const Literal &other) = default;

    // Copy assignment
    Literal &operator=(const Literal &other) = default;

    // Move ctor
    Literal(Literal &&other) noexcept = default;

    // Move assignment
    Literal &operator=(Literal &&other) noexcept = default;

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
        switch (type()) {
            case LiteralType::Int:
                return std::to_string(intValue().value());
            case LiteralType::Float:
                return std::to_string(floatValue().value());
            case LiteralType::String:
                return stringValue().value();
        }
    }

    constexpr bool operator==(const Literal &that) const { return this->value == that.value; }

    constexpr bool operator!=(const Literal &that) const { return this->value != that.value; }

    constexpr bool operator<(const Literal &that) const { return this->value < that.value; }

    constexpr bool operator>(const Literal &that) const { return this->value > that.value; }

    constexpr bool operator<=(const Literal &that) const { return this->value <= that.value; }

    constexpr bool operator>=(const Literal &that) const { return this->value <= that.value; }
};
