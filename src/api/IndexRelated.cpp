#include "API.hpp"

std::vector<int> API::getAllIndexedAttributeIndex(const TableInfo &table) {
    std::vector<int> result;
    for (int i = 0; i < table.attrNum; i++)
        if (table.hasIndex[i]) result.push_back(i);
    return result;
}

void API::createIndex(TableInfo &table, Index &index, int attributeIndex, const std::string &indexName) {
    auto attribute = Adapter::toAttribute(table, attributeIndex);
    index.createIndexWithDatas(Adapter::getIndexFilePath(table.TableName, table.attrName[attributeIndex]),
                               Adapter::toDataType(attribute.type), attributeIndex,
                               recordManager.nonConditionSelect(table.TableName, table),
                               table.attrLength[attributeIndex]);
    catalogManager.createIndex(table.TableName, table.attrName[attributeIndex], Adapter::unsafeCStyleString(indexName));
}

void API::dropIndex(TableInfo &table, int attributeIndex) {
    // Assume the index exists
    auto attribute = Adapter::toAttribute(table, attributeIndex);
    auto attributeName = table.attrName[attributeIndex];
    Index index(table.TableName, table, bufferManager);
    index.dropIndex(Adapter::getIndexFilePath(table.TableName, attributeName),
                    Adapter::toDataType(attribute.type));
}
