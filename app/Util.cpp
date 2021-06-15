#include "Util.h"

void Util::printTable(std::vector<Tuple> tuples, TableInfo table) {
    // TODO: Table formatted output
}

std::set<int> Util::intersect(const std::set<int> &destination, const std::vector<int> &source) {
    std::set<int> result;
    std::vector<int> sortedSource = source;
    std::sort(sortedSource.begin(), sortedSource.end());
    std::set_intersection(sortedSource.cbegin(), sortedSource.cend(), destination.cbegin(), destination.cend(),
                          std::inserter(result, result.begin()));
    return result;
}
