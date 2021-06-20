/*
格式：
	tuple数目 4字节
	tuple长度 4字节
	tuple数组： tupleLength*tupleNum
*/
#include <cstring>

#include"tablePage.h"

tablePage::tablePage() {};

tablePage::~tablePage() {};

int tablePage::insertTuple(char *pagedata, Tuple tup, int k) {
    int p = k * tupleLength;
    int asw = 0;
    if (k == -1) {
        tp[tupleNum] = tup;
        tupleNum++;
        memcpy(pagedata, tup.rowData, tupleLength);
        asw = tupleNum;
    } else {
        tp[k] = tup;
        memcpy(pagedata + p, tup.rowData, tupleLength);
        asw = k + 1;
    }
    return asw;
}

void tablePage::deleteTuple(char *pagedata, std::vector<int> no) {
    int i, j = 0, flag = 0;
    int asw = 0;
    char null[4096] = "";
    bool f = true;
    memcpy(null, &f, 1);
    for (i = 0; i < no.size(); i++) {
        memcpy((tp + no[i])->rowData, null, tupleLength);
    }
    writeTablePage(pagedata);
}

std::vector<Tuple> tablePage::nonconditionsearch() {
    int i = 0;
    std::vector<Tuple> tup;

    for (; i < tupleNum; i++) {
        tup.push_back(*(tp + i));
    }
    return tup;
}

std::vector<Tuple> tablePage::searchTuple(std::vector<int> no) {
    int i = 0;
    int n = 0;
    std::vector<Tuple> tup;

    for (; i < no.size(); i++) {
        n = no[i];
        tup.push_back(*(tp + n));
    }
    return tup;
}

std::vector<int> tablePage::conditionsearch(Attribute attr, char *operater, int attrno,
                                            int p) //参数：attr，算术运算符,int attrno;返回tuple编号
{
    int i;
    std::vector<int> no;
    for (i = 0; i < tupleNum; i++) {

        switch (attr.getOperator(operater)) {
            case 0:
                if (*((tp + i)->attr + attrno) < attr) {
                    no.push_back(i + p);
                }
                break;
            case 1:
                if (*((tp + i)->attr + attrno) <= attr) {
                    no.push_back(i + p);
                }
                break;
            case 2:
                if (*((tp + i)->attr + attrno) > attr) {
                    no.push_back(i + p);
                }
                break;
            case 3:
                if (*((tp + i)->attr + attrno) >= attr) {
                    no.push_back(i + p);
                }
                break;
            case 4:
                if (*((tp + i)->attr + attrno) == attr) {
                    no.push_back(i + p);
                }
                break;
            case 5:
                if (*((tp + i)->attr + attrno) != attr) {
                    no.push_back(i + p);
                }
                break;

        }
    }
    return no;
}

void tablePage::writeTablePage(char *pagedata) {
    int i;
    memcpy(pagedata, &tupleNum, 4);
    memcpy(pagedata + 4, &tupleLength, 4);
    for (i = 0; i < tupleNum; i++) {
        strncat(pagedata, (tp + i)->rowData, tupleLength);

    }
}

void tablePage::readTablePage(char *pagedata, TableInfo tbinfo) {
    tbif = tbinfo;
    int i;
    memcpy(&tupleNum, pagedata, 4);
    memcpy(&tupleLength, pagedata + 4, 4);

    for (i = 0; i < tupleNum; i++) {
        (tp + i)->readRowData(pagedata + 8 + tupleLength * i, tbif);

    }
}

int tablePage::checkdelete() {
    int i;
    for (i = 0; i < tupleNum; i++) {
        if (tp[i].hasdeleted) {
            return i;
        }
    }
    return -1;

}
