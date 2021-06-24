#pragma once

#include <exception>
#include <string>
#include <utility>

struct InvalidQueryException : public std::exception {
    const std::string message;

    explicit InvalidQueryException(std::string message) : message{std::move(message)} {};

    [[nodiscard]] const char *what() const noexcept override { return message.c_str(); }
};
