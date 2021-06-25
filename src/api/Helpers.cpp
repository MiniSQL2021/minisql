#include "API.hpp"

void API::directlyInput(const std::string &query) {
    std::stringstream ss(query);
    interpreter.parse(ss);
}

std::string API::toString(AttributeType type) {
    switch (type) {
        case AttributeType::INT:
            return "INT";
        case AttributeType::FLOAT:
            return "FLOAT";
        case AttributeType::CHAR:
            return "CHAR";
        case AttributeType::UNDEFINE:
            return "UNDEFINED";
    }
}
