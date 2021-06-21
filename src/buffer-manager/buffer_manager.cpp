#include"buffer_manager.h"

BufferManager::BufferManager(int size) {
    init(size);
}

void BufferManager::init(int size) {
    Frames.resize(size);
    frame_size = size;
    current_pos = 0;
}

BufferManager::~BufferManager() {
    for (int i = 0; i < frame_size; i++) {
        std::string file_name = Frames[i].getName();
        int block_id = Frames[i].getBlockId();
        flushPage(i, file_name, block_id);
    }
}

char *BufferManager::getPage(std::string file_name, int block_id) {
    int page_id = getPageId(file_name, block_id);
    if (page_id == -1) {
        page_id = getAnEmptyPageId();
        loadDiskBlock(page_id, file_name, block_id);
    }
    Frames[page_id].setRef(true);
    return Frames[page_id].getPageData();
}

void BufferManager::modifyPage(int page_id) {
    Frames[page_id].setIsDirty(true);
}

void BufferManager::pinPage(int page_id) {
    int pinned_count = Frames[page_id].getPinnedCount();
    Frames[page_id].setPinnedCount(pinned_count + 1);
}

bool BufferManager::unpinPage(int page_id) {
    int pinned_count = Frames[page_id].getPinnedCount();
    if (pinned_count <= 0)
        return false;
    else {
        Frames[page_id].setPinnedCount(pinned_count - 1);
        return true;
    }
}

void BufferManager::loadDiskBlock(int page_id, std::string file_name, int block_id) {
    Frames[page_id].init();

    FILE *f = fopen(file_name.c_str(), "a+");

    fseek(f, PAGE_SIZE * block_id, SEEK_SET);

    char *buffer = Frames[page_id].getPageData();

    fread(buffer, PAGE_SIZE, 1, f);

    fclose(f);

    Frames[page_id].setName(file_name);
    Frames[page_id].setBlockId(block_id);
    Frames[page_id].setPinnedCount(0);
    Frames[page_id].setIsDirty(false);
    Frames[page_id].setRef(true);
    Frames[page_id].setViable(false);

}

// linear scan
int BufferManager::getPageId(std::string file_name, int block_id) {
    for (int i = 0; i < frame_size; i++) {
        std::string tmp_file_name = Frames[i].getName();
        int tmp_block_id = Frames[i].getBlockId();
        if (tmp_file_name == file_name && tmp_block_id == block_id)
            return i;
    }
    return -1;
}

// LRU
int BufferManager::getAnEmptyPageId() {
    for (int i = 0; i < frame_size; i++) {
        if (Frames[i].getViable() == true)
            return i;
    }

    while (1) {
        if (Frames[current_pos].getRef() == true) {
            Frames[current_pos].setRef(false);
        } else if (Frames[current_pos].getPinnedCount() == 0) {
            if (Frames[current_pos].getIsDirty() == true) {
                std::string file_name = Frames[current_pos].getName();
                int block_id = Frames[current_pos].getBlockId();
                flushPage(current_pos, file_name, block_id);
            }
            Frames[current_pos].init();
            return current_pos;
        }
        current_pos = (current_pos + 1) % frame_size;
    }
}

void BufferManager::flushPage(int page_id, std::string file_name, int block_id) {
    FILE *f = fopen(file_name.c_str(), "r+");

    fseek(f, PAGE_SIZE * block_id, SEEK_SET);
    char *buffer = Frames[page_id].getPageData();
    fwrite(buffer, PAGE_SIZE, 1, f);
    fclose(f);
    Frames[page_id].setIsDirty(false);
}

// after each query, write dirty pages to disk
void BufferManager::flushAfterQuery() {
    for (int i = 0; i < frame_size; i++) {
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
