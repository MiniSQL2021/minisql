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
#include "exception.h"

class tablePage {
public:
    tablePage();

    ~tablePage();

    char tableName[28] = "";
    int tupleLength = 0;
    int tupleNum = 0;
    TableInfo tbif;
    Tuple tp[1024];

    std::vector<int> conditionsearch(
            Attribute, char *, int attrno,
            int p); //参数：attr，算术运算符：占两个字节（第二个字节可为\0）;返回tuple编号存储在传入的指针中
    std::vector<Tuple> nonconditionsearch();

    std::vector<Tuple> searchTuple(std::vector<int>);

    int insertTuple(char *, Tuple tup, int k);

    void deleteTuple(char *, std::vector<int>);

    int checkdelete();

    void writeTablePage(char *pagedata);

    void readTablePage(char *pagedata, TableInfo tbinfo);

};

#endif // !tablePage_hpp

#pragma once
