#pragma once

#include <set>

#include "../../catalog-manager/tableInfo.h"
#include "../../record-manager/tuple.h"

namespace API_Util {
    void printTable(const std::vector<Tuple> &tuples, const TableInfo &table);

    void printError(const std::string &message);

    std::set<int> intersect(const std::set<int> &a, const std::vector<int> &b);

    std::set<int> intersect(const std::vector<int> &a, const std::vector<int> &b);
}
