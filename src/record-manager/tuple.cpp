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
    strcpy(rowData, tp.rowData);
}

void Tuple::writeRowData(char *pageRowData) {
    memcpy(pageRowData, &hasdeleted, 1);
    int i;
    for (i = 0; i < attrNum; i++) {

        switch (attr[i].type) {
            case AttributeType::INT: {
                attr[i].getRowData();
                strncat(pageRowData, attr[i].rowData, 4);
                break;
            }
            case AttributeType::FLOAT: {
                attr[i].getRowData();
                strncat(pageRowData, attr[i].rowData, 4);
                break;
            }
            case AttributeType::CHAR: {
                attr[i].getRowData();
                strncat(pageRowData, attr[i].rowData, attr[i].dataLength);
                break;
            }
        }
    }
}

void Tuple::readRowData(char *RowData, TableInfo tbif) {
    memcpy(&hasdeleted, RowData, 1);
    attrNum = tbif.attrNum;
    int i;
    int p = 0;
    for (i = 0; i < attrNum; i++) {
        attr[i].dataLength = tbif.dataLength;
        switch (tbif.attrType[i]) {
            case AttributeType::INT: {
                attr[i].type = AttributeType::INT;
                strncpy(attr[i].rowData, RowData + p, 4);
                attr[i].releaseRowData();
                break;
            }
            case AttributeType::FLOAT: {
                attr[i].type = AttributeType::FLOAT;
                strncpy(attr[i].rowData, RowData + p, 4);
                attr[i].releaseRowData();
                break;
            }
            case AttributeType::CHAR: {
                attr[i].type = AttributeType::CHAR;
                strncpy(attr[i].rowData, RowData + p, attr[i].dataLength);
                attr[i].releaseRowData();
                break;
            }
        }
        p += attr[i].dataLength;
    }
}

void Tuple::setTuple(int attrnum, vector<Attribute> atr, TableInfo tbif)
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

    }
}

