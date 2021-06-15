#pragma once

#include <set>

#include "Catalog_Manager.h"
#include "RecordManager.h"

namespace Util {
    void printTable(std::vector<Tuple> tuples, TableInfo table);

    static std::set<int> intersect(const std::set<int> &destination, const std::vector<int> &source);
}
