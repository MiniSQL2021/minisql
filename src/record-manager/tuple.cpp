#include"tuple.h"

Tuple::Tuple()
{
	attrNum = 0;
}
Tuple::~Tuple() {};
Tuple::Tuple(const Tuple&tp)
{
	int i;
	hasdeleted = tp.hasdeleted;
	attrNum = tp.attrNum;
	for (i = 0; i < attrNum; i++)
	{
		attr[i] = tp.attr[i];
	}
	strcpy_s(rowData, tp.rowData);
}


void Tuple::insertAttr(int num, Attribute* at)
{
	attrNum = num;

	int i;
	for (i = 0; i < attrNum; i++)
	{
		this->attr[i] = *(at + i);		//拷贝构造
		strcat(rowData,attr[i].rowData);

	}
}

void Tuple::writeRowData(char* pageRowData)
{
	memcpy(pageRowData, &hasdeleted, 1);
	int i;
	for (i = 0; i < attrNum; i++)
	{
		
		switch (attr[i].type)
		{
		case AttributeType::INT: {
			attr[i].getRowData();
			strncat( pageRowData, attr[i].rowData, 4);
			break;
		}
		case AttributeType::FLOAT: {
			attr[i].getRowData();
			strncat( pageRowData, attr[i].rowData, 4);
			break;
		}
		case AttributeType::CHAR: {
			attr[i].getRowData();
			strncat( pageRowData, attr[i].rowData, attr[i].dataLength);
			break;
		}
		}
	}
}

void Tuple::readRowData(char* RowData, TableInfo tbif)	 
	
{
	memcpy( &hasdeleted, RowData, 1);
	attrNum = tbif.attrNum;
	int i;
	for (i = 0; i < attrNum; i++)
	{
		attr[i].dataLength = tbif.dataLength;
		switch (tbif.attrType[i])
		{
		case AttributeType::INT: {
			attr[i].type = AttributeType::INT;
			strncpy_s(attr[i].rowData, RowData, 4);
			attr[i].releaseRowData();
			break;
		}
		case AttributeType::FLOAT: {
			attr[i].type = AttributeType::FLOAT;
			strncpy_s(attr[i].rowData, RowData, 4);
			attr[i].releaseRowData();
			break;
		}
		case AttributeType::CHAR: {
			attr[i].type = AttributeType::CHAR;
			strncpy_s(attr[i].rowData, RowData, attr[i].dataLength);
			attr[i].releaseRowData();
			break;
		}
		}
	}
}

void Tuple::setTuple(int attrnum, char** rowdata,TableInfo tbif)  
//参数*rowdata：（4字节 attrType）数据
{
	attrNum = attrnum;
	int i;
	AttributeType attrtyp[32] = {};
	for (i = 0; i < attrNum; i++)
	{
		if (*(tbif.attrType + i) != attrtyp[i])
		{
			throw illegal_data;
		}
		if (*(tbif.attrLength + i) < strlen(*(rowdata + i)))
		{
			throw illegal_data;
		}

		strcpy((attr + i)->rowData, *(rowdata + i) + 4);
		(attr + i)->releaseRowData();
	}
}

