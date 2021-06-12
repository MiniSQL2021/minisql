/*
	record�Ĵ��桢ɾ��������
*/
#ifndef tablePage_hpp

#include<iostream>
#include<string>
#include"Attribute.h"
#include"catalogPage.h"
#include"tuple.h"


using namespace std;

class tablePage
{
public:
	tablePage();
	~tablePage();
	
	char tableName[28]="";
	int tupleLength = 0;
	int tupleNum = 0;
	tableInfo tbif;		
	Tuple tp[1024];

	void conditionsearch(Attribute, char*, int attrno,int* no);			//������attr�������������ռ�����ֽڣ��ڶ����ֽڿ�Ϊ\0��;����tuple��Ŵ洢�ڴ����ָ����
	void nonconditionsearch(int* no);
	void insertTuple(char*, Tuple tup,int k);
	void deleteTuple(int *);
	int checkdelete();
	

	void writeTablePage(char* pagedata);	
	void readTablePage(char* pagedata, tableInfo tbinfo);
	


};

#endif // !tablePage_hpp

#pragma once
