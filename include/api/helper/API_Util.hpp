#pragma once

#include <set>

#include "../../catalog-manager/Catalog_Manager.h"
#include "../../record-manager/RecordManager.h"

namespace Util {
    void printTable(std::vector<Tuple> tuples, TableInfo table);

    void printError(const std::string &message);

    static std::set<int> intersect(const std::set<int> &a, const std::vector<int> &b);

    static std::set<int> intersect(const std::vector<int> &a, const std::vector<int> &b);
}
