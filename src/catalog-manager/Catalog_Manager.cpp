#include"Catalog_Manager.h"

CatalogManager::CatalogManager(BufferManager bm)
{
	buffer = bm;
}
CatalogManager::~CatalogManager() 
{
	buffer.~BufferManager();
}


bool CatalogManager::checkTable(char* tableName)			//���������������table�Ƿ����
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i;
	char* pgdata;
	int flag = 0;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		flag=cgpage.searchTableInfo(tableName);
		if (flag != -1)
		{
			buffer.releasePage(pgdata);
			return true;
		}
	}
	if (flag == -1)
	{
		buffer.releasePage(pgdata);
		return false;
	}
}


bool CatalogManager::checkIndex(char* tableName)			//���������������table�Ƿ��������
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i ,j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}		
	}
	if (i == pgNum)
	{
		buffer.releasePage(pgdata);
		throw table_does_not_exist;
	}
	for (j = 0; j < cgpage.tbif[n].attrNum; j++)
	{
		if ((cgpage.tbif + n)->hasIndex[j]) { flag = true; }
	}
	buffer.releasePage(pgdata);
	return flag;
	
}
bool CatalogManager::checkIndex(char* tableName, char* attrname)	//�������������������������������Ƿ���Index
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}
	}
	if (i == pgNum)
	{
		buffer.releasePage(pgdata);
		throw table_does_not_exist;
	}
	for (j = 0; j < cgpage.tbif[n].attrNum; j++)
	{
		if ((cgpage.tbif + n)->hasIndex[j] && strcmp((cgpage.tbif + n)->attrName[j], attrname) == 0)
		{
			flag = true;
		}
	}
	if (j == cgpage.tbif[n].attrNum)
	{
		buffer.releasePage(pgdata);
		throw attr_does_not_exist;
	}
	buffer.releasePage(pgdata);
	return flag;

}
string CatalogManager::searchIndex(char* indexname)			//������IndexName���������ڵı�
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j,m;
	char* pgdata;
	int n;
	string str;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		m = cgpage.tableNum;
		for (n = 0; n < m; n++)
		{
			for (j = 0; j < cgpage.tbif[n].attrNum; j++)
			{
				if (strcmp((cgpage.tbif + n)->indexName[j],indexname)==0)
				{
					str.append((cgpage.tbif + n)->TableName);
					str += '/n';
					str.append((cgpage.tbif + n)->indexName[j]);
					buffer.releasePage(pgdata);
					return str;
				}
			}
		}
	}
	if (i == pgNum)
	{
		throw index_does_not_exist;
	}

}

bool CatalogManager::checkAttr(char* tableName, char* attrnm)	    //����������������������������Ƿ����
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}	
	}
	if (i == pgNum)
	{
		buffer.releasePage(pgdata);
		throw table_does_not_exist;
	}
	for (j = 0; j < cgpage.tbif[n].attrNum; j++)
	{
		if (strcmp((cgpage.tbif + n)->attrName[j], attrnm) == 0) { flag = 1; }
	}
	buffer.releasePage(pgdata);
	return flag;
}
bool CatalogManager::checkUnique(char* tableName, char*)	//����������������������������Ƿ�unique
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}	
	}
	if (i == pgNum)
	{
		buffer.releasePage(pgdata);
		throw table_does_not_exist;
	}
	for (j = 0; j < cgpage.tbif[n].attrNum; j++)
	{
		if ((cgpage.tbif + n)->attrUnique[j]) { flag = true; }
	}
	if (j == cgpage.tbif[n].attrNum)
	{
		buffer.releasePage(pgdata);
		throw attr_does_not_exist;
	}
	buffer.releasePage(pgdata);
	return flag;
}

int CatalogManager::getAttrNo(char* tableName, char* attrname)
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}
		
	}
	if (i == pgNum)
	{
		buffer.releasePage(pgdata);
		throw table_does_not_exist;
	}
	for (j = 0; j < cgpage.tbif[n].attrNum; j++)
	{
		if (strcmp(cgpage.tbif[n].attrName[j], attrname) == 0)
		{
			buffer.releasePage(pgdata);
			return j;
		}
	}
	if (j == cgpage.tbif[n].attrNum)
	{
		buffer.releasePage(pgdata);
		throw attr_does_not_exist;
	}
}


AttributeType CatalogManager::getAttrType(char* tableName, char* attrname)	//��������������������������������
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}
	}
	if (i == pgNum)
	{
		buffer.releasePage(pgdata);
		throw table_does_not_exist;
	}

	for (j = 0; j < cgpage.tbif[n].attrNum; j++)
	{
		if (strcmp((cgpage.tbif + n)->attrName[j], attrname) == 0)
		{
			return (cgpage.tbif + n)->attrType[j];
		}
	}
	if (j == cgpage.tbif[n].attrNum)
	{
		buffer.releasePage(pgdata);
		throw attr_does_not_exist;
	}

}
	

TableInfo CatalogManager::getTableInfo(char* tableName)   //���������������ر���Ϣ
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}
	}
	buffer.releasePage(pgdata);
	if(i!=pgNum)
	{ 
		
		return *(cgpage.tbif + n);
	}
	else
	{
		throw table_does_not_exist;
	}
	
}

void CatalogManager::dropTable(char* tableName)				//������������ɾ��һ��������ɾ����������
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}
	}
	if(i==pgNum)
	{ 
		buffer.releasePage(pgdata); 
		throw table_does_not_exist; 
	}
	cgpage.deleteTable(pgdata, n);
	buffer.releasePage(pgdata);

	
}
void CatalogManager::createTable(TableInfo tbif)		//������TableInfo;��ʧ�ܴ�ӡ����
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j ,k=0;
	char* pgdata;
	bool flag = false;
	int n = -1;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		if (strlen(pgdata) + tbif.dataLength > 4096)
		{
			continue;
		}
		else
		{
			cgpage.tableNum++;
			*(cgpage.tbif + cgpage.tableNum) = tbif;
			cgpage.writePage(pgdata);
		}
	}
	if (i == pgNum)
	{
		buffer.addCatalogPage();
		pgdata = buffer.getCatalogPage(i);
		memcpy(pgdata, &k, 4);
		cgpage.readPage(pgdata);
		cgpage.tableNum++;
		*(cgpage.tbif + cgpage.tableNum) = tbif;
		cgpage.writePage(pgdata);
	}
	buffer.releasePage(pgdata);
}

void CatalogManager::createIndex(char* tableName, char* attrName, char* indexName)	
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j;
	char* pgdata;
	bool flag = false;
	int n = -1;
	int num;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		n = cgpage.searchTableInfo(tableName);
		if (n != -1)
		{
			break;
		}
	}

	if (i == pgNum) 
	{ 
		buffer.releasePage(pgdata);
		throw table_does_not_exist;
	}
	num = (cgpage.tbif + n)->attrNum;
	j = (cgpage.tbif + n)->searchAttr(attrName);
	if ((cgpage.tbif + n)->attrUnique[j] == false)
	{
		buffer.releasePage(pgdata);
		throw attr_does_not_unique;
	}
	if ((cgpage.tbif + n)->hasIndex[j])
	{
		buffer.releasePage(pgdata);
		throw index_already_exist;
	}
	(cgpage.tbif + n)->hasIndex[j] = true;
	memcpy((cgpage.tbif + n)->indexName[j], indexName, 32);

	cgpage.updatePage(pgdata, n);
	buffer.releasePage(pgdata);
}
void CatalogManager::deleteIndex(char* indexName)	//������indexName��ɾ��index��ʧ���򱨴���index_does_not_exist
{
	CatalogPage cgpage;
	int pgNum = buffer.getCatalogPageNum();
	int i, j, m;
	char* pgdata;
	int n;
	char nul[32] = {};
	string str;
	for (i = 0; i < pgNum; i++)
	{
		pgdata = buffer.getCatalogPage(i);
		cgpage.readPage(pgdata);
		m = cgpage.tableNum;
		for (n = 0; n < m; n++)
		{
			for (j = 0; j < cgpage.tbif[n].attrNum; j++)
			{
				if (strcmp((cgpage.tbif + n)->indexName[j], indexName) == 0)
				{
					(cgpage.tbif + n)->hasIndex[j] = false;
					memcpy((cgpage.tbif + n)->indexName, nul, 32);
					cgpage.updatePage(pgdata, n);
					buffer.releasePage(pgdata);
				}
			}
		}
	}
	if (i == pgNum)
	{
		buffer.releasePage(pgdata);
		throw index_does_not_exist;
	}
}