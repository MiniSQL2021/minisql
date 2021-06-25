#include "Index.h"
#include <iostream>
#include "buffer_manager.h"
#include "Tree.h"
#include "Catalog_Manager.h"
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include "exception.h"
#include <sstream>
#include <tuple>
#include "tableInfo.h"

Index::Index(std::string table_name, TableInfo attr, BufferManager &buffer_manager):buffer_manager(buffer_manager){
	for (int i = 0; i < attr.attrNum; i++)
		if (attr.hasIndex[i]) {
			std::string a = attr.attrName[i];
			int b;
			memcpy(&b,attr.attrType+i,4);
			createIndex("INDEX_FILE_" +  table_name + "_" +a, b);
		}
}

Index::~Index()
{
	for (intMap::iterator itInt = indexIntMap.begin(); itInt != indexIntMap.end(); itInt++) {
		if (itInt->second) {
			itInt->second->writtenbackToDiskAll();
			delete itInt->second;
		}
	}
	for (stringMap::iterator itString = indexStringMap.begin(); itString != indexStringMap.end(); itString++) {
		if (itString->second) {
			itString->second->writtenbackToDiskAll();
			delete itString->second;
		}
	}
	for (floatMap::iterator itFloat = indexFloatMap.begin(); itFloat != indexFloatMap.end(); itFloat++) {
		if (itFloat->second) {
			itFloat->second->writtenbackToDiskAll();
			delete itFloat->second;
		}
	}
}

void Index::createIndex(std::string file_path, int type, int string_length)
{

	int key_size = getKeySize(type, string_length); //获取key的size
	int degree = getDegree(type); //获取需要的degree

	//根据数据类型不同，用对应的方法建立映射关系
	//并且先初始化一颗B+树
	if (type == TYPE_INT) {
		Tree<int> *tree = new Tree<int>(file_path, key_size, degree, buffer_manager);
		indexIntMap.insert(intMap::value_type(file_path, tree));
	}
	else if (type == TYPE_FLOAT) {
		Tree<float> *tree = new Tree<float>(file_path, key_size, degree, buffer_manager);
		indexFloatMap.insert(floatMap::value_type(file_path, tree));
	}
	else {
		Tree<std::string> *tree = new Tree<std::string>(file_path, key_size, degree, buffer_manager);
		indexStringMap.insert(stringMap::value_type(file_path, tree));
	}

	return;
}

void Index::createIndexWithDatas(std::string file_path, int type,int n, std::vector<Tuple> datasTuple)
{
	createIndex(file_path, type);
	for (int i = 0; i < datasTuple.size(); i++) {
		Data data;
		data.type = type;
		if (type == 0) {

			data.datai = datasTuple[i].attr[n].intData;
		}
		else if(type==1){
			data.dataf = datasTuple[i].attr[n].floatData;
		}
		else {
			std::string strtemp = datasTuple[i].attr[n].charData;
			data.datas = strtemp;
		}
		insertIndex(file_path, data, i);
	}



}

void Index::dropIndex(std::string file_path, int type)
{
	//根据不同数据类型采用对应的处理方式
	if (type == TYPE_INT) {
		//查找路径对应的键值对
		intMap::iterator itInt = indexIntMap.find(file_path);
		if (itInt == indexIntMap.end()) { //未找到
			throw dropIndex_cannot_find_index();
			return;
		}
		else {
			//删除对应的B+树
			delete itInt->second;
			//清空该键值对
			indexIntMap.erase(itInt);
		}
	}
	else if (type == TYPE_FLOAT) { //同上
		floatMap::iterator itFloat = indexFloatMap.find(file_path);
		if (itFloat == indexFloatMap.end()) {
			throw dropIndex_cannot_find_index();
			return;
		}
		else {
			delete itFloat->second;
			indexFloatMap.erase(itFloat);
		}
	}
	else {
		stringMap::iterator itString = indexStringMap.find(file_path);
		if (itString == indexStringMap.end()) { //同上
			throw dropIndex_cannot_find_index();
			return;
		}
		else {
			delete itString->second;
			indexStringMap.erase(itString);
		}
	}

	std::string file_name = "./database/index/" + file_path;
	buffer_manager.deleteFile(file_name);
	return;
}

void Index::clearIndex(std::string file_path, int type)
{
	Index::createIndex( file_path, type);
	Index::dropIndex(file_path, type);

}

int Index::findIndex(std::string file_path, Data data)
{
	//setKey(type, key);

	if (data.type == TYPE_INT) {
		intMap::iterator itInt = indexIntMap.find(file_path);
		if (itInt == indexIntMap.end()) { //未找到
			throw findIndex_cannot_find_index();
			return -1;
		}
		else {
			//找到则返回对应的键值
			return itInt->second->searchKey(data.datai);
		}
	}
	else if (data.type == TYPE_FLOAT) {
		floatMap::iterator itFloat = indexFloatMap.find(file_path);
		if (itFloat == indexFloatMap.end()) { //同上
			throw findIndex_cannot_find_index();
			return -1;
		}
		else {
			return itFloat->second->searchKey(data.dataf);
		}
	}
	else {
		stringMap::iterator itString = indexStringMap.find(file_path);
		if (itString == indexStringMap.end()) { //同上
			throw findIndex_cannot_find_index();
			return -1;
		}
		else {
			return itString->second->searchKey(data.datas);
		}
	}
}


void Index::insertIndex(std::string file_path, Data data, int index_in_record)
{
	//setKey(type, key);

	if (data.type == TYPE_INT) {
		intMap::iterator itInt = indexIntMap.find(file_path);
		if (itInt == indexIntMap.end()) {
			throw insertIndex_cannot_find_file_path();
			return;
		}
		else
			itInt->second->insertKey(data.datai, index_in_record);
	}
	else if (data.type == TYPE_FLOAT) {
		floatMap::iterator itFloat = indexFloatMap.find(file_path);
		if (itFloat == indexFloatMap.end()) {
			throw insertIndex_cannot_find_file_path();
			return;
		}
		else
			itFloat->second->insertKey(data.dataf, index_in_record);
	}
	else {
		stringMap::iterator itString = indexStringMap.find(file_path);
		if (itString == indexStringMap.end()) {
			throw insertIndex_cannot_find_file_path();
			return;
		}
		else
			itString->second->insertKey(data.datas, index_in_record);
	}

	return;
}

void Index::deleteIndexByKey(std::string file_path, Data data)
{
	//setKey(type, key);

	if (data.type == TYPE_INT) {
		intMap::iterator itInt = indexIntMap.find(file_path);
		if (itInt == indexIntMap.end()) {
			throw deleteIndex_cannot_find_with_file_path();
			return;
		}
		else
			itInt->second->deleteKey(data.datai);
	}
	else if (data.type == TYPE_FLOAT) {
		floatMap::iterator itFloat = indexFloatMap.find(file_path);
		if (itFloat == indexFloatMap.end()) {
			throw deleteIndex_cannot_find_with_file_path();
			return;
		}
		else
			itFloat->second->deleteKey(data.dataf);
	}
	else {
		stringMap::iterator itString = indexStringMap.find(file_path);
		if (itString == indexStringMap.end()) {
			throw deleteIndex_cannot_find_with_file_path();
			return;
		}
		else
			itString->second->deleteKey(data.datas);
	}
}


std::vector<int> Index::searchRange(std::string file_path, Data data1, Data data2, int flag)
{
	std::vector<int> index_in_records;

	if (data1.type == TYPE_INT) {
		intMap::iterator itInt = indexIntMap.find(file_path);
		if (itInt == indexIntMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itInt->second->searchRange(data1.datai, data2.datai, index_in_records,flag);
	}
	else if (data1.type == TYPE_FLOAT) {
		floatMap::iterator itFloat = indexFloatMap.find(file_path);
		if (itFloat == indexFloatMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itFloat->second->searchRange(data1.dataf, data2.dataf, index_in_records, flag);
	}
	else {
		stringMap::iterator itString = indexStringMap.find(file_path);
		if (itString == indexStringMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itString->second->searchRange(data1.datas, data2.datas, index_in_records,flag);
	}

	return std::vector<int>(index_in_records);
}

std::vector<int> Index::searchRange1(std::string file_path, Data data, int flag)
{
	std::vector<int> index_in_records;

	if (data.type == TYPE_INT) {
		intMap::iterator itInt = indexIntMap.find(file_path);
		if (itInt == indexIntMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itInt->second->searchRange1(data.datai, index_in_records, flag);
	}
	else if (data.type == TYPE_FLOAT) {
		floatMap::iterator itFloat = indexFloatMap.find(file_path);
		if (itFloat == indexFloatMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itFloat->second->searchRange1(data.dataf, index_in_records,flag);
	}
	else {
		stringMap::iterator itString = indexStringMap.find(file_path);
		if (itString == indexStringMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itString->second->searchRange1(data.datas,index_in_records,flag);
	}

	return std::vector<int>(index_in_records);
}

std::vector<int> Index::searchRange2(std::string file_path, Data data, int flag)
{
	std::vector<int> index_in_records;

	if (data.type == TYPE_INT) {
		intMap::iterator itInt = indexIntMap.find(file_path);
		if (itInt == indexIntMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itInt->second->searchRange2(data.datai, index_in_records, flag);
	}
	else if (data.type == TYPE_FLOAT) {
		floatMap::iterator itFloat = indexFloatMap.find(file_path);
		if (itFloat == indexFloatMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itFloat->second->searchRange2(data.dataf, index_in_records, flag);
	}
	else {
		stringMap::iterator itString = indexStringMap.find(file_path);
		if (itString == indexStringMap.end()) {
			throw searchIndex_cannot_find_with_file_path();

		}
		else
			itString->second->searchRange2(data.datas, index_in_records, flag);
	}

	return std::vector<int>(index_in_records);
}




int Index::getDegree(int type)
{
	int degree = (PAGE_SIZE - sizeof(int)) / (getKeySize(type) + sizeof(int)+4);
	if (degree % 2 == 0)
		degree -= 1;
	return degree;
}

int Index::getKeySize(int type,int string_length)
{
	if (type == TYPE_FLOAT)
		return sizeof(float);
	else if (type == TYPE_INT)
		return sizeof(int);
	else if (type > 0)
		return string_length;
	else {
		throw getKeySize_wrong();
		return -100;
	}
}
