#include"Attribute.h"



Attribute::Attribute()
{
	dataLength = 0;
	type = AttributeType::UNDEFINE;
	intData = 0;
	floatData = 0.0;
}
Attribute::~Attribute() {}
Attribute::Attribute(const Attribute& attr)
{
	this->dataLength = attr.dataLength;
	this->type = attr.type;
	this->intData = attr.intData;
	this->floatData = attr.floatData;
	strcpy_s(charData, attr.charData);
	strcpy_s(rowData, attr.rowData);
}

void Attribute::getRowData()			//��attribute���е��뵽rowData��
{
	assert(type != AttributeType::UNDEFINE);
	switch (type)
	{
	case AttributeType::INT: {
		dataLength = sizeof(intData);
		memcpy(rowData, &intData, dataLength);
		break;
	}
	case AttributeType::FLOAT: {
		dataLength = sizeof(floatData);
		memcpy(rowData, &floatData, dataLength);
		break;
	}
	case AttributeType::CHAR: {
											//dataLength���⸳ֵ
		strcpy_s(rowData, charData);
		break;
	}
	default:
		break;
	}
}

void Attribute::releaseRowData()		//��rowData������attribute��,����dataLength��ֵ
{
	switch (type)
	{
	case AttributeType::INT: {
		dataLength = sizeof(int);
		memcpy(&intData, rowData, dataLength);
		break;
	}
	case AttributeType::FLOAT: {
		dataLength = sizeof(float);
		memcpy(&floatData,rowData, dataLength);
		break;
	}
	case AttributeType::CHAR: {
		dataLength = sizeof(rowData);
		strcpy_s(charData, rowData);
		break;
	}
	default:
		break;
	}
}
int Attribute::compare(const Attribute& attr)  //�Ƚ����ݴ�С�������������������
{
	assert(type != AttributeType::UNDEFINE);
	switch (type)
	{
	case AttributeType::INT: {
		if (intData > attr.intData)
		{
			return 1;
		}
		else if (intData == attr.intData) {
			return 0;
		}
		else {
			return -1;
		}
		break;
	}
	case AttributeType::FLOAT: {
		if (floatData > attr.floatData)
		{
			return 1;
		}
		else if (floatData == attr.floatData) {
			return 0;
		}
		else {
			return -1;
		}
		break;
	}
	case AttributeType::CHAR: {
		return strcmp(charData, attr.charData);
		break;
	}
	default:
		break;
	}
}
	int Attribute::getDataLength()
	{
		switch (type) {
		case AttributeType::CHAR:
			return dataLength;
			break;
		case AttributeType::INT:
			return sizeof(int);
			break;
		case AttributeType::FLOAT:
			return sizeof(float);
			break;
		case AttributeType::UNDEFINE:
			return 0;
			break;
		default:
			break;
		}
	}

	bool Attribute::operator <  (const Attribute& attr) {
		return compare(attr) < 0;
	}

	bool Attribute::operator == (const Attribute& attr) {
		return compare(attr) == 0;
	}

	bool Attribute::operator != (const Attribute& attr) {
		return compare(attr) != 0;
	}

	bool Attribute::operator >  (const Attribute& attr) {
		return compare(attr) > 0;
	}

	bool Attribute::operator <= (const Attribute& attr) {
		return (*this < attr) || (*this == attr);
	}

	bool Attribute::operator >= (const Attribute& attr) {
		return (*this > attr) || (*this == attr);
	}

	int Attribute::getOperator(char* op)
	{
		if (strcmp(op, "<"))
		{
			return 0;
		}
		else if (strcmp(op, "<=")==0)
		{
			return 1;
		}
		else if (strcmp(op, ">") == 0)
		{
			return 2;
		}
		else if (strcmp(op, ">=") == 0)
		{
			return 3;
		}
		else if (strcmp(op, "==") == 0)
		{
			return 4;
		}
		else if (strcmp(op, "!=") == 0)
		{
			return 5;
		}
		
	}