//tableInfo��pagedata�Ĵ���
/*
catalogPage��ʽ �����������������ݶ���
����Ŀ4�ֽ� int
����Ϣ
*/

#ifndef pageData_hpp

#include<string>
#include<iostream>
#include"tableInfo.h"

using namespace std;

class CatalogPage     
{
public:
	CatalogPage();
	~CatalogPage();

	int tableNum=0;
	tableInfo tbif[50];
	int searchTableInfo(char*);


	void updatePage(char*, int i);		//������pageָ�룬���µı���š����±�
	void writePage(char*);				//��ӱ�
	void readPage(char*);
	void deleteTable(char*,int i);
};


#endif // !pageData_hpp
    