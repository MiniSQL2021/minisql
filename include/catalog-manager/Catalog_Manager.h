//实现创建、删除表、索引这些关系模式
//检查表、属性、索引等关系模式是否存在、用于增删时候检查报错
//继承catalogPage，方便数据传递

#ifndef Catalog_Manager
#define Catalog_Manager
//实现关系模式的储存调用，提供函数


#include<iostream>
#include<string>
#include "TableInfo.h"
#include"Attribute.h"
#include"Page.h"
#include"catalogPage.h"
#include"buffer_manager.h"

using namespace std;

class CatalogManager {
public:
    CatalogManager(BufferManager);

    ~CatalogManager();

    BufferManager buffer;

    bool checkTable(char *);

    //参数：表名；检查table是否存在
    bool checkIndex(char *);

    //参数：表名；检查table是否存在索引
    //table_does_not_exist
    bool checkIndex(char *, char *);

    //参数：表名，属性名；检查该属性上是否有Index
    //table_does_not_exist
    //attr_does_not_exist
    std::pair<char *, char *> searchIndex(char *);

    //参数：IndexName；返回值：“表名 /n 属性名”
    //index_does_not_exist
    bool checkAttr(char *, char *);

    //参数：表名，属性名；检查属性是否存在
    //table_does_not_exist
    bool checkUnique(char *, char *);
    //参数：表名，属性名；检查属性是否unique
    //table_does_not_exist
    //attr_does_not_exist

    int getAttrNo(char *, char *);

    //参数：表名，属性名，返回这是第几个属性
    //table_does_not_exist
    //attr_does_not_exist
    AttributeType getAttrType(char *, char *);

    //参数：表名，属性名；返回属性类型
    //table_does_not_exist
    //attr_does_not_exist
    TableInfo getTableInfo(char *);

    //参数：表名；返回表信息
    //table_does_not_exist
    void dropTable(char *);

    //参数：表名；删除一个表
    //table_does_not_exist
    void createTable(TableInfo);

    //参数：TableInfo;
    void createIndex(char *tableName, char *attrName, char *indexName);

    //table_does_not_exist
    //attr_does_not_exist
    //index_already_exist，
    //attr_does_not_unique
    void deleteIndex(char *indexName);
    //参数：indexName；删除index
    //index_does_not_exist

};

#endif // !Catalog_Manager
#pragma once
