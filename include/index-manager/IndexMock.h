#pragma once

#include <string>
#include <map>

#include "buffer_manager.h"
#include "tuple.h"
#include "Attribute.h"
#include "tableInfo.h"

struct Data {
    int type;
    int datai;
    float dataf;
    std::string datas;
};

class Index {
public :
    BufferManager &buffer_manager;

    Index(std::string table_name, TableInfo attr, BufferManager &buffer_manager) : buffer_manager(buffer_manager) {};

    void createIndex(std::string file_path, int type) {};

    void createIndexWithDatas(std::string file_path, int type, int n, vector<Tuple> datasTuple) {};

    void dropIndex(std::string file_path, int type) {};

    void clearIndex(std::string file_path, int type) {};

    int findIndex(std::string file_path, Data data) { return 0; }

    void insertIndex(std::string file_path, Data data, int index_in_record) {};

    void deleteIndexByKey(std::string file_path, Data data) {};

    std::vector<int> searchRange(std::string file_path, Data data1, Data data2, int flag) { return {}; }

    std::vector<int> searchRange1(std::string file_path, Data data, int flag) { return {}; }

    std::vector<int> searchRange2(std::string file_path, Data data, int flag) { return {}; }
};
