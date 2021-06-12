//����������Ϣ������������ֵ�ıȽ�������\�ṩ���Դ���ת������ʱ����

#ifndef Attribute_hpp
#define Attribute_hpp

#include <iostream>
#include <string>
#include <math.h>
#include<vector>
#include<cassert>

using namespace std;

enum class AttributeType
{
	INT = 0, 
	FLOAT,
	CHAR, 
	UNDEFINE,
};
class Attribute
{
public:
	int dataLength;               //��������
	AttributeType type;
	int intData;
	float floatData;
	char  charData[255]="";
	char  rowData[255]="";


	Attribute();
	~Attribute();
	Attribute(const Attribute&);

	void getRowData();			//��attribute���е��뵽rowData��ת��Ϊchar����
	void releaseRowData();		//��rowData������attribute��ת��Ϊԭ��������
	int compare(const Attribute&);  //�Ƚ����ݴ�С�������������������
	int getDataLength();        //�������ݳ���

	bool operator <  (const Attribute& attr);
	bool operator == (const Attribute& attr);
	bool operator != (const Attribute& attr);
	bool operator >  (const Attribute& attr);
	bool operator <= (const Attribute& attr);
	bool operator >= (const Attribute& attr);

	int getOperator(char*);
};






#endif //Attribute_hpp

