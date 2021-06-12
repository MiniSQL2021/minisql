//实现数据文件的创建与删除（由表的定义与删除引起）、记录的插入、删除、查找操作，并对外提供相应的接口。
//其中记录的查找操作要求能够支持不带条件的查找和带一个条件的查找（包括等值查找、不等值查找和区间查找）


#ifndef RecordManager_hpp
#define RecordManager_hpp

#include<iostream>
#include<string>
#include"tableInfo.h"
#include"Attribute.h"
#include"tuple.h"
#include"CatalogManager.h"
#include"tablePage.h"
#include"buffer_manager.h"

using namespace std;

class RecordManager {
    BufferManager buffer;

    RecordManager();

    ~RecordManager();

    void createTable(char *tablename, tableInfo tbif);

    void deleteTable(char *tablename);

    void insertRecord(char *, Tuple, tableInfo);       //参数：表名，Tuple；向表中插入元组，插入失败则报错
    void deleteRecord(char *tableName, int attrno, char *op, Attribute attr, tableInfo tbif);       //参数：同select，不需要tup
    void conditionSelect(char *, int, char *, Attribute, tableInfo tbif, Tuple *tup);

    //参数：表名，属性序号（用catalog'的getattrNo），算数比较符，比较值, tbif
    //返回值由tuple数组传出
    void nonconditionSelect(char *, Tuple *tup, tableInfo tbif);                       //参数：表名,存放数组，tableinfo；返回全部tuple

    bool checkUnique(char *tablename, int attrno, Tuple tup,
                     tableInfo tbif);                            //参数：attrno由catalog中的checkattrno得到

};

#endif // !record_hpp

