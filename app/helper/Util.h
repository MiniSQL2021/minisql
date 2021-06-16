#pragma once

#include <set>

#include "Catalog_Manager.h"
#include "RecordManager.h"

namespace Util {
    void printTable(std::vector<Tuple> tuples, TableInfo table);

    static std::set<int> intersect(const std::set<int> &a, const std::vector<int> &b);

    static std::set<int> intersect(const std::vector<int> &a, const std::vector<int> &b);
}
