#pragma once

#include <set>

#include "../../catalog-manager/Catalog_Manager.h"
#include "../../record-manager/RecordManager.h"

namespace API_Util {
    void printTable(const std::vector<Tuple> &tuples, const TableInfo &table);

    void printError(const std::string &message);

    static std::set<int> intersect(const std::set<int> &a, const std::vector<int> &b);

    static std::set<int> intersect(const std::vector<int> &a, const std::vector<int> &b);
}
