#include"buffer_manager.h"

using namespace std;

BufferManager::BufferManager(int size) {
    init(size);
}

void BufferManager::init(int size) {
    Frames.resize(size);
    current_pos = 0;
    for (int i = 0; i < Frames.size(); i++){
        Frames[i].init();
        Frames[i].setRefCount(0);
    }
}

BufferManager::~BufferManager() {
    for (int i = 0; i < Frames.size(); i++) {
        string file_name = Frames[i].getName();
        int block_id = Frames[i].getBlockId();
        flushPage(i, file_name, block_id);
    }
}

char *BufferManager::getPage(string file_name, int block_id) {
    int page_id = getPageId(file_name, block_id);
    if (page_id == -1) {
        page_id = getAnEmptyPageId();
        loadDiskBlock(page_id, file_name, block_id);
    }
    Frames[page_id].setRefCount(Frames[page_id].getRefCount() + 1);
    return Frames[page_id].getPageData();
}

void BufferManager::modifyPage(int page_id) {
    Frames[page_id].setIsDirty(true);
}

void BufferManager::pinPage(int page_id) {
    Frames[page_id].setIsPinned(true);
}

bool BufferManager::unpinPage(int page_id) {
    Frames[page_id].setIsPinned(false);
}

void BufferManager::loadDiskBlock(int page_id, string file_name, int block_id) {
    Frames[page_id].init();

    FILE *f = fopen(file_name.c_str(), "a+");

    fseek(f, PAGE_SIZE * block_id, SEEK_SET);

    char *buffer = Frames[page_id].getPageData();

    fread(buffer, PAGE_SIZE, 1, f);

    fclose(f);

    Frames[page_id].setName(file_name);
    Frames[page_id].setBlockId(block_id);
    Frames[page_id].setIsPinned(false);
    Frames[page_id].setIsDirty(false);
    Frames[page_id].setRefCount(1);
    Frames[page_id].setIsEmpty(false);
}

// linear scan
int BufferManager::getPageId(string file_name, int block_id) {
    for (int i = 0; i < Frames.size(); i++) {
        string tmp_file_name = Frames[i].getName();
        if (tmp_file_name != file_name)
            continue;
        int tmp_block_id = Frames[i].getBlockId();
        if (tmp_block_id == block_id)
            return i;
    }
    return -1;
}

// LRU
int BufferManager::getAnEmptyPageId() {
    for (int i = 0; i < Frames.size(); i++) {
        if (Frames[i].getIsEmpty() == true)
            return i;
    }
    while (1) {
        if (Frames[current_pos].getIsPinned() == false){
            if (Frames[current_pos].getRefCount() == 0){
                if (Frames[current_pos].getIsDirty() == true){
                    string file_name = Frames[current_pos].getName();
                    int block_id = Frames[current_pos].getBlockId();
                    flushPage(current_pos, file_name, block_id);
                }
                Frames[current_pos].init();
                return current_pos;
            }
            else{
                Frames[current_pos].setRefCount(Frames[current_pos].getRefCount()-1);
            }
        }
        current_pos = (current_pos + 1) % Frames.size();

    }
}

void BufferManager::flushPage(int page_id, string file_name, int block_id) {
    FILE *f = fopen(file_name.c_str(), "r+");

    fseek(f, PAGE_SIZE * block_id, SEEK_SET);
    char *buffer = Frames[page_id].getPageData();
    fwrite(buffer, PAGE_SIZE, 1, f);
    fclose(f);
    Frames[page_id].setIsDirty(false);
}

// after each query, write dirty pages to disk
void BufferManager::flushAfterQuery() {
    for (int i = 0; i < Frames.size(); i++) {
        if (Frames[i].getIsDirty()) {
            FILE *f = fopen(Frames[i].getName().c_str(), "r+");

            fseek(f, PAGE_SIZE * Frames[i].getBlockId(), SEEK_SET);
            char *buffer = Frames[i].getPageData();
            fwrite(buffer, PAGE_SIZE, 1, f);
            fclose(f);
            Frames[i].setIsDirty(false);
        }
    }
}

void BufferManager::deleteFile(string file_name) {
    for (int i = 0; i < Frames.size(); i++) {
        if (Frames[i].getName() == file_name) {
            Frames[i].init();
        }
    }
    remove(file_name.c_str());
}
