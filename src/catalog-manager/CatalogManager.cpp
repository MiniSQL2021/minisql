#include"CatalogManager.h"



bool catalogManager::checkTable(char* tableName)			//参数：表名；检查table是否存在
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


bool catalogManager::checkIndex(char* tableName)			//参数：表名；检查table是否存在索引
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
		if (n == -1)
		{
			continue;
		}
		for (j = 0; j < 32; j++)
		{
			if ((cgpage.tbif + n)->hasIndex[j]) { flag = true; }
		}
		
	}
	buffer.releasePage(pgdata);
	return flag;
	
}
bool catalogManager::checkAttr(char* tableName, char* attrnm)	    //参数：表名，属性名；检查属性是否存在
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
		if (n == -1)
		{
			continue;
		}
		for (j = 0; j < 32; j++)
		{
			if (strcmp((cgpage.tbif + n)->attrName[j], attrnm) == 0) { flag = 1; }
		}
		
	}
	buffer.releasePage(pgdata);
	return flag;
}
bool catalogManager::checkUnique(char* tableName, char*)	//参数：表名，属性名；检查属性是否unique
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
		if (n == -1)
		{
			continue;
		}
		for (j = 0; j < 32; j++)
		{
			if ((cgpage.tbif + n)->attrUnique[j]) { flag = true; }
		}
	
	}
	buffer.releasePage(pgdata);
	return flag;
}
bool catalogManager::checkPrimaryKey(char* tableName)		//参数：表名；检查是否存在主键
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
		if (n == -1)
		{
			continue;
		}
		flag=(cgpage.tbif + n)->hasPrimaryKey;
		
	}
	buffer.releasePage(pgdata);
	return flag;
}

int catalogManager::getAttrNo(char* tableName, char* attrname)
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


AttributeType* catalogManager::getAttrType(char* tableName, char* attrname)	//参数：表名，属性名；返回属性类型
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
	return (cgpage.tbif + n)->attrType;
}
tableInfo* catalogManager::getTableInfo(char* tableName)   //参数：表名；返回表信息
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
			continue;
		}
	}
	buffer.releasePage(pgdata);
	if(i!=pgNum){ return (cgpage.tbif + n); }
	else
	{
		throw table_does_not_exist;
	}
	
}

void catalogManager::dropTable(char* tableName)				//参数：表名；删除一个表，并删除表的索引
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
		if (n == -1)
		{
			continue;
		}
		cgpage.deleteTable(pgdata, n);
	}
	buffer.releasePage(pgdata);
	
}
void catalogManager::createTable(tableInfo tbif)		//参数：tableInfo;若失败打印报错
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


void catalogManager::editIndex(char* tableName, char* attrnm, int flag)
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
		if (n == -1)
		{
			continue;
		}
		num = (cgpage.tbif + n)->attrNum;
		j = (cgpage.tbif + n)->searchAttr(attrnm);
		if (flag)
		{
			(cgpage.tbif + n)->attrUnique[j] = true;
		}
		else {
			if ((cgpage.tbif + n)->hasIndex[j] == false)
			{
				throw index_does_not_exist;								//Index does not exisit
			}
			(cgpage.tbif + n)->attrUnique[j] = false;
		}
		cgpage.updatePage(pgdata, n);

	}
	buffer.releasePage(pgdata);
}
