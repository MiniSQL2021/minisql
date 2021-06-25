#include <cstring>

#include"RecordManager.h"

void RecordManager::createTable(char *tablename, TableInfo tbif) {
    int j, length = 1;
    for (j = 0; j < tbif.attrNum; j++) {
        length += tbif.attrLength[j];
    }

    std::string str = "./database/data/";
    str += tablename;
    FILE *f = fopen(str.c_str(), "w");
    int n[2] = {0, length};
    fwrite(n, 4, 2, f);
    fclose(f);
}

void RecordManager::deleteTable(char *tablename) {
    std::string table_name = tablename;
    table_name = "./database/data/" + table_name;
    buffer.deleteFile(table_name);
}

int RecordManager::insertRecord(char *tbnm, Tuple tup, TableInfo tbif)       //参数：表名，rowdata；向表中插入元组，插入失败则报错
{
    tablePage *tbpg = new tablePage;
    int pgNum = getPageNum(tbnm);
    int i, k, j, asw = 0, p = 0;
    char *pgdata;
    int MaxPgNUM = 0;
    bool isWritten = false;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage("./database/data/" + std::string(tbnm), i);
        tbpg->readTablePage(pgdata, tbif);
        MaxPgNUM = 4096 / tbpg->tupleLength;
        k = tbpg->checkdelete();
        if (tbpg->tupleNum < MaxPgNUM || k != -1) {
            p = tbpg->insertTuple(pgdata, tup, k);
            isWritten = true;
            break;
        }
        asw += tbpg->tupleNum;
    }
    if (!isWritten) {
        p = 1;
        int m = 0;
        int tplength = 0;
        for (j = 0; j < tbif.attrNum; j++) {
            tplength += tbif.attrLength[j];
        }
        pgdata = buffer.getPage("./database/data/" + std::string(tbnm), i);
        memcpy(pgdata, &m, 4);
        memcpy(pgdata + 4, &tplength, 4);
        tbpg->readTablePage(pgdata, tbif);
        tbpg->insertTuple(pgdata, tup, -1);
    }
    int b = buffer.getPageId("./database/data/" + std::string(tbnm), i);
    buffer.modifyPage(b);
    buffer.flushAfterQuery();
    delete tbpg;
    return asw + p;
}

void RecordManager::deleteRecord(char *tableName, std::vector<int> no,
                                 TableInfo tbif) //参数：表名，序号
{
    tablePage *tbpg = new tablePage;
    std::vector<int> nm;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j = 0;
    int p = 0, size = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage("./database/data/" + std::string(tableName), i);
        tbpg->readTablePage(pgdata, tbif);

        size += tbpg->tupleNum;
        while (j < no.size() && size > no[j]) {
            nm.push_back(no[j] - p);
            j++;
        }
        p = size;

        if (!nm.empty()) {
            tbpg->deleteTuple(pgdata, nm);
            int b = buffer.getPageId("./database/data/" + std::string(tableName), i);
            buffer.modifyPage(b);
            buffer.flushAfterQuery();
        }
        nm.clear();
    }
    delete tbpg;
}

void RecordManager::deleteAllRecord(char *tableName, TableInfo tbif) {
    deleteTable(tableName);
    createTable(tableName, tbif);
}

std::vector<Tuple> RecordManager::searchTuple(char *tableName, TableInfo tbif,
                                              std::vector<int> no) {
    tablePage *tbpg = new tablePage;
    std::vector<int> nm;
    std::vector<Tuple> tup;
    std::vector<Tuple> temp;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j = 0;
    int p = 0, size = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage("./database/data/" + std::string(tableName), i);
        tbpg->readTablePage(pgdata, tbif);

        size += tbpg->tupleNum;
        while (j < no.size() && size > no[j]) {
            nm.push_back(no[j] - p);
            j++;
        }
        p = size;
        temp = tbpg->searchTuple(nm);
        tup.insert(tup.end(), temp.begin(), temp.end());
        nm.clear();
        temp.clear();
    }
    delete tbpg;
    return tup;
}

std::vector<int> RecordManager::conditionSelect(char *tableName, int attrno, char *op,
                                                Attribute attr, TableInfo tbif)
//参数：表名，属性序号（用catalog'的getattrNo），算数比较符，比较值, tbif
{
    std::vector<int> no;
    std::vector<int> temp;
    tablePage *tbpg = new tablePage;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j;
    int p = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage("./database/data/" + std::string(tableName), i);
        tbpg->readTablePage(pgdata, tbif);

        temp = tbpg->conditionsearch(attr, op, attrno, p);
        no.insert(no.end(), temp.begin(), temp.end());
        p += tbpg->tupleNum;
    }
    delete tbpg;
    return no;
}

std::vector<Tuple>
RecordManager::nonConditionSelect(char *tableName,
                                  TableInfo tbif) //参数：表名,存放数组，tableinfo；返回全部tuple
{
    std::vector<Tuple> tup;
    std::vector<Tuple> temp;
    tablePage *tbpg = new tablePage;
    int pgNum = getPageNum(tableName);
    char *pgdata;
    int i, j;
    int count = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = buffer.getPage("./database/data/" + std::string(tableName), i);
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
        pgdata = buffer.getPage("./database/data/" + std::string(tableName), i);
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
    std::string name;
    name = tableName;
    char *p;
    int block_num = -1;
    do {
        p = buffer.getPage("./database/data/" + std::string(name), block_num + 1);
        block_num++;
    } while (p[0] != '\0');
    if (block_num == 0) block_num = 1;
    return block_num;
}
