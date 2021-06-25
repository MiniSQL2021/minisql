#include "API.hpp"

#include <filesystem>

namespace fs = std::filesystem;

void API::bootstrap() {
    try {
        fs::create_directories("database/catalog");
        fs::create_directories("database/data");
        fs::create_directories("database/index");
    } catch (...) {
        std::cout << "FATAL ERROR: File access denied." << std::endl;
        exit(1);
    }
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
