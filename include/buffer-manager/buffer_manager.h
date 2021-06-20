#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include"Page.h"
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<vector>

class BufferManager {
private:
    std::vector<Page> Frames;        // an array of Page
    int frame_size;
    int current_pos;    // used for LRU

    void init(int size);

    int getAnEmptyPageId();

    // load the block with the file_name to the page_id page
    // failed to open, return false
    // else, return true
    void loadDiskBlock(int page_id, std::string file_name, int block_id);

public:
    BufferManager(int size = MAX_BLOCK);

    ~BufferManager();

    // return the pointer of the page
    char *getPage(std::string file_name, int block_id);

    // mark the modified page
    void modifyPage(int page_id);

    void pinPage(int page_id);

    // unpin a page
    // if pinned_count is 0, return fasle
    // else, return true
    bool unpinPage(int page_id);

    // write the page to disk
    void flushPage(int page_id, std::string file_name, int block_id);

    // return file_name's block_id th block's page_id
    int getPageId(std::string file_name, int block_id);

    // after each query, write dirty pages to disk
    void flushAfterQuery();
};

#endif // !BUFFER_MANAGER_H

