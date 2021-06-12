//实现创建、删除表、索引这些关系模式
//检查表、属性、索引等关系模式是否存在、用于增删时候检查报错
//继承catalogPage，方便数据传递

#ifndef CatalogManager
#define CatalogManager
//实现关系模式的储存调用，提供函数


#include<iostream>
#include<string>
#include "tableInfo.h"
#include"Attribute.h"
#include"Page.h"
#include"catalogPage.h"
#include"buffer_manager.h"

using namespace std;

class catalogManager
{
public:
	BufferManager buffer;

	bool checkTable(char*);			//参数：表名；检查table是否存在
	bool checkIndex(char*);			//参数：表名，属性名；检查table的attr上是否存在索引
	bool checkAttr(char*, char*);	    //参数：表名，属性名；检查属性是否存在
	bool checkUnique(char*, char*);	//参数：表名，属性名；检查属性是否unique
	bool checkPrimaryKey(char*);		//参数：表名；检查是否存在主键

	int getAttrNo(char*, char*);		//参数：表名，属性名，返回这是第几个属性
	AttributeType* getAttrType(char*, char*);	//参数：表名，属性名；返回属性类型
	tableInfo* getTableInfo(char*);    //参数：表名；返回表信息

	void dropTable(char*);				//参数：表名；删除一个表，并删除表的索引
	void createTable(tableInfo);		//参数：tableInfo;若失败打印报错
	void editIndex(char*, char*, int);	//参数：表名，属性名，1为创建，0为删除索引

};

#endif // !CatalogManager
#pragma once
