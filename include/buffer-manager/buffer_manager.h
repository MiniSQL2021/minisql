#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include"Page.h"
#include<iostream>
#include<vector>

class BufferManager {
private:
	Page* Frames;		// an array of Page
	int frame_size;
	int current_pos;	// used for LRU



public:
	BufferManager();
	BufferManager(int size);
	~BufferManager();

	
	char* getPage(std::string file_name, int block_id);
	void modifyPage(int page_id);
	void pinPage(int page_id);
	bool unpinPage(int page_id);
	void flushPage(int page_id, std::string file_name, int block_id);
	int getPageId(std::string file_name, int block_id);

	int getAnEmptyPageId();	
	bool loadDiskBlock(int page_id, std::string file_name, int block_id);


};




#endif // !BUFFER_MANAGER_H

