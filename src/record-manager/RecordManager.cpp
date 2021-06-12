#include"RecordManager.h"
#include"CatalogManager.h"

RecordManager::RecordManager() {};

RecordManager::~RecordManager() {};

void RecordManager::createTable(char *tablename, tableInfo tbif) {
    buffer.createTablePage(tablename);
    char *pgdata = buffer.getTablePage(tablename, 0);
    int num = 0, length = 0;
    int j;
    for (j = 0; j < tbif.attrNum; j++) {
        length += tbif.attrLength[j];
    }
    memcpy(pgdata, &num, 4);
    memcpy(pgdata + 4, &length, 4);
    buffer.releasePage(pgdata);
}

void RecordManager::deleteTable(char *tablename) {
    buffer.dropTable(tablename);
}

void RecordManager::insertRecord(char *tbnm, Tuple tup, tableInfo tbif)       //参数：表名，rowdata；向表中插入元组，插入失败则报错
{
    tablePage tbpg;
    int pgNum = buffer.getTablePageNum(tbnm);
    int i, k, j;
    char *pgdata;
    int MaxPgNUM = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getTablePage(tbnm, i);
        tbpg.readTablePage(pgdata, tbif);
        MaxPgNUM = 4096 / tbpg.tupleLength;
        k = tbpg.checkdelete();
        if (tbpg.tupleNum < MaxPgNUM || k != -1) {
            tbpg.insertTuple(pgdata, tup, k);
        }
    }
    if (i == pgNum) {
        int m = 0;
        int tplength = 0;
        for (j = 0; j < tbif.attrNum; j++) {
            tplength += tbif.attrLength[j];
        }
        pgdata = buffer.addTablePage(tbnm);
        memcpy(pgdata, &m, 4);
        memcpy(pgdata + 4, &tplength, 4);
        tbpg.readTablePage(pgdata, tbif);
        tbpg.insertTuple(pgdata, tup, -1);
    }
    buffer.releasePage(pgdata);
}

void RecordManager::deleteRecord(char *tableName, int attrno, char *op, Attribute attr, tableInfo tbif) {
    tablePage tbpg;
    int pgNum = buffer.getTablePageNum(tableName);
    char *pgdata;
    int i, j, n = -1, p = 0;
    int t[200][1024] = {0};
    int count = 0;
    char null[4096] = "";
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getTablePage(tableName, i);
        tbpg.readTablePage(pgdata, tbif);
        tbpg.conditionsearch(attr, op, attrno, t[i]);
        j = 0;
        while (t[i][j] != 0) {
            tbpg.tp[(t[i][j])].hasdeleted = true;
            memcpy(tbpg.tp[(t[i][j])].rowData + 1, null, 4095);
            j++;
        }

    }
    buffer.releasePage(pgdata);
}

void RecordManager::conditionSelect(char *tableName, int attrno, char *op, Attribute attr, tableInfo tbif,
                                    Tuple *tup)//参数：表名，属性名，算数比较符，比较值
{
    tablePage tbpg;
    int pgNum = buffer.getTablePageNum(tableName);
    char *pgdata;
    int i, j, n = -1, p = 0;
    int t[200][1024] = {0};
    int count = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getTablePage(tableName, i);
        tbpg.readTablePage(pgdata, tbif);
        tbpg.conditionsearch(attr, op, attrno, t[i]);
        j = 0;
        while (t[i][j] != 0) {
            *(tup + count) = tbpg.tp[(t[i][j])];
            j++;
        }

    }
    buffer.releasePage(pgdata);
}

void RecordManager::nonconditionSelect(char *tableName, Tuple *tup, tableInfo tbif)                      //参数：表名；打印全部元组
{
    tablePage tbpg;
    int pgNum = buffer.getTablePageNum(tableName);
    char *pgdata;
    int i, j, n = -1, p = 0;
    int t[200][1024] = {0};
    int count = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getTablePage(tableName, i);
        tbpg.readTablePage(pgdata, tbif);
        tbpg.nonconditionsearch(t[i]);
        j = 0;
        while (t[i][j] != 0) {
            *(tup + count) = tbpg.tp[(t[i][j])];
            j++;
        }

    }
    buffer.releasePage(pgdata);
}


bool RecordManager::checkUnique(char *tableName, int attrno, Tuple tup, tableInfo tbif) {
    tablePage tbpg;
    int pgNum = buffer.getTablePageNum(tableName);
    char *pgdata;
    int i, j, n = -1, p = 0;
    int t[200][1024] = {0};
    Attribute attr = tup.attr[attrno];
    char op[3] = "==";
    bool flag = true;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getTablePage(tableName, i);
        tbpg.readTablePage(pgdata, tbif);
        tbpg.conditionsearch(attr, op, attrno, t[i]);
        j = 0;
        while (t[i][j] != 0) {
            flag = false;
        }

    }
    buffer.releasePage(pgdata);
    return flag;
}