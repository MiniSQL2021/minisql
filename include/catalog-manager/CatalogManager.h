//ʵ�ִ�����ɾ����������Щ��ϵģʽ
//�������ԡ������ȹ�ϵģʽ�Ƿ���ڡ�������ɾʱ���鱨��
//�̳�catalogPage���������ݴ���

#ifndef CatalogManager
#define CatalogManager
//ʵ�ֹ�ϵģʽ�Ĵ�����ã��ṩ����


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

	bool checkTable(char*);			//���������������table�Ƿ����
	bool checkIndex(char*);			//�����������������������table��attr���Ƿ��������
	bool checkAttr(char*, char*);	    //����������������������������Ƿ����
	bool checkUnique(char*, char*);	//����������������������������Ƿ�unique
	bool checkPrimaryKey(char*);		//����������������Ƿ��������

	int getAttrNo(char*, char*);		//���������������������������ǵڼ�������
	AttributeType* getAttrType(char*, char*);	//��������������������������������
	tableInfo* getTableInfo(char*);    //���������������ر���Ϣ

	void dropTable(char*);				//������������ɾ��һ������ɾ���������
	void createTable(tableInfo);		//������tableInfo;��ʧ�ܴ�ӡ����
	void editIndex(char*, char*, int);	//��������������������1Ϊ������0Ϊɾ������

};

#endif // !CatalogManager
#pragma once
