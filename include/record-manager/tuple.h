//元组作为插入媒介，包含行记录中每个data对应的attribute，以及要插入的表名

#ifndef tuple_hpp
#define tuple_hpp

#include<string>
#include<iostream>
#include"Attribute.h"
#include"tableInfo.h"

using namespace std;

class Tuple
{
public:
	Tuple();
	~Tuple();
	Tuple(const Tuple&);

	Attribute attr[32];		//元组中的属性数组
	int attrNum;			//元组中属性数
	bool hasdeleted = false;

	void insertAttr(int num, Attribute* attr);      //插入属性,并将字符串插入
	

	char rowData[4096]="";				 //元组记录的格式化，用于存入page

	void writeRowData(char* pageRowData);	//写入rowdata；
	void readRowData(char* RowData,tableInfo);	 //同时对上层与下层
	void setTuple(int attrnum, char** rowdata, tableInfo tbif);
};


#endif // !tuple_hpp
