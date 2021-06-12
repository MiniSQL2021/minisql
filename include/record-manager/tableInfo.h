//储存表信息
//上层接口函数：setAttrInfo，setTableInfo。有报错

#ifndef tableInfo_hpp
#define tableInfo_hpp

#include<cstdio>
#include <string>
#include"Attribute.h"
using namespace std;

class tableInfo
{
public:
	tableInfo();
	tableInfo(const tableInfo&);
	~tableInfo();				
	void setTableInfo(char*, char*, bool,int,attrStruct*);				//参数：表名，主键名，有无主键，属性数,attrStruct属性数组

    char primaryKey[31]="";
	bool hasPrimaryKey=false;
	char TableName[28]="";
	int attrNum;
	
	char attrName[32][31];
	AttributeType attrType[32];
	bool attrUnique[32];
	bool hasIndex[32];
	char indexName[32][32];
	int attrLength[32];
	int searchAttr(char* attrname);

	int dataLength;											//指的是catalogPage的大小
	char rowData[1024]="";   
	void insertRowData();
	void getFromRowData();
};

struct attrStruct
{
	char* attrName;
	AttributeType attrType;
	bool attrUnique;
	bool hasIndex;
	char* indexname;
	int	attrlength;
};



#endif tableInfo_hpp

