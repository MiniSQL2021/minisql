#ifndef PAGE_H
#define PAGE_H


#include<string>

#define PAGE_SIZE 4096
#define MAX_BLOCK 40

class Page {
private:
	char page_data[PAGE_SIZE];
	std::string file_name;		// the file name of this page
	int block_id;				// the block id of this page in this file
	int pinned_count;
	bool is_dirty;
	bool ref;					// reference number, used for LRU
	bool viable;

public:
	Page();
	~Page();
	char* getPageData();
	void setName(std::string name);
	std::string getName();
	void setBlockId(int id);
	int getBlockId();
	void setPinnedCount(int count);
	int getPinnedCount();
	void setIsDirty(bool dirty);
	bool getIsDirty();
	void setRef(bool r);
	bool getRef();
	void setViable(bool via);
	bool getViable();

};


#endif // !PAGE_H
