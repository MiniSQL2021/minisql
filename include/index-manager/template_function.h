
#pragma once

#include <sstream>

//以下是几个模版函数，目的是为了简化record_manager中的代码

template<typename T>
int getDataLength(T data) {
    std::stringstream stream;
    stream << data;
    return stream.str().length();
}

template<typename T>
void copyString(char *p, int &offset, T data) {
    std::stringstream stream;
    stream << data;
    std::string s1 = stream.str();
    for (int i = 0; i < s1.length(); i++, offset++)
        p[offset] = s1[i];
}
