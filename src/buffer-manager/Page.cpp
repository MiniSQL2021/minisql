#include"Page.h"

Page::Page() {
    init();
}

void Page::init() {
    file_name = "";
    block_id = -1;
    is_pinned = 0;
    is_dirty = false;
    ref_count = 1;
    is_empty = true;
    for (int i = 0; i < PAGE_SIZE; i++)
        page_data[i] = '\0';
}

Page::~Page() {

}

char *Page::getPageData() {
    return page_data;
}

void Page::setName(std::string name) { file_name = name; }

std::string Page::getName() { return file_name; }

void Page::setBlockId(int id) {
    block_id = id;
}

int Page::getBlockId() {
    return block_id;
}

void Page::setIsPinned(bool p) {
    is_pinned = p;
}

int Page::getIsPinned() {
    return is_pinned;
}

void Page::setIsDirty(bool dirty) {
    is_dirty = dirty;
}

bool Page::getIsDirty() {
    return is_dirty;
}

void Page::setRefCount(int r) {
    if (r >= 0)
        ref_count = r;
    else
        ref_count = 0;
}

bool Page::getRefCount() {
    return ref_count;
}

void Page::setIsEmpty(bool e) {
    is_empty = e;
}

bool Page::getIsEmpty() {
    return is_empty;
}
