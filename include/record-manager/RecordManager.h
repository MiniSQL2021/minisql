//实现数据文件的创建与删除（由表的定义与删除引起）、记录的插入、删除、查找操作，并对外提供相应的接口。
//其中记录的查找操作要求能够支持不带条件的查找和带一个条件的查找（包括等值查找、不等值查找和区间查找）


#ifndef RecordManager_hpp
#define RecordManager_hpp

#include<iostream>
#include<string>
#include"TableInfo.h"
#include"Attribute.h"
#include"tuple.h"
#include"tablePage.h"
#include"buffer_manager.h"
#include<vector>
#include "exception.h"

using namespace std;

class RecordManager {
public:
    BufferManager &buffer;

    RecordManager(BufferManager &bufferManager) : buffer(bufferManager) {};

    void createTable(char *tablename, TableInfo tbif);

    void deleteTable(char *tablename);

    int insertRecord(char *, Tuple, TableInfo);       //参数：表名，Tuple；向表中插入元组，插入失败则报错
    void deleteRecord(char *tableName, vector<int> no, TableInfo tbif);       //参数：表名，序号
    void deleteAllRecord(char *tableName, TableInfo tbif);

    vector<int> conditionSelect(char *tableName, int attrno, char *op, Attribute attr, TableInfo tbif);
    //参数：表名，属性序号（用catalog'的getattrNo），算数比较符，比较值, tbif


    vector<Tuple>
    nonConditionSelect(char *tableName, TableInfo tbif);                       //参数：表名,存放数组，tableinfo；返回全部tuple
    vector<Tuple> searchTuple(char *tableName, TableInfo tbif, vector<int> no);

    bool checkUnique(char *tableName, int attrno, Attribute attr,
                     TableInfo tbif);                            //参数：attrno由catalog中的checkattrno得到
    int getPageNum(char *tableName);
};

#endif // !record_hpp

