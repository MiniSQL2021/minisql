#include"Page.h"

using namespace std;


Page::Page() {
	init();	
}


void Page::init() {
	file_name = "";
	block_id = -1;
	pinned_count = -1;
	is_dirty = false;
	ref = false;
	viable = true;
	for (int i = 0; i < PAGE_SIZE; i++)
		page_data[i] = '\0';
}



Page::~Page() {

}


char* Page::getPageData() {
	return page_data;
}


void Page::setName(string name) {
	file_name = name;
}

string Page::getName() {
	return file_name;
}

void Page::setBlockId(int id) {
	block_id = id;
}


int Page::getBlockId() {
	return block_id;
}


void Page::setPinnedCount(int count) {
	pinned_count = count;
}

int Page::getPinnedCount() {
	return pinned_count;
}

void Page::setIsDirty(bool dirty) {
	is_dirty = dirty;
}

bool Page::getIsDirty() {
	return is_dirty;
}

void Page::setRef(bool r) {
	ref = r;
}

bool Page::getRef() {
	return ref;
}

void Page::setViable(bool via) {
	viable = via;
}


bool Page::getViable() {
	return viable;
}