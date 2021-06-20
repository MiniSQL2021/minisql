#include <cstring>

/*
68+72n字节
	表长 4字节 int
	表名 28字节
	属性数4字节 int
		
		属性一共72字节
		{名称30字节 char，
		属性类型4字节 int，
		是否unique 1字节 char，
		索引有无1字节 char，
		索引名 32字节 char，
		属性长 4字节 int
		 }
		属性二、、、
	primarykey有无 1字节 char
	primarykey名31字节 char*/
#include "TableInfo.h"

TableInfo::TableInfo() {
    int i, j;
    for (i = 0; i < 32; i++) {
        for (j = 0; j < 31; j++) {
            attrName[i][j] = '\0';
            indexName[i][j] = '\0';
        }
        attrType[i] = AttributeType::UNDEFINE;
        hasIndex[i] = false;
        attrLength[i] = 0;

    }
    attrNum = 0;
    dataLength = 0;
}

TableInfo::TableInfo(const TableInfo &tbif) {
    strcpy(primaryKey, tbif.primaryKey);
    strcpy(TableName, tbif.TableName);
    memcpy(&hasPrimaryKey, &tbif.hasPrimaryKey, 1);
    memcpy(&attrNum, &tbif.attrNum, 4);

    int i;
    for (i = 0; i < attrNum; i++) {
        strcpy(attrName[i], tbif.attrName[i]);
        memcpy(attrType + i, tbif.attrType + i, 4);
        memcpy(attrUnique + i, tbif.attrUnique + i, 1);
        memcpy(hasIndex + i, tbif.hasIndex + i, 1);
        strcpy(indexName[i], tbif.indexName[i]);
        attrLength[i] = tbif.attrLength[i];
    }

    memcpy(&dataLength, &tbif.dataLength, 4);
    strcpy(rowData, tbif.rowData);
}

TableInfo::~TableInfo() {};

void TableInfo::setTableInfo(char *tbn, char *pn, bool hp, int an, attrStruct *atrs) {
    strcpy(TableName, tbn);
    strcpy(primaryKey, pn);
    hasPrimaryKey = hp;
    attrNum = an;
    dataLength = 69 + 72 * attrNum;

    int i;
    for (i = 0; i < attrNum; i++) {
        strcpy(attrName[i], (atrs + i)->attrName);
        memcpy(attrType + i, &(atrs + i)->attrType, 4);
        memcpy(attrUnique + i, &(atrs + i)->attrUnique, 1);
        memcpy(hasIndex + i, &(atrs + i)->hasIndex, 1);
        strcpy(indexName[i], (atrs + i)->indexname);
        attrLength[i] = (atrs + i)->attrlength;
    }
    insertRowData();
}

int TableInfo::searchAttr(char *attrname) {
    int i;
    for (i = 0; i < attrNum; i++) {
        if (strcmp(attrname, attrName[i])) {
            return i;
        }
    }
    if (i >= attrNum) {
        throw attr_does_not_exist();                //attr does not exist
    }
}

void TableInfo::insertRowData() {

    int i, p = 0;
    memcpy(rowData, &dataLength, 4);
    p += 4;
    memcpy(rowData + p, TableName, 28);
    p += 28;
    memcpy(rowData + p, &attrNum, 4);
    p += 4;
    for (i = 0; i < attrNum; i++) {
        memcpy(rowData + p, attrName[i], 30);
        p += 30;
        memcpy(rowData + p, attrType + i, 4);
        p += 4;
        memcpy(rowData + p, attrUnique + i, 1);
        p += 1;
        memcpy(rowData + p, hasIndex + i, 1);
        p += 1;
        memcpy(rowData + p, indexName[i], 32);
        p += 32;
        memcpy(rowData + p, attrLength + i, 4);
        p += 4;
    }
    memcpy(rowData + p, &hasPrimaryKey, 1);
    p += 1;
    memcpy(rowData + p, primaryKey, 31);
    p += 31;
    char a = '#';
    memcpy(rowData + p, &a, 1);
}

void TableInfo::getFromRowData() {
    int i, p = 0;
    memcpy(&dataLength, rowData, 4);
    p += 4;
    memcpy(TableName + p, rowData, 28);
    p += 28;
    memcpy(&attrNum, rowData + p, 4);
    p += 4;
    for (i = 0; i < attrNum; i++) {
        memcpy(attrName[i], rowData + p, 30);
        p += 30;
        memcpy(attrType + i, rowData + p, 4);
        p += 4;
        memcpy(attrUnique + i, rowData + p, 1);
        p += 1;
        memcpy(hasIndex + i, rowData + p, 1);
        p += 1;
        memcpy(indexName[i], rowData + p, 32);
        p += 32;
        memcpy(attrLength + i, rowData + p, 4);
        p += 4;
    }
    memcpy(&hasPrimaryKey, rowData + p, 1);
    p += 1;
    memcpy(primaryKey, rowData + p, 31);
}
