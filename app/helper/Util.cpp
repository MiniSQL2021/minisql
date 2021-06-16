#include "Util.h"

void Util::printTable(std::vector<Tuple> tuples, TableInfo table) {
    // TODO: Table formatted output
}

void Util::printError(const string &message) {
    std::cout << "ERROR: " << message << "." << std::endl;
}

std::set<int> Util::intersect(const std::set<int> &a, const std::vector<int> &b) {
    std::set<int> result;
    std::vector<int> sortedB = b;
    std::sort(sortedB.begin(), sortedB.end());
    std::set_intersection(a.cbegin(), a.cend(), sortedB.cbegin(), sortedB.cend(),
                          std::inserter(result, result.begin()));
    return result;
}

std::set<int> Util::intersect(const std::vector<int> &a, const std::vector<int> &b) {
    std::set<int> result;
    std::vector<int> sortedA = a;
    std::sort(sortedA.begin(), sortedA.end());
    std::vector<int> sortedB = b;
    std::sort(sortedB.begin(), sortedB.end());
    std::set_intersection(sortedA.cbegin(), sortedA.cend(), sortedB.cbegin(), sortedB.cend(),
                          std::inserter(result, result.begin()));
    return result;
}
