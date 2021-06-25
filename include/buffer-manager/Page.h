#ifndef PAGE_H
#define PAGE_H

#include<string>

#define PAGE_SIZE 4096
#define MAX_BLOCK 400

class Page {
private:
    char page_data[PAGE_SIZE];
    std::string file_name;        // the file name of this page
    int block_id;                // the block id of this page in this file
    bool is_pinned;
    bool is_dirty;         
    int ref_count;              
    bool is_empty;             

public:
    Page();

    ~Page();

    void init();

    char *getPageData();

    void setName(std::string name);

    std::string getName();

    void setBlockId(int id);

    int getBlockId();

    void setIsPinned(bool p);

    int getIsPinned();

    void setIsDirty(bool dirty);

    bool getIsDirty();

    void setRefCount(int r);

    bool getRefCount();

    void setIsEmpty(bool e);

    bool getIsEmpty();

};

#endif // !PAGE_H
