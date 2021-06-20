#pragma once
#include "Attribute.h"
#include "Tree.h"
#include "buffer_manager.h"
#include "tableInfo.h"
#include "tuple.h"
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Data {
	int type;
	int datai;
	float dataf;
	std::string datas;
};
class Index{
	
	
public :

	BufferManager &buffer_manager;
	//构造函数
	Index(std::string table_name, TableInfo attr, BufferManager &buffer_manager);  //这个attr是API传入从catlog获取的表信息
	//析构函数
	~Index();
	//输入：Index文件名(路径)，索引的key的类型
	//输出：void
	//功能：创建索引文件及B+树
	//异常：
	void createIndex(std::string file_path, int type);

        void createIndexWithDatas(std::string file_path, int type, int n,
                                  std::vector<Tuple> datasTuple);

        //输入：Index文件名(路径)，索引的key的类型
        //输出：void
        //功能：删除索引、B+树及文件
        //异常：
        void dropIndex(std::string file_path, int type);
        //输入：Index文件名(路径)，索引的key(包含类型)
	//输出：void
	//功能：创建索引文件及B+树
	//异常：
	void clearIndex(std::string file_path, int type);
	int findIndex(std::string file_path, Data data);
	//输入：Index文件名(路径)，索引的key(包含类型)，index_in_record)
	//输出：void
	//功能：在指定索引中插入一个key
	//异常：
	void insertIndex(std::string file_path, Data data, int index_in_record);
	//输入：Index文件名(路径)，索引的key(包含类型)
	//输出：void
	//功能：在索引中删除相应的Key
	//异常：
	void deleteIndexByKey(std::string file_path, Data data);
	//输入：Index文件名(路径)，索引的key1(包含类型)，索引的key2(包含类型)，返回的index_in_records数组
	//输出：void
	//功能：范围查找，返回一定范围内的index_in_record
	//异常：

        std::vector<int> searchRange(std::string file_path, Data data1, Data data2, int flag);
        std::vector<int> searchRange1(std::string file_path, Data data, int flag);
        std::vector<int> searchRange2(std::string file_path, Data data, int flag);

      private:
        typedef std::map<std::string, Tree<int> *> intMap;
        typedef std::map<std::string, Tree<std::string> *> stringMap;
	typedef std::map<std::string, Tree<float> *> floatMap;

	int static const TYPE_INT = 0;
	int static const TYPE_FLOAT = 1;
	int static const TYPE_STRING = 2;

	intMap indexIntMap;
	stringMap indexStringMap;
	floatMap indexFloatMap;


	//计算B+树适合的degree
	int getDegree(int type);

	//计算不同类型Key的size
	int getKeySize(int type);

};
