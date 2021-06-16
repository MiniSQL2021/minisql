#include"RecordManager.h"

void RecordManager::createTable(char *tablename, TableInfo tbif) {
    int j, length = 0;
    for (j = 0; j < tbif.attrNum; j++) {
        length += tbif.attrLength[j];
    }

    string str = "./database/data/";
    str += tablename;
    FILE *f = fopen(str.c_str(), "w");
    int n[2] = {0, length};
    fwrite(n, 4, 2, f);
    fclose(f);
}

void RecordManager::deleteTable(char *tablename) {
    string table_name = tablename;
    table_name = "./database/data/" + table_name;
    remove(table_name.c_str());
}

int RecordManager::insertRecord(char *tbnm, Tuple tup, TableInfo tbif)       //参数：表名，rowdata；向表中插入元组，插入失败则报错
{
    tablePage *tbpg = new tablePage;
    int pgNum = getPageNum(tbnm);
    int i, k, j, asw = 0, p = 0;
    char *pgdata = '\0';
    int MaxPgNUM = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage(tbnm, i);
        tbpg->readTablePage(pgdata, tbif);
        MaxPgNUM = 4096 / tbpg->tupleLength;
        k = tbpg->checkdelete();
        if (tbpg->tupleNum < MaxPgNUM || k != -1) {
            p = tbpg->insertTuple(pgdata, tup, k);

        }
        asw += tbpg->tupleNum;
    }
    if (i == pgNum) {
        p = 1;
        int m = 0;
        int tplength = 0;
        for (j = 0; j < tbif.attrNum; j++) {
            tplength += tbif.attrLength[j];
        }
        pgdata = buffer.getPage(tbnm, i);
        memcpy(pgdata, &m, 4);
        memcpy(pgdata + 4, &tplength, 4);
        tbpg->readTablePage(pgdata, tbif);
        tbpg->insertTuple(pgdata, tup, -1);
    }
    int b = buffer.getPageId(tbnm, i);
    buffer.modifyPage(b);
    delete tbpg;
    return asw + p;
}

void RecordManager::deleteRecord(char *tableName, vector<int> no, TableInfo tbif)   //参数：表名，序号
{
    tablePage *tbpg = new tablePage;
    vector<int> nm;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j = 0;
    int p = 0, size = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage(tableName, i);
        tbpg->readTablePage(pgdata, tbif);

        size += tbpg->tupleNum;
        while (size > no[j]) {
            nm.push_back(no[j] - p);
            j++;
        }
        p = size;

        nm.clear();
        if (nm[0]) {
            tbpg->deleteTuple(pgdata, nm);
            int b = buffer.getPageId(tableName, i);
            buffer.modifyPage(b);
        }
    }
    delete tbpg;
}

void RecordManager::deleteAllRecord(char *tableName, TableInfo tbif) {
    deleteTable(tableName);
    createTable(tableName, tbif);
}

vector<Tuple> RecordManager::searchTuple(char *tableName, TableInfo tbif, vector<int> no) {
    tablePage *tbpg = new tablePage;
    vector<int> nm;
    vector<Tuple> tup;
    vector<Tuple> temp;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j = 0;
    int p = 0, size = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage(tableName, i);
        tbpg->readTablePage(pgdata, tbif);

        size += tbpg->tupleNum;
        while (size > no[j]) {
            nm.push_back(no[j] - p);
            j++;
        }
        p = size;
        temp = tbpg->searchTuple(nm);
        tup.insert(tup.end(), temp.begin(), temp.end());
        nm.clear();
        temp.clear();
    }
    return tup;
    delete tbpg;
}

vector<int> RecordManager::conditionSelect(char *tableName, int attrno, char *op, Attribute attr, TableInfo tbif)
//参数：表名，属性序号（用catalog'的getattrNo），算数比较符，比较值, tbif
{
    vector<int> no;
    vector<int> temp;
    tablePage *tbpg = new tablePage;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j;
    int p = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage(tableName, i);
        tbpg->readTablePage(pgdata, tbif);

        temp = tbpg->conditionsearch(attr, op, attrno, p);
        no.insert(no.end(), temp.begin(), temp.end());
        p += tbpg->tupleNum;
    }
    delete tbpg;
    return no;
}

vector<Tuple> RecordManager::nonConditionSelect(char *tableName,
                                                TableInfo tbif)                        //参数：表名,存放数组，tableinfo；返回全部tuple
{
    vector<Tuple> tup;
    vector<Tuple> temp;
    tablePage *tbpg = new tablePage;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j;
    int count = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage(tableName, i);
        tbpg->readTablePage(pgdata, tbif);
        temp = (tbpg->nonconditionsearch());
        tup.insert(tup.end(), temp.begin(), temp.end());
    }
    delete tbpg;
    return tup;
}

bool RecordManager::checkUnique(char *tableName, int attrno, Attribute attr, TableInfo tbif) {
    tablePage *tbpg = new tablePage;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j, n = -1, p = 0;
    char op[3] = "==";
    bool flag = true;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage(tableName, i);
        tbpg->readTablePage(pgdata, tbif);

        for (j = 0; j < tbpg->tupleNum; j++) {
            if (tbpg->tp[j].attr[attrno] == attr) {
                flag = false;
            }
        }
    }
    delete tbpg;
    return flag;
}

int RecordManager::getPageNum(char *tableName) {
    string name;
    name = tableName;
    char *p;
    int block_num = -1;
    do {
        p = buffer.getPage(name, block_num + 1);
        block_num++;
    } while (p[0] != '\0');
    return block_num;
}
