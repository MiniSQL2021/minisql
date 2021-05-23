#pragma once

#include <iostream>

#include "Literal.hpp"
#include "BinaryOperator.hpp"

namespace util {
    template<typename Derived, typename Base, typename Del>
    static std::unique_ptr<Derived, Del>
    dynamic_unique_ptr_cast(std::unique_ptr<Base, Del> &p) {
        if (auto *result = dynamic_cast<Derived *>(p.get())) {
            p.release();
            return std::unique_ptr<Derived, Del>(result, std::move(p.get_deleter()));
        }
        return std::unique_ptr<Derived, Del>(nullptr, p.get_deleter());
    }

    static std::string literalTypeString(const LiteralType &type) {
        switch (type) {
            case LiteralType::Int:
                return "int";
            case LiteralType::Float:
                return "float";
            case LiteralType::String:
                return "string";
        }
    }

    static std::string binaryOperatorString(const BinaryOpearator &binaryOperator) {
        switch (binaryOperator) {
            case BinaryOpearator::Equal:
                return "=";
            case BinaryOpearator::NotEqual:
                return "!=";
            case BinaryOpearator::LessThan:
                return "<";
            case BinaryOpearator::LessThanOrEqual:
                return "≤";
            case BinaryOpearator::GreaterThan:
                return ">";
            case BinaryOpearator::GreaterThanOrEqual:
                return "≥";
        }
    }
}