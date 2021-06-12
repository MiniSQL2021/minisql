//ʵ�������ļ��Ĵ�����ɾ�����ɱ�Ķ�����ɾ�����𣩡���¼�Ĳ��롢ɾ�������Ҳ������������ṩ��Ӧ�Ľӿڡ�
//���м�¼�Ĳ��Ҳ���Ҫ���ܹ�֧�ֲ��������Ĳ��Һʹ�һ�������Ĳ��ң�������ֵ���ҡ�����ֵ���Һ�������ң�


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

class RecordManager 
{
	BufferManager buffer;
	RecordManager();
	~RecordManager();

	void createTable(char* tablename,tableInfo tbif);
	void deleteTable(char* tablename);
	
	void insertRecord(char*, Tuple,tableInfo);	   //������������Tuple������в���Ԫ�飬����ʧ���򱨴�
	void deleteRecord(char* tableName, int attrno, char* op, Attribute attr, tableInfo tbif);	   //������ͬselect������Ҫtup
	void conditionSelect(char* , int, char*, Attribute, tableInfo tbif, Tuple* tup);
	//������������������ţ���catalog'��getattrNo���������ȽϷ����Ƚ�ֵ, tbif
	//����ֵ��tuple���鴫��
	void nonconditionSelect(char*, Tuple* tup, tableInfo tbif);                       //����������,������飬tableinfo������ȫ��tuple

	bool checkUnique(char* tablename, int attrno, Tuple tup, tableInfo tbif);					    	//������attrno��catalog�е�checkattrno�õ�

};

#endif // !record_hpp

