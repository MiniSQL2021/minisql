//Ԫ����Ϊ����ý�飬�����м�¼��ÿ��data��Ӧ��attribute���Լ�Ҫ����ı���

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

	Attribute attr[32];		//Ԫ���е���������
	int attrNum;			//Ԫ����������
	bool hasdeleted = false;

	void insertAttr(int num, Attribute* attr);      //��������,�����ַ�������
	

	char rowData[4096]="";				 //Ԫ���¼�ĸ�ʽ�������ڴ���page

	void writeRowData(char* pageRowData);	//д��rowdata��
	void readRowData(char* RowData,tableInfo);	 //ͬʱ���ϲ����²�
	void setTuple(int attrnum, char** rowdata, tableInfo tbif);
};


#endif // !tuple_hpp
