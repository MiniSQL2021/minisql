#include <cstring>

#include"Catalog_Manager.h"

bool CatalogManager::checkTable(char *tableName)            //参数：表名；检查table是否存在
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i;
    char *pgdata;
    int flag = 0;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        flag = cgpage->searchTableInfo(tableName);
        if (flag != -1) {

            delete cgpage;
            return true;
        }
    }
    if (flag == -1) {

        delete cgpage;
        return false;
    }

}

bool CatalogManager::checkIndex(char *tableName, char *attrname)    //参数：表名，属性名；检查该属性上是否有Index
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }
    }
    if (i == pgNum) {

        delete cgpage;
        throw table_does_not_exist();
    }
    for (j = 0; j < (cgpage->tbif[n]).attrNum; j++) {
        if ((cgpage->tbif + n)->hasIndex[j] && strcmp((cgpage->tbif + n)->attrName[j], attrname) == 0) {
            flag = true;
            delete cgpage;
            return flag;

        }
    }
    if (j == cgpage->tbif[n].attrNum) {

        delete cgpage;
        throw attr_does_not_exist();
    }


}

std::pair<char *, char *>
CatalogManager::searchIndex(char *indexname) //参数：IndexName；返回所在的表
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j, m;
    char *pgdata;
    int n;
    std::string str;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        m = cgpage->tableNum;
        for (n = 0; n < m; n++) {
            for (j = 0; j < cgpage->tbif[n].attrNum; j++) {
                if (strcmp((cgpage->tbif + n)->indexName[j], indexname) == 0) {
                    delete cgpage;
                    return std::make_pair((cgpage->tbif + n)->TableName,
                                          (cgpage->tbif + n)->indexName[j]);
                }
            }
        }
    }
    if (i == pgNum) {
        delete cgpage;
        throw index_does_not_exist();
    }
}

bool CatalogManager::checkAttr(char *tableName, char *attrnm)        //参数：表名，属性名；检查属性是否存在
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }
    }
    if (i == pgNum) {
        delete cgpage;
        throw table_does_not_exist();
    }
    for (j = 0; j < cgpage->tbif[n].attrNum; j++) {
        if (strcmp((cgpage->tbif + n)->attrName[j], attrnm) == 0) { flag = 1; }
    }
    delete cgpage;
    return flag;
}

bool CatalogManager::checkUnique(char *tableName, char * attrname)    //参数：表名，属性名；检查属性是否unique
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }
    }
    if (i == pgNum) {
        delete cgpage;
        throw table_does_not_exist();
    }
    for (j = 0; j < cgpage->tbif[n].attrNum; j++) {
        if (strcmp(cgpage->tbif[n].attrName[j], attrname) == 0) 
        {
              if ((cgpage->tbif + n)->attrUnique[j])
               {
                    flag = true; 
                    delete cgpage;
                    return flag;

                }
        }
       
    }
    if (j == cgpage->tbif[n].attrNum) {
        delete cgpage;
        throw attr_does_not_exist();
    }
  
}

int CatalogManager::getAttrNo(char *tableName, char *attrname) {
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }

    }
    if (i == pgNum) {
        delete cgpage;
        throw table_does_not_exist();
    }
    for (j = 0; j < cgpage->tbif[n].attrNum; j++) {
        if (strcmp(cgpage->tbif[n].attrName[j], attrname) == 0) {
            delete cgpage;
            return j;
        }
    }
    if (j == cgpage->tbif[n].attrNum) {
        delete cgpage;
        throw attr_does_not_exist();
    }
}

AttributeType CatalogManager::getAttrType(char *tableName, char *attrname)    //参数：表名，属性名；返回属性类型
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }
    }
    if (i == pgNum) {
        delete cgpage;
        throw table_does_not_exist();
    }

    for (j = 0; j < cgpage->tbif[n].attrNum; j++) {
        if (strcmp((cgpage->tbif + n)->attrName[j], attrname) == 0) {
            delete cgpage;
            return (cgpage->tbif + n)->attrType[j];
        }
    }
    if (j == cgpage->tbif[n].attrNum) {
        delete cgpage;
        throw attr_does_not_exist();
    }

}

TableInfo CatalogManager::getTableInfo(char *tableName)   //参数：表名；返回表信息
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }
    }
    if (i != pgNum) {
        delete cgpage;
        return *(cgpage->tbif + n);
    } else {
        delete cgpage;
        throw table_does_not_exist();
    }

}

void CatalogManager::dropTable(char *tableName)                //参数：表名；删除一个表，并删除表的索引
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j, b;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }
    }
    if (i == pgNum) {

        delete cgpage;
        throw table_does_not_exist();
    }
    cgpage->deleteTable(pgdata, n);
    b = buffer.getPageId("./database/catalog/catalog", i);
    buffer.modifyPage(b);
    buffer.flushAfterQuery();
    delete cgpage;

}

void CatalogManager::createTable(TableInfo tbif)        //参数：TableInfo;若失败打印报错
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j, k = 0, b;
    char *pgdata;
    bool flag = false;
    int n = -1;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        if (strlen(pgdata) + tbif.dataLength > 4096) {
            continue;
        } else {
            cgpage->tableNum++;
            cgpage->tbif[cgpage->tableNum - 1] = tbif;
            cgpage->writePage(pgdata);
            b = buffer.getPageId("./database/catalog/catalog", i);
            buffer.modifyPage(b);
            buffer.flushAfterQuery();
            return;
        }
    }
    if (i == pgNum) {
        pgdata = getCatalogPage(i);
        memcpy(pgdata, &k, 4);
        cgpage->readPage(pgdata);
        cgpage->tableNum++;
        cgpage->tbif[cgpage->tableNum - 1] = tbif;
        cgpage->writePage(pgdata);
        b = buffer.getPageId("./database/catalog/catalog", i);
        buffer.modifyPage(b);
        buffer.flushAfterQuery();
    };
    delete cgpage;
}

void CatalogManager::createIndex(char *tableName, char *attrName, char *indexName) {
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j, b;
    char *pgdata;
    bool flag = false;
    int n = -1;
    int num;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        n = cgpage->searchTableInfo(tableName);
        if (n != -1) {
            break;
        }
    }

    if (i == pgNum) {
        delete cgpage;
        throw table_does_not_exist();
    }
    num = (cgpage->tbif + n)->attrNum;
    j = (cgpage->tbif + n)->searchAttr(attrName);
    if ((cgpage->tbif + n)->attrUnique[j] == false) {
        delete cgpage;
        throw attr_does_not_unique();
    }
    if ((cgpage->tbif + n)->hasIndex[j]) {
        delete cgpage;
        throw index_already_exist();
    }
    (cgpage->tbif + n)->hasIndex[j] = true;
    memcpy((cgpage->tbif + n)->indexName[j], indexName, 32);

    cgpage->updatePage(pgdata, n);
    delete cgpage;
    b = buffer.getPageId("./database/catalog/catalog", i);
    buffer.modifyPage(b);
    buffer.flushAfterQuery();
}

void CatalogManager::deleteIndex(char *indexName)    //参数：indexName；删除index，失败则报错：index_does_not_exist
{
    CatalogPage *cgpage = new CatalogPage;
    int pgNum = getCatalogPageNum();
    int i, j, m, b;
    char *pgdata;
    int n;
    char nul[32] = "";
    std::string str;
    for (i = 0; i < pgNum; i++) {
        pgdata = getCatalogPage(i);
        cgpage->readPage(pgdata);
        m = cgpage->tableNum;
        for (n = 0; n < m; n++) {
            for (j = 0; j < cgpage->tbif[n].attrNum; j++) {
                if (strcmp((cgpage->tbif + n)->indexName[j], indexName) == 0) {
                    (cgpage->tbif + n)->hasIndex[j] = false;
                    memcpy((cgpage->tbif + n)->indexName, nul, 32);
                    cgpage->updatePage(pgdata, n);
                    delete cgpage;
                    b = buffer.getPageId("./database/catalog/catalog", i);
                    buffer.modifyPage(b);
                    buffer.flushAfterQuery();
                    return;
                }
            }
        }
    }
    if (i == pgNum) {
        delete cgpage;
        throw index_does_not_exist();
    }
}

int CatalogManager::getCatalogPageNum() {
    std::string name = "./database/catalog/catalog";
    char *p;
    int block_num = -1;
    do {
        p = buffer.getPage(name, block_num + 1);
        block_num++;
    } while (p[0] != '\0');
    if (block_num == 0) block_num = 1;
    return block_num;
}

char *CatalogManager::getCatalogPage(int pageID) {
    return buffer.getPage("./database/catalog/catalog", pageID);
}
