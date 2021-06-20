//元组作为插入媒介，包含行记录中每个data对应的attribute，以及要插入的表名

#ifndef tuple_hpp
#define tuple_hpp

#include<string>
#include<iostream>
#include"Attribute.h"
#include"TableInfo.h"
#include"exception.h"
#include<vector>

class Tuple {
public:
    Tuple();

    ~Tuple();

    Tuple(const Tuple &);

    Attribute attr[32];        //元组中的属性数组
    int attrNum;            //元组中属性数
    bool hasdeleted = false;

    char rowData[4096] = "";                 //元组记录的格式化，用于存入page

    void readRowData(char *RowData, TableInfo);

    void setTuple(int attrnum, std::vector<Attribute>, TableInfo tbif);

    void setRowData();
};

#endif // !tuple_hpp
