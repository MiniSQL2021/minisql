#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include"Page.h"
#include<iostream>
#include<vector>

class BufferManager {
private:
    Page *Frames;        // an array of Page
    int frame_size;
    int current_pos;    // used for LRU



public:
    BufferManager();

    BufferManager(int size);

    ~BufferManager();

    char *getPage(std::string file_name, int block_id);

    void modifyPage(int page_id);

    void pinPage(int page_id);

    bool unpinPage(int page_id);

    void flushPage(int page_id, std::string file_name, int block_id);

    int getPageId(std::string file_name, int block_id);

    int getAnEmptyPageId();

    bool loadDiskBlock(int page_id, std::string file_name, int block_id);

    //null
    int getCatalogPageNum();

    char *getCatalogPage(int pageID);

    int getTablePageNum(char *tableName);

    char *getTablePage(char *tablename, int tableID);

    char *createTablePage(char *tableName);    //buffer新建文件，设置pageNum为1，并返回pagedata指针
    char *addTablePage(char *tablename);        //buffer设置pageNum++，并返回pagedata指针
    char *addCatalogPage();            //buffer设置pageNum++，并返回pagedata指针

    void releasePage(char *pagedata);            //pagedata编辑完成，buffer收回指针，将page存回文件中，释放这个page缓存
    void dropTable(char *tablename);

};

#endif // !BUFFER_MANAGER_H

