#include <cstring>

#include"tuple.h"

Tuple::Tuple() {
    attrNum = 0;
}

Tuple::~Tuple() {};

Tuple::Tuple(const Tuple &tp) {
    int i;
    hasdeleted = tp.hasdeleted;
    attrNum = tp.attrNum;
    for (i = 0; i < attrNum; i++) {
        attr[i] = tp.attr[i];
    }
    memcpy(rowData, tp.rowData, 4096);
}

void Tuple::readRowData(char *RowData, TableInfo tbif) {
    memcpy(&hasdeleted, RowData, 1);
    attrNum = tbif.attrNum;
    int i;
    int p = 1;
    for (i = 0; i < attrNum; i++) {
        attr[i].dataLength = tbif.attrLength[i];
        switch (tbif.attrType[i]) {
            case AttributeType::INT: {
                attr[i].type = AttributeType::INT;
                memcpy(attr[i].rowData, RowData + p, 4);
                attr[i].releaseRowData();
                break;
            }
            case AttributeType::FLOAT: {
                attr[i].type = AttributeType::FLOAT;
                memcpy(attr[i].rowData, RowData + p, 4);
                attr[i].releaseRowData();
                break;
            }
            case AttributeType::CHAR: {
                attr[i].type = AttributeType::CHAR;
                memcpy(attr[i].rowData, RowData + p, attr[i].dataLength);
                attr[i].releaseRowData();
                break;
            }
        }
        p += attr[i].dataLength;
    }
}

void Tuple::setRowData() {
    memcpy(rowData, &hasdeleted, 1);
    int i, p = 1;
    for (i = 0; i < attrNum; i++) {

        switch (attr[i].type) {
            case AttributeType::INT: {
                attr[i].getRowData();
                memcpy(rowData + p, attr[i].rowData, 4);
                p += 4;
                break;
            }
            case AttributeType::FLOAT: {
                attr[i].getRowData();
                memcpy(rowData + p, attr[i].rowData, 4);
                p += 4;
                break;
            }
            case AttributeType::CHAR: {
                attr[i].getRowData();
                memcpy(rowData + p, attr[i].rowData, attr[i].dataLength);
                p += attr[i].dataLength;
                break;
            }
        }
    }
}

void Tuple::setTuple(int attrnum, std::vector<Attribute> atr, TableInfo tbif)
//参数*rowdata：（4字节 attrType）数据
{
    attrNum = attrnum;
    int i;
    for (i = 0; i < attrNum; i++) {
        if (*(tbif.attrType + i) != atr[i].type) {
            throw illegal_data();
        }
        if (*(tbif.attrLength + i) < atr[i].dataLength) {
            throw illegal_data();
        }
        attr[i] = atr[i];
        if (attr[i].type == AttributeType::CHAR) attr[i].dataLength = tbif.attrLength[i];
    }
    setRowData();
}
