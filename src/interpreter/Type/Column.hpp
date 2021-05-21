#pragma once

#include <optional>
#include <string>
#include <vector>

#include "Literal.hpp"

class Column {
    const std::string name;
    const LiteralType type;
    const std::optional<int> maxLength;
    const bool unique;

  public:
    Column(std::string name, LiteralType type, bool unique = false)
        : name(name), type(type), unique(unique){};
    Column(std::string name, LiteralType type, int maxLength, bool unique = false)
        : name(name), type(type), maxLength(maxLength), unique(unique){};
    virtual ~Column(){};
};
