#include "Util.h"

char *Util::toCStyleString(std::string str) {
    char *result = new char[str.size() + 1];
    strcpy(result, str.c_str());
    return result;
}