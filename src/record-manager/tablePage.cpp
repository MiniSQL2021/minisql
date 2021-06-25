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
    int pN = tupleNum * tupleLength + 8;
    int asw = 0;
    if (k == -1) {
        tp[tupleNum] = tup;
        tupleNum++;
        memcpy(pagedata, &tupleNum, 4);
        memcpy(pagedata + pN, tup.rowData, tupleLength);
        asw = tupleNum-1;
    } else {
        tp[k] = tup;
        memcpy(pagedata + p, tup.rowData, tupleLength);
        asw = k;
    }
    return asw;
}

void tablePage::deleteTuple(char *pagedata, std::vector<int> no) {
    int i;
    bool flag = true;
    for (i = 0; i < no.size(); i++) {
        memcpy(pagedata + no[i] * tupleLength + 8, &flag, 1);
    }
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
        if ((tp + i)->hasdeleted) {
            continue;
        }
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
    int p = 8;
    for (i = 0; i < tupleNum; i++) {
        memcpy(pagedata + p, (tp + i)->rowData, tupleLength);
        p += tupleLength;
    }
}

void tablePage::readTablePage(char *pagedata, TableInfo tbinfo) {
    tbif = tbinfo;
    int i, p = 8;
    memcpy(&tupleNum, pagedata, 4);
    memcpy(&tupleLength, pagedata + 4, 4);

    for (i = 0; i < tupleNum; i++) {

        memcpy(tp[i].rowData, pagedata + p, tupleLength);
        p += tupleLength;
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
