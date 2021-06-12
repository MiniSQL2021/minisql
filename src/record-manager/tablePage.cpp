/*
格式：
	tuple数目 4字节
	tuple长度 4字节
	tuple数组： tupleLength*tupleNum
*/


#include"tablePage.h"

tablePage::tablePage() {};
tablePage::~tablePage() {};


void tablePage::insertTuple(char* pagedata, Tuple tup, int k)
{
	if (k == -1)
	{
		tp[tupleNum] = tup;
		tupleNum++;
		strncat_s(pagedata, 4096, tup.rowData, tupleLength);
	}
	else
	{
		tp[k] = tup;
		memcpy(pagedata+k*tupleLength, tup.rowData, tupleLength);
	}

}
void tablePage:: deleteTuple(int* no)
{
	int i, j = 0, flag = 0;
	for (i = 0; i < tupleNum; i++)
	{
		j = 0;
		flag = 0;
		while (*no)
		{
			if (*(no + j) == i) { flag = 1; }
			j++;
		}
		if(flag)
		{
			for (j = i; j < tupleNum; j++)
			{
				*(tp + j) = *(tp + j + 1);
			}
		}
	}


}



void tablePage::conditionsearch(Attribute attr, char* operater,int attrno,int* no)		//参数：attr，算术运算符,int attrno;返回tuple编号
{
	int i;
	for (i = 0; i < tupleNum; i++)
	{
		
		switch (attr.getOperator(operater))
		{
		case 0:
			if (*((tp + i)->attr + attrno) < attr)
			{
				*(no +1) = i + 1;
			}
			break;
		case 1:
			if (*((tp + i)->attr + attrno) <= attr)
			{
				*(no + 1) = i + 1;
			}
			break;
		case 2:
			if (*((tp + i)->attr + attrno) > attr)
			{
				*(no + 1) = i + 1;
			}
			break;
		case 3:
			if (*((tp + i)->attr + attrno) >= attr)
			{
				*(no + 1) = i + 1;
			}
			break;
		case 4:
			if (*((tp + i)->attr + attrno) == attr)
			{
				*(no + 1) = i + 1;
			}
			break;
		case 5:
			if (*((tp + i)->attr + attrno) != attr)
			{
				*(no + 1) = i + 1;
			}
			break;
		
		}
	}

}
void tablePage::nonconditionsearch(int* no)
{
	int i = 0;
	for (; i < tupleNum; i++)
	{
		*(no + i) = i+1;
	}
}


void tablePage::writeTablePage(char* pagedata)
{
	int i;
	memcpy(pagedata, &tupleNum, 4);
	memcpy(pagedata + 4, &tupleLength, 4);
	for (i = 0; i < tupleNum; i++)
	{
		strncat(pagedata, (tp + i)->rowData, tupleLength);

	}
}
void tablePage::readTablePage(char* pagedata,tableInfo tbinfo)
{
	tbif = tbinfo;
	int i;
	memcpy(&tupleNum, pagedata, 4);
	memcpy(&tupleLength, pagedata + 4, 4);

	for (i = 0; i < tupleNum; i++)
	{
		(tp + i)->readRowData(pagedata + 8 + tupleLength * i, tbif);

	}
}

int tablePage::checkdelete()
{
	int i; 
	for (i = 0; i < tupleNum; i++)
	{
		if (tp[i].hasdeleted)
		{
			return i;
		}
	}
	return -1;

}