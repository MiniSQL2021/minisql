#include "API_Util.hpp"
#include "Adapter.hpp"
#include "helper/tabulate.hpp"

using TableRow = std::vector<variant<std::string, const char *, tabulate::Table>>;

void API_Util::printTable(const std::vector<Tuple> &tuples, const TableInfo &table) {
    tabulate::Table output;

    TableRow header;
    header.reserve(table.attrNum);
    for (int i = 0; i < table.attrNum; i++) header.emplace_back(table.attrName[i]);
    output.add_row(header);

    for (const auto &tuple:tuples) {
        TableRow row;
        row.reserve(table.attrNum);
        for (int i = 0; i < table.attrNum; i++) row.push_back(Adapter::toString(tuple.attr[i]));
        output.add_row(row);
    }

    // Set alignment (right for numbers, left default)
    for (int i = 0; i < table.attrNum; i++) {
        switch (table.attrType[i]) {
            case AttributeType::INT:
            case AttributeType::FLOAT:
                output.column(i).format().font_align(tabulate::FontAlign::right);
                break;
            default:
                break;
        }
    }

    std::cout << output << std::endl;
    std::cout << table.attrNum << (table.attrNum <= 1 ? "row" : "rows") << " in set ";
}

void API_Util::printError(const string &message) {
    std::cout << "ERROR: " << message << "." << std::endl;
}

std::set<int> API_Util::intersect(const std::set<int> &a, const std::vector<int> &b) {
    std::set<int> result;
    std::vector<int> sortedB = b;
    std::sort(sortedB.begin(), sortedB.end());
    std::set_intersection(a.cbegin(), a.cend(), sortedB.cbegin(), sortedB.cend(),
                          std::inserter(result, result.begin()));
    return result;
}

std::set<int> API_Util::intersect(const std::vector<int> &a, const std::vector<int> &b) {
    std::set<int> result;
    std::vector<int> sortedA = a;
    std::sort(sortedA.begin(), sortedA.end());
    std::vector<int> sortedB = b;
    std::sort(sortedB.begin(), sortedB.end());
    std::set_intersection(sortedA.cbegin(), sortedA.cend(), sortedB.cbegin(), sortedB.cend(),
                          std::inserter(result, result.begin()));
    return result;
}
