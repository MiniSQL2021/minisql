#include"catalogPage.h"

CatalogPage::CatalogPage() {};
CatalogPage::~CatalogPage() {};


int CatalogPage::searchTableInfo(char* tbnm)
{
	int i,flag=0;
	for (i = 0; i < tableNum; i++)
	{
		if (strcmp((tbif+i)->TableName, tbnm) == 0)
		{
			return i;
			flag = 1;
		}
	}
	if (!flag)
	{
		return -1;
	}
}




void CatalogPage::writePage(char* pagedata)
{
	int i;
	memcpy(pagedata, &tableNum, 4);
	strncat(pagedata, (tbif + tableNum - 1)->rowData, (tbif + tableNum - 1)->dataLength);
}


void CatalogPage::updatePage(char* pagedata,int i)
{
	int p = 4,j;
	for (j = 0; j < i; j++)
	{
		p += 68;
		p += 36 * tbif->attrNum;
	}
	memcpy(pagedata+p, (tbif + i)->rowData, (tbif + i)->dataLength);
}
void CatalogPage::readPage(char* pagedata)
{
	int i;
	int size=0;
	int p = 4;
	memcpy(&tableNum, pagedata, 4);
	char* rowdata[50];
	for (i = 0; i < tableNum; i++)
	{
		memcpy(&size, pagedata + p, 4);
		memcpy((tbif + i)->rowData, pagedata + p, size);
		p += size;
		(tbif + i)->getFromRowData();
	}
}

void CatalogPage::deleteTable(char* pagedata, int i)
{
	int j;
	char temp[4096]="";
	int size = 0;
	int p=4;
	
	for (j = 0; j <= i; j++)
	{
		memcpy(&size, pagedata + p, 4);
		p += size;
	}//p指向所删数组后一个的位置
	memcpy(temp, pagedata + p, 4097 - p);
	memcpy(pagedata+p-size, temp, 4097 - p+size);
	
}