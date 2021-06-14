/*
	record的储存、删除、更新
*/
#ifndef tablePage_hpp

#include<iostream>
#include<string>
#include"Attribute.h"
#include"catalogPage.h"
#include"tuple.h"
#include<vector>

using namespace std;

class tablePage {
public:
    tablePage();

    ~tablePage();

    char tableName[28] = "";
    int tupleLength = 0;
    int tupleNum = 0;
    TableInfo tbif;
    Tuple tp[1024];

    vector<int> conditionsearch(Attribute, char *, int attrno,
                                int p);            //参数：attr，算术运算符：占两个字节（第二个字节可为\0）;返回tuple编号存储在传入的指针中
    vector<Tuple> nonconditionsearch();

    vector<Tuple> searchTuple(vector<int>);

    void insertTuple(char *, Tuple tup, int k);

    void deleteTuple(int *);

    int checkdelete();

    void writeTablePage(char *pagedata);

    void readTablePage(char *pagedata, TableInfo tbinfo);

};

#endif // !tablePage_hpp

#pragma once
