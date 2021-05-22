#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "Literal.hpp"

struct Column {
    const std::string name;
    const LiteralType type;
    const std::optional<int> maxLength;
    const bool unique;

    Column(std::string name, LiteralType type, bool unique = false)
            : name(std::move(name)), type(type), unique(unique) {};

    Column(std::string name, LiteralType type, int maxLength, bool unique = false)
            : name(std::move(name)), type(type), maxLength(maxLength), unique(unique) {};

    virtual ~Column() = default;
};
