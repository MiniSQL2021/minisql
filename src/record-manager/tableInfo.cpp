/*
68+72n�ֽ�
	�� 4�ֽ� int
	���� 28�ֽ�
	������4�ֽ� int
		
		����һ��72�ֽ�
		{����30�ֽ� char��
		��������4�ֽ� int��
		�Ƿ�unique 1�ֽ� char��
		��������1�ֽ� char��
		������ 32�ֽ� char��
		���Գ� 4�ֽ� int
		 }
		���Զ�������
	primarykey���� 1�ֽ� char
	primarykey��31�ֽ� char*/
#include "tableInfo.h"

tableInfo::tableInfo()
{
	int i, j;
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 31; j++)
		{
			attrName[i][j] = '\0';
			indexName[i][j] = '\0';
		}
		attrType[i] = AttributeType::UNDEFINE;
		hasIndex[i] = false;
		attrLength[i] = 0;

	}
	attrNum = 0;
	dataLength = 0;
}
tableInfo::tableInfo(const tableInfo& tbif)
{
	strcpy_s(primaryKey, tbif.primaryKey);
	strcpy_s(TableName, tbif.TableName);
	memcpy(&hasPrimaryKey, &tbif.hasPrimaryKey, 1);
	memcpy(&attrNum, &tbif.attrNum, 4);

	int i;
	for (i = 0; i < attrNum; i++)
	{
		strcpy_s(attrName[i], tbif.attrName[i]);
		memcpy(attrType + i, tbif.attrType + i, 4);
		memcpy(attrUnique + i, tbif.attrUnique + i, 1);
		memcpy(hasIndex + i, tbif.hasIndex + i, 1);
		strcpy_s(indexName[i], tbif.indexName[i]);
		attrLength[i] = tbif.attrLength[i];
	}

	memcpy(&dataLength, &tbif.dataLength, 4);
	strcpy_s(rowData, tbif.rowData);
}
tableInfo::~tableInfo() {};

void tableInfo::setTableInfo(char* tbn, char* pn, bool hp, int an, attrStruct* atrs)		
{
	strcpy_s(TableName, tbn);
	strcpy_s(primaryKey, pn);
	hasPrimaryKey = hp;
	attrNum = an;
	dataLength = 69 + 72 * attrNum;


	int i;
	for (i = 0; i < attrNum; i++)
	{
		strcpy_s(attrName[i], (atrs+i)->attrName);
		memcpy(attrType + i, &(atrs + i)->attrType,4);
		memcpy(attrUnique + i, &(atrs + i)->attrUnique,1);
		memcpy(hasIndex + i, &(atrs + i)->hasIndex, 1);
		strcpy_s(indexName[i], (atrs + i)->indexname);
		attrLength[i] = (atrs + i)->attrlength;
	}
	insertRowData();
}

int tableInfo::searchAttr(char* attrname)
{
	int i;
	for (i = 0; i < attrNum; i++)
	{
		if (strcmp(attrname, attrName[i]))
		{
			return i;
		}
	}
	if (i >= attrNum) {
		throw;				//attr does not exist
	}
}



void tableInfo::insertRowData()
{

	int i,p=0;
	memcpy(rowData, &dataLength, 4);
	p += 4;
	memcpy(rowData+p, TableName,28);
	p += 28;
	memcpy(rowData+p, &attrNum, 4);
	p += 4;
	for (i = 0; i < attrNum; i++)
	{
		memcpy(rowData+p, attrName[i],30);
		p += 30;
		memcpy(rowData+p, attrType + i,4);
		p += 4;
		memcpy(rowData+p, attrUnique+i,1);
		p += 1;
		memcpy(rowData+p, hasIndex+i,1 );
		p += 1;
		memcpy(rowData + p, indexName[i], 32);
		p += 32;
		memcpy(rowData + p, attrLength + i, 4);
		p += 4;
	}
	memcpy(rowData + p, &hasPrimaryKey, 1);
	p += 1;
	memcpy(rowData + p, primaryKey, 31);
	p += 31;
	char a = '#';
	memcpy(rowData + p, &a, 1);
}

void tableInfo::getFromRowData()
{
	int i, p = 0;
	memcpy( &dataLength,rowData, 4);
	p += 4;
	memcpy(TableName + p,rowData , 28);
	p += 28;
	memcpy(&attrNum, rowData + p,4);
	p += 4;
	for (i = 0; i < attrNum; i++)
	{
		memcpy( attrName[i], rowData + p, 30);
		p += 30;
		memcpy( attrType + i, rowData + p, 4);
		p += 4;
		memcpy( attrUnique + i, rowData + p, 1);
		p += 1;
		memcpy(hasIndex + i, rowData + p, 1);
		p += 1;
		memcpy( indexName[i], rowData + p, 32);
		p += 32;
		memcpy( attrLength + i, rowData + p, 4);
		p += 4;
	}
	memcpy(&hasPrimaryKey, rowData + p, 1);
	p += 1;
	memcpy(primaryKey, rowData + p, 31);
}
