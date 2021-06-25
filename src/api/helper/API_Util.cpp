#include "API_Util.hpp"
#include "tabulate/table.hpp"

using TableRow = std::vector<variant<std::string, const char *, tabulate::Table>>;

std::string toString(Attribute attribute) {
    switch (attribute.type) {
        case AttributeType::INT:
            return std::to_string(attribute.intData);
        case AttributeType::FLOAT:
            return std::to_string(attribute.floatData);
        case AttributeType::CHAR:
            return std::string(attribute.charData);
        case AttributeType::UNDEFINE:
            return "";
    }
}

void API_Util::printTable(const std::vector<Tuple> &tuples, const TableInfo &table) {
    tabulate::Table output;

    TableRow header;
    header.reserve(table.attrNum);
    for (int i = 0; i < table.attrNum; i++) header.emplace_back(table.attrName[i]);
    output.add_row(header);

    for (const auto &tuple:tuples) {
        TableRow row;
        row.reserve(table.attrNum);
        for (int i = 0; i < table.attrNum; i++) row.push_back(toString(tuple.attr[i]));
        output.add_row(row);
    }

    output.format().hide_border_top();
    output[0].format()
            .show_border_top();
    if (!tuples.empty()) output[1].format().show_border_top();

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
    std::cout << tuples.size() << (tuples.size() <= 1 ? " row" : " rows") << " in set ";
}

void API_Util::printError(const std::string &message) { std::cout << "ERROR: " << message << " "; }

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

std::string API_Util::internalIndexName(const std::string &tableName, const std::string &attributeName) {
    return "__idx" + tableName + "_" + attributeName;
}
