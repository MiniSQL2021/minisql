//TableInfo和pagedata的传递
/*
catalogPage格式 ：不定长、单个数据定长
表数目4字节 int
表信息
*/

#ifndef pageData_hpp
#define pageData_hpp

#include<string>
#include<iostream>
#include"TableInfo.h"
#include "exception.h"

using namespace std;

class CatalogPage {
public:
    CatalogPage();

    ~CatalogPage();

    int tableNum = 0;
    TableInfo tbif[50];

    int searchTableInfo(char *);

    void updatePage(char *, int i);        //参数：page指针，更新的表序号。更新表
    void writePage(char *);                //添加表
    void readPage(char *);

    void deleteTable(char *, int i);
};

#endif // !pageData_hpp
