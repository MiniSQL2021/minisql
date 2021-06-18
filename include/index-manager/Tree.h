#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include"TreeNode.h"
#include "exception.h"
#include "buffer_manager.h"
#include "template_function.h"



template <typename T>
class Tree {
private:
	//重命名TreeNode指针，方便后边进行操作区分
	typedef TreeNode<T>* TreeNode1;
	//文件名
	std::string file_name;
	//根节点
	TreeNode1 root;
	//叶节点头指针
	TreeNode1 leafHead;
	int key_num;
	int level;
	int node_num;
	int key_size;
	int degree;


	//初始化B+树，并分配内存空间
	bool initialization();
	//用于插入某key后结点满情况，对整棵树进行调整
	bool adjustAfterinsert(TreeNode1 pNode);
	//用于删除某key后可能出现结点空情况，对整棵树进行调整
	bool adjustAfterDelete(TreeNode1 pNode);
	//用于查找某key值所处的叶结点位置
	bool findToLeaf1(TreeNode1 pNode, T key, TreeNode1 &return_node, int &return_index);
	//用于查找某key值所处的叶结点位置
	bool findToLeaf2(TreeNode1 pNode, T key, TreeNode1 &return_node, int &return_index);

	bool findMin(TreeNode1 root, T & key, TreeNode1 &return_node, int &return_index);
	//获取文件大小
	void getFile(std::string file_path);
	int getBlockNum(std::string table_name);

public:
	BufferManager& buffer_manager;
	//构造函数
	//用于构造一颗新的树，确定m_name,key的size，树的度
	//同时调用其他函数为本树分配内存
	Tree(std::string m_name, int key_size, int degree, BufferManager &buffer_manager);
	//析构函数
	//释放相应的内存
	~Tree();

	//根据key值返回对应的index_in_record
	int searchKey(T &key);

	//输入：key值及其index_in_record
	//输出：bool
	//功能：在树中插入一个key值
	//返回是否插入成功
	bool insertKey(T &key, int index_in_record);

	//输入：key值
	//输出：bool
	//功能：在树中删除一个key值
	//返回是否删除成功
	bool deleteKey(T &key);

	//输入：树的根结点
	//功能：删除整棵树并释放内存空间，主要用在析构函数中
	void dropTree(TreeNode1 tree_node);

	//输入：key1，key2，返回index_in_records的容器
	//功能：返回范围搜索结果，将index_in_record放入index_in_records容器中
	void searchRange(T &key1, T &key2, std::vector<int>& index_in_records, int flag);
	void searchRange1(T &key, std::vector<int>& index_in_records ,int flag);
	void searchRange2(T &key, std::vector<int>& index_in_records ,int flag);

	//从磁盘读取所有数据
	void readFromDiskAll();
	//将新数据写入磁盘
	void writtenbackToDiskAll();
	//在磁盘中读取某一块的数据
	void readFromDisk(char *p, char* end);


};


//New Tree
template<typename T>
inline Tree<T>::Tree(std::string in_name, int key_size, int in_degree,BufferManager &buffer_manager):
	buffer_manager(buffer_manager),
	file_name(in_name),
	key_num(0),
	level(0),
	node_num(0),
	root(NULL),
	leafHead(NULL),
	key_size(key_size),
	degree(in_degree)
{
	//初始化并读取数据
	initialization();
	readFromDiskAll();

}

template<typename T>
inline Tree<T>::~Tree()
{
	dropTree(root);
	key_num = 0;
	root = NULL;
	level = 0;
}


template<typename T>
inline int Tree<T>::searchKey(T & key)
{
	if (!root) {
		return -1;
	}
	int return_index;
	TreeNode1 return_node;
	bool a = findToLeaf1(root, key, return_node, return_index);
	if (!a) {
		return -1;
	}
	else {
		return return_node->index_in_records[return_index];
	}
}

template<typename T>
inline bool Tree<T>::insertKey(T & key, int index_in_record)
{
	TreeNode1 pNode;
	int index;
	//根结点不存在
	if (!root)
		initialization();
	//查找插入值是否存在
	bool ifFound = findToLeaf1(root, key, pNode, index);
	if (ifFound) { //已存在
		
		return false;
	}
	else { //不存在，可以插入
		pNode->addKey(key, index_in_record);
		//插入后结点满，需要进行调整
		if (pNode->num == degree) {
			adjustAfterinsert(pNode);
		}
		key_num++;
		return true;
	}

	return false;
}

template<typename T>
inline bool Tree<T>::deleteKey(T & key)
{
	TreeNode1 pNode;
	int index;
	//根结点不存在
	if (!root) {
		throw deleteKey_no_node_in_tree() ;
	
		return false;
	}
	else { //正常进行操作
	 //查找位置
		bool ifFound = findToLeaf1(root, key, pNode, index);
		if (!ifFound) { //找不到该key
			throw deleteKey_no_keys_in_tree();
			return false;
		}
		else { //正常找到进行删除
			if (pNode->isRoot()) { //当前为根结点
				pNode->deleteKeyByIndex(index);
				key_num--;
				return adjustAfterDelete(pNode);
			}
			else {
				if (index == 0 && leafHead != pNode) {
					//key存在于枝干结点上
					//到上一层去更新枝干层
					int i = 0;

					TreeNode1 now_parent = pNode->parent;
					bool if_found_inBranch = now_parent->findKey1(key, i);
					while (!if_found_inBranch) {
						if (now_parent->parent)
							now_parent = now_parent->parent;
						else
							break;
						if_found_inBranch = now_parent->findKey1(key, i);
					}

					now_parent->keys[i] = pNode->keys[1];

					pNode->deleteKeyByIndex(i);
					key_num--;
					return adjustAfterDelete(pNode);

				}
				else { //同时必然存在于叶结点
					pNode->deleteKeyByIndex(index);
					key_num--;
					return adjustAfterDelete(pNode);
				}
			}
		}
	}

	return false;
}



template<typename T>
inline bool Tree<T>::initialization()
{
	root = new TreeNode<T> (degree, true);
	key_num = 0;
	level = 1;
	node_num = 1;
	leafHead = root;
	return true;
}

template<typename T>
inline bool Tree<T>::adjustAfterinsert(TreeNode1 pNode)
{
	T key;
	TreeNode1 newNode = pNode->splitNode(key);
	node_num++;

	//当前结点为根结点情况
	if (pNode->isRoot()) {
		TreeNode1 root = new TreeNode<T> (degree, false);
		if (root == NULL) {
			throw adjustAfterinser_can_not_allocate_the_new_root();
		}
		else {
			level++;
			node_num++;
			this->root = root;
			pNode->parent = root;
			newNode->parent = root;
			root->addKey(key);
			root->childs[0] = pNode;
			root->childs[1] = newNode;
			return true;
		}
	}
	else { //当前结点非根结点
		TreeNode1 parent = pNode->parent;
		int i = parent->addKey(key);

		parent->childs[i + 1] = newNode;
		newNode->parent = parent;
		//递归进行调整
		if (parent->num == degree)
			return adjustAfterinsert(parent);

		return true;
	}

	return false;
}

template<typename T>
inline bool Tree<T>::adjustAfterDelete(TreeNode1 pNode)
{
	int minmumKeyNum = (degree - 1) / 2;
	//三种不需要调整的情况
	if (((pNode->isLeaf) && (pNode->num >= minmumKeyNum)) ||
		((degree != 3) && (!pNode->isLeaf) && (pNode->num >= minmumKeyNum - 1)) ||
		((degree == 3) && (!pNode->isLeaf) && (pNode->num < 0))) {
		return  true;
	}
	if (pNode->isRoot()) { //当前结点为根结点
		//不需要调整
		if (pNode->num > 0) {
			return true;
		}
		//正常需要调整
		else { 
			if (root->isLeaf) { //将成为空树情况
				delete pNode;
				root = NULL;
				leafHead = NULL;
				level--;
				node_num--;
			}
			else { //根节点将成为左头部
				root = pNode->childs[0];
				root->parent = NULL;
				delete pNode;
				level--;
				node_num--;
			}
		}
	}
	else { //非根节点情况
		TreeNode1 parent = pNode->parent, brother = NULL;
		if (pNode->isLeaf) { //当前为叶节点
			int index = 0;
			parent->findKey1(pNode->keys[0], index);

			//选择左兄弟
			if ((parent->childs[0] != pNode) && (index + 1 == parent->num)) {
				brother = parent->childs[index];
				if (brother->num > minmumKeyNum) {
					for (unsigned int i = pNode->num; i > 0; i--) {
						pNode->keys[i] = pNode->keys[i - 1];
						pNode->index_in_records[i] = pNode->index_in_records[i - 1];
					}
					pNode->keys[0] = brother->keys[brother->num - 1];
					pNode->index_in_records[0] = brother->index_in_records[brother->num - 1];
					brother->deleteKeyByIndex(brother->num - 1);

					pNode->num++;
					parent->keys[index] = pNode->keys[0];
					return true;

				}
				else {
					parent->deleteKeyByIndex(index);

					for (int i = 0; i < pNode->num; i++) {
						brother->keys[i + brother->num] = pNode->keys[i];
						brother->index_in_records[i + brother->num] = pNode->index_in_records[i];
					}
					brother->num += pNode->num;
					brother->nextLeafNode = pNode->nextLeafNode;

					delete pNode;
					node_num--;

					return adjustAfterDelete(parent);
				}

			}
			else {
				if (parent->childs[0] == pNode)
					brother = parent->childs[1];
				else
					brother = parent->childs[index + 2];
				if (brother->num > minmumKeyNum) {
					pNode->keys[pNode->num] = brother->keys[0];
					pNode->index_in_records[pNode->num] = brother->index_in_records[0];
					pNode->num++;
					brother->deleteKeyByIndex(0);
					if (parent->childs[0] == pNode)
						parent->keys[0] = brother->keys[0];
					else
						parent->keys[index + 1] = brother->keys[0];
					return true;

				}
				else {
					for (int i = 0; i < brother->num; i++) {
						pNode->keys[pNode->num + i] = brother->keys[i];
						pNode->index_in_records[pNode->num + i] = brother->index_in_records[i];
					}
					if (pNode == parent->childs[0])
						parent->deleteKeyByIndex(0);
					else
						parent->deleteKeyByIndex(index + 1);
					pNode->num += brother->num;
					pNode->nextLeafNode = brother->nextLeafNode;
					delete brother;
					node_num--;

					return adjustAfterDelete(parent);
				}
			}

		}
		else { //枝干节点情况
			int index = 0;
			parent->findKey1(pNode->childs[0]->keys[0], index);
			if ((parent->childs[0] != pNode) && (index + 1 == parent->num)) {
				brother = parent->childs[index];
				if (brother->num > minmumKeyNum - 1) {
					pNode->childs[pNode->num + 1] = pNode->childs[pNode->num];
					for (unsigned int i = pNode->num; i > 0; i--) {
						pNode->childs[i] = pNode->childs[i - 1];
						pNode->keys[i] = pNode->keys[i - 1];
					}
					pNode->childs[0] = brother->childs[brother->num];
					pNode->keys[0] = parent->keys[index];
					pNode->num++;

					parent->keys[index] = brother->keys[brother->num - 1];

					if (brother->childs[brother->num])
						brother->childs[brother->num]->parent = pNode;
					brother->deleteKeyByIndex(brother->num - 1);

					return true;

				}
				else {
					brother->keys[brother->num] = parent->keys[index];
					parent->deleteKeyByIndex(index);
					brother->num++;

					for (int i = 0; i < pNode->num; i++) {
						brother->childs[brother->num + i] = pNode->childs[i];
						brother->keys[brother->num + i] = pNode->keys[i];
						brother->childs[brother->num + i]->parent = brother;
					}
					brother->childs[brother->num + pNode->num] = pNode->childs[pNode->num];
					brother->childs[brother->num + pNode->num]->parent = brother;

					brother->num += pNode->num;

					delete pNode;
					node_num--;

					return adjustAfterDelete(parent);
				}

			}
			else {
				if (parent->childs[0] == pNode)
					brother = parent->childs[1];
				else
					brother = parent->childs[index + 2];
				if (brother->num > minmumKeyNum - 1) {

					pNode->childs[pNode->num + 1] = brother->childs[0];
					pNode->keys[pNode->num] = brother->keys[0];
					pNode->childs[pNode->num + 1]->parent = pNode;
					pNode->num++;

					if (pNode == parent->childs[0])
						parent->keys[0] = brother->keys[0];
					else
						parent->keys[index + 1] = brother->keys[0];

					brother->childs[0] = brother->childs[1];
					brother->deleteKeyByIndex(0);

					return true;
				}
				else {

					pNode->keys[pNode->num] = parent->keys[index];

					if (pNode == parent->childs[0])
						parent->deleteKeyByIndex(0);
					else
						parent->deleteKeyByIndex(index + 1);

					pNode->num++;

					for (int i = 0; i < brother->num; i++) {
						pNode->childs[pNode->num + i] = brother->childs[i];
						pNode->keys[pNode->num + i] = brother->keys[i];
						pNode->childs[pNode->num + i]->parent = pNode;
					}
					pNode->childs[pNode->num + brother->num] = brother->childs[brother->num];
					pNode->childs[pNode->num + brother->num]->parent = pNode;

					pNode->num += brother->num;

					delete brother;
					node_num--;

					return adjustAfterDelete(parent);
				}

			}

		}

	}

	return false;
}

template<typename T>
inline bool Tree<T>::findToLeaf1(TreeNode1 pNode, T key, TreeNode1 &return_node, int &return_index)
{
	int index = 0;
	if (pNode->findKey1(key, index)) {
		//如果是叶节点
		if(pNode->isLeaf) {
			return_node = pNode;
			return_index = index;
			return true;
		}
		else {
			//此结点不是叶结点，递归查找它的下一层
			pNode = pNode->childs[index + 1];
			while (!pNode->isLeaf) {
				pNode = pNode->childs[0];
			}
			return_node = pNode;
			return_index = index;
			return true;
		}
	}
	//该结点内没有的话
	else{
		//如果是已经到了叶节点还没有
		if (pNode->isLeaf) {
			return_node = pNode;
			return_index = index;
			return false;
		}
		else {
			//递归寻找下一层
			findToLeaf1(pNode->childs[index], key, return_node, return_index);
		}


	}
	return false;
}

template<typename T>
inline bool Tree<T>::findToLeaf2(TreeNode1 pNode, T key, TreeNode1 &return_node, int &return_index)
{
	int index = 0;
	if (pNode->findKey2(key, index)) {
		//如果是叶节点
		if (pNode->isLeaf) {
			return_node = pNode;
			return_index = index;
			return true;
		}
		else {
			//此结点不是叶结点，递归查找它的下一层
			pNode = pNode->childs[index + 1];
			while (!pNode->isLeaf) {
				pNode = pNode->childs[0];
			}
			return_node = pNode;
			return_index = index;
			return true;
		}
	}
	//该结点内没有的话
	else {
		//如果是已经到了叶节点还没有
		if (pNode->isLeaf) {
			return_node = pNode;
			return_index = index;
			return false;
		}
		else {
			//递归寻找下一层
			findToLeaf1(pNode->childs[index],key, return_node, return_index);
		}
	}
	return false;
}


template<typename T>
inline bool Tree<T>::findMin(TreeNode1 root, T & key, TreeNode1 & return_node, int & return_index)
{
	return_node = root;
	while (! return_node->isLeaf) {
		return_node = return_node->childs[0];
	}
	key = return_node->keys[0];
	return_index = 0;
	return true;
}


template<typename T>
inline void Tree<T>::getFile(std::string file_path)
{
	FILE* f = fopen(file_path.c_str(), "r");
	if (f == NULL) {
		f = fopen(file_path.c_str(), "w+");
		fclose(f);
		f = fopen(file_path.c_str(), "r");
	}
	fclose(f);
	return;
}

template<typename T>
inline int Tree<T>::getBlockNum(std::string table_name)
{
	char* p;
	int block_num = -1;
	do {
		p = buffer_manager.getPage(table_name, block_num + 1);
		block_num++;
	} while (p[0] != '\0');
	return block_num;
}



template<typename T>
inline void Tree<T>::dropTree(TreeNode1 tree_root)
{
	if (!tree_root) {
		return ;
	}
	if(!tree_root->isLeaf){
		for (unsigned int i = 0; i <= tree_root->num; i++) {
			dropTree(tree_root->childs[i]);
			tree_root->childs[i] = NULL;
		}
	}
	delete tree_root;
	node_num--;
	return;
}

template<typename T>
inline void Tree<T>::searchRange(T & key1, T &key2, std::vector<int>& index_in_records, int flag)
{

	T temp_key1 = key1;
	T temp_key2 = key2;
	//空树
	if (!root) {
		return;
	}
	else {
		int index1,index2;
		TreeNode1 pNode1, pNode2;
		findToLeaf1(root, key1, pNode1, index1);
		findToLeaf2(root, key2, pNode2, index2);
		bool finished = false;
		unsigned int index;

		if (key1 <= key2) {
			TreeNode1 pNode = pNode1;
			index = index1;
			do {
				finished = pNode->findRange(index, key2, index_in_records);
				index = 0;
				if (pNode->nextLeafNode == NULL)
					break;
				else
					pNode = pNode->nextLeaf();
			} while (!finished);
		}
		else {
			TreeNode1 pNode = pNode2;
			index = index2;
			do {
				finished = pNode->findRange(index, key1, index_in_records);
				index = 0;
				if (pNode->nextLeafNode == NULL)
					break;
				else
					pNode = pNode->nextLeaf();
			} while (!finished);
		}
	}

	if (flag == 0) {
		if (temp_key1 == key1) {
			index_in_records.erase(index_in_records.begin());
		}
		if (temp_key2 == key2) {
			index_in_records.erase(index_in_records.end());
		}
	}
	else if (flag == 1) {
		if (temp_key2 == key2) {
			index_in_records.erase(index_in_records.end());
		}
	}
	else if (flag == 2) {
		if (temp_key1 == key1) {
			index_in_records.erase(index_in_records.begin());
		}
	}


	std::sort(index_in_records.begin(), index_in_records.end());
	index_in_records.erase(unique(index_in_records.begin(), index_in_records.end()), index_in_records.end());
	return;

}


template<typename T>
inline void Tree<T>::searchRange1(T & key2, std::vector<int>& index_in_records, int flag)
{
	T key_temp = key2;
	T  key1;
	//空树
	if (!root) {
		return;
	}
	else {
		int index1, index2;
		TreeNode1 pNode1, pNode2;
		findMin(root,key1, pNode1, index1);
		findToLeaf2(root, key2, pNode2, index2);
		bool finished = false;
		unsigned int index;


		TreeNode1 pNode = pNode1;
		index = index1;
		do {
			finished = pNode->findRange(index, key2, index_in_records);
			index = 0;
			if (pNode->nextLeafNode == NULL)
				break;
			else
				pNode = pNode->nextLeaf();
		} while (!finished);
	}

	if (flag == 0) {
		if (key_temp == key2) {
			index_in_records.erase(index_in_records.end());
		}
	}

	std::sort(index_in_records.begin(), index_in_records.end());
	index_in_records.erase(unique(index_in_records.begin(), index_in_records.end()), index_in_records.end());
	return;
}


template<typename T>
inline void Tree<T>::searchRange2(T & key, std::vector<int>& index_in_records, int flag)
{
	T key_temp = key;
	//空树
	if (!root) {
		return;
	}
	else {
		int index1;
		TreeNode1 pNode1;
		findToLeaf1(root, key, pNode1, index1);
		bool finished = false;
		unsigned int index;
		TreeNode1 pNode = pNode1;
		index = index1;
		do {
			finished = pNode->findRange2(index, index_in_records);
			index = 0;
			if (pNode->nextLeafNode == NULL)
				break;
			else
				pNode = pNode->nextLeaf();
		} while (!finished);
		
	}

	if (flag == 0) {
		if (key_temp == key) {
			index_in_records.erase(index_in_records.begin());
		}
	}
	std::sort(index_in_records.begin(), index_in_records.end());
	index_in_records.erase(unique(index_in_records.begin(), index_in_records.end()), index_in_records.end());
	return;

}


template<typename T>
inline void Tree<T>::readFromDiskAll()
{
	std::string fname = "./database/index/" + file_name;
	//std::string fname = file_name;
	getFile(fname);
	int block_num = getBlockNum(fname);

	if (block_num <= 0)
		block_num = 1;

	for (int i = 0; i < block_num; i++) {
		//获取当前块的句柄
		char* p = buffer_manager.getPage(fname, i);
		//char* t = p;
		//遍历块中所有记录

		readFromDisk(p, p + PAGE_SIZE);
	}
}

template<typename T>
inline void Tree<T>::writtenbackToDiskAll()
{
	std::string fname = "./database/index/" + file_name;
	//std::string fname = file_name;
	getFile(fname);
	int block_num = getBlockNum(fname);

	TreeNode1 ntmp = leafHead;
	int i, j;

	for (j = 0, i = 0; ntmp != NULL; j++) {
		char* p = buffer_manager.getPage(fname, j);
		int offset = 0;

		memset(p, 0, PAGE_SIZE);

		for (i = 0; i < ntmp->num; i++) {
			p[offset++] = '#';
			p[offset++] = ' ';

			copyString(p, offset, ntmp->keys[i]);
			p[offset++] = ' ';
			copyString(p, offset, ntmp->index_in_records[i]);
			p[offset++] = ' ';
		}

		p[offset] = '\0';

		int page_id = buffer_manager.getPageId(fname, j);
		buffer_manager.modifyPage(page_id);

		ntmp = ntmp->nextLeafNode;
	}

	while (j < block_num) {
		char* p = buffer_manager.getPage(fname, j);
		memset(p, 0, PAGE_SIZE);

		int page_id = buffer_manager.getPageId(fname, j);
		buffer_manager.modifyPage(page_id);

		j++;
	}

	return;
}

template<typename T>
inline void Tree<T>::readFromDisk(char * p, char * end)
{
	T key;
	int index_in_record;

	for (int i = 0; i < PAGE_SIZE; i++)
		if (p[i] != '#')
			return;
		else {
			i += 2;
			char tmp[100];
			int j;

			for (j = 0; i < PAGE_SIZE && p[i] != ' '; i++)
				tmp[j++] = p[i];
			tmp[j] = '\0';
			std::string s(tmp);
			std::stringstream stream(s);
			stream >> key;

			memset(tmp, 0, sizeof(tmp));

			i++;
			for (j = 0; i < PAGE_SIZE && p[i] != ' '; i++)
				tmp[j++] = p[i];
			tmp[j] = '\0';
			std::string s1(tmp);
			std::stringstream stream1(s1);
			stream1 >> index_in_record;

			insertKey(key, index_in_record);
		}
}
