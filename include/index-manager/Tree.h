#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "basic.h"
#include"TreeNode.h"
#include "exception.h"
#include "buffer_manager.h"

extern BufferManager buffer_manager;




template <typename T>
class Tree {
private:
	//������TreeNodeָ�룬�����߽��в�������
	typedef TreeNode<T>* TreeNode;
	//�ļ���
	std::string file_name;
	//���ڵ�
	TreeNode root;
	//Ҷ�ڵ�ͷָ��
	TreeNode leafHead;
	int key_num;
	int level;
	int node_num;
	int key_size;
	int degree;


	//��ʼ��B+�����������ڴ�ռ�
	bool initialization();
	//���ڲ���ĳkey����������������������е���
	bool adjustAfterinsert(TreeNode pNode);
	//����ɾ��ĳkey����ܳ��ֽ�������������������е���
	bool adjustAfterDelete(TreeNode pNode);
	//���ڲ���ĳkeyֵ������Ҷ���λ��
	bool findToLeaf(TreeNode pNode, T key, TreeNode &return_node, int &return_index);
	//��ȡ�ļ���С
	void getFile(std::string file_path);
	int getBlockNum(std::string table_name);

public:
	//���캯��
	//���ڹ���һ���µ�����ȷ��m_name,key��size�����Ķ�
	//ͬʱ������������Ϊ���������ڴ�
	Tree(std::string m_name, int key_size, int degree);
	//��������
	//�ͷ���Ӧ���ڴ�
	~Tree();

	//����keyֵ���ض�Ӧ��index_in_record
	int searchKey(T &key);

	//���룺keyֵ����index_in_record
	//�����bool
	//���ܣ������в���һ��keyֵ
	//�����Ƿ����ɹ�
	bool insertKey(T &key, int index_in_record);

	//���룺keyֵ
	//�����bool
	//���ܣ�������ɾ��һ��keyֵ
	//�����Ƿ�ɾ���ɹ�
	bool deleteKey(T &key);

	//���룺���ĸ����
	//���ܣ�ɾ�����������ͷ��ڴ�ռ䣬��Ҫ��������������
	void dropTree(TreeNode tree_node);

	//���룺key1��key2������index_in_records������
	//���ܣ����ط�Χ�����������index_in_record����index_in_records������
	void searchRange(T &key1, T &key2, std::vector<int>& index_in_records, int flag);

	//�Ӵ��̶�ȡ��������
	void readFromDiskAll();
	//��������д�����
	void writtenbackToDiskAll();
	//�ڴ����ж�ȡĳһ�������
	void readFromDisk(char *p, char* end);


};


//New Tree
template<typename T>
inline Tree<T>::Tree(std::string in_name, int key_size, int in_degree):
	file_name(in_name),
	key_num(0),
	level(0),
	node_num(0),
	root(NULL),
	leafHead(NULL),
	key_size(key_size),
	degree(in_degree)
{
	//��ʼ������ȡ����
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
	TreeNode return_node;
	bool a = findToLeaf(root, key, return_node, return_index);
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
	TreeNode pNode;
	int index;
	//����㲻����
	if (!root)
		initialization();
	//���Ҳ���ֵ�Ƿ����
	bool ifFound = findToLeaf(root, key, pNode, index);
	if (ifFound) { //�Ѵ���
		
		return false;
	}
	else { //�����ڣ����Բ���
		pNode->addKey(key, index_in_record);
		//�������������Ҫ���е���
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
	TreeNode pNode;
	int index;
	//����㲻����
	if (!root) {
		throw deleteKey_no_node_in_tree ;
	
		return false;
	}
	else { //�������в���
	 //����λ��
		bool ifFound = findToLeaf(root, key, pNode, index);
		if (!ifFound) { //�Ҳ�����key
			throw deleteKey_no_keys_in_tree;
			return false;
		}
		else { //�����ҵ�����ɾ��
			if (pNode->isRoot()) { //��ǰΪ�����
				pNode->deleteKeyByIndex(index);
				key_num--;
				return adjustAfterDelete(pNode);
			}
			else {
				if (index == 0 && leafHead != pNode) {
					//key������֦�ɽ����
					//����һ��ȥ����֦�ɲ�
					int i = 0;

					TreeNode now_parent = pNode->parent;
					bool if_found_inBranch = now_parent->findKey(key, i);
					while (!if_found_inBranch) {
						if (now_parent->parent)
							now_parent = now_parent->parent;
						else
							break;
						if_found_inBranch = now_parent->findKey(key, i);
					}

					now_parent->keys[i] = pNode->keys[1];

					pNode->deleteKeyByIndex(i);
					key_num--;
					return adjustAfterDelete(pNode);

				}
				else { //ͬʱ��Ȼ������Ҷ���
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
	root = new TreeNode<T>(degree, true);
	key_num = 0;
	level = 1;
	node_num = 1;
	leafHead = root;
	return true;
}

template<typename T>
inline bool Tree<T>::adjustAfterinsert(TreeNode pNode)
{
	T key;
	TreeNode newNode = pNode->splitNode(key);
	node_num++;

	//��ǰ���Ϊ��������
	if (pNode->isRoot()) {
		TreeNode root = new TreeNode<T>(degree, false);
		if (root == NULL) {
			throw adjustAfterinser_can_not_allocate_the_new_root;
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
	else { //��ǰ���Ǹ����
		Tree parent = pNode->parent;
		int i = parent->addKey(key);

		parent->childs[i + 1] = newNode;
		newNode->parent = parent;
		//�ݹ���е���
		if (parent->num == degree)
			return adjustAfterinsert(parent);

		return true;
	}

	return false;
}

template<typename T>
inline bool Tree<T>::adjustAfterDelete(TreeNode pNode)
{
	int minmumKeyNum = (degree - 1) / 2;
	//���ֲ���Ҫ���������
	if (((pNode->isLeaf) && (pNode->num >= minmumKeyNum)) ||
		((degree != 3) && (!pNode->isLeaf) && (pNode->num >= minmumKeyNum - 1)) ||
		((degree == 3) && (!pNode->isLeaf) && (pNode->num < 0))) {
		return  true;
	}
	if (pNode->isRoot()) { //��ǰ���Ϊ�����
		//����Ҫ����
		if (pNode->num > 0) {
			return true;
		}
		//������Ҫ����
		else { 
			if (root->isLeaf) { //����Ϊ�������
				delete pNode;
				root = NULL;
				leafHead = NULL;
				level--;
				node_num--;
			}
			else { //���ڵ㽫��Ϊ��ͷ��
				root = pNode->childs[0];
				root->parent = NULL;
				delete pNode;
				level--;
				node_num--;
			}
		}
	}
	else { //�Ǹ��ڵ����
		TreeNode parent = pNode->parent, brother = NULL;
		if (pNode->isLeaf) { //��ǰΪҶ�ڵ�
			int index = 0;
			parent->findKey(pNode->keys[0], index);

			//ѡ�����ֵ�
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
		else { //֦�ɽڵ����
			int index = 0;
			parent->findKey(pNode->childs[0]->keys[0], index);
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
inline bool Tree<T>::findToLeaf(TreeNode pNode, T key, TreeNode &return_node, int &return_index)
{
	int index = 0;
	if (pNode->findKey(key, index)) {
		//�����Ҷ�ڵ�
		if(pNode->isLeaf) {
			return_node = pNode;
			return_index = index;
			return true;
		}
		else {
			//�˽�㲻��Ҷ��㣬�ݹ����������һ��
			pNode = pNode->childs[index + 1];
			while (!pNode->isLeaf) {
				pNode = pNode->childs[0];
			}
			return_node = pNode;
			return_index = index;
			return true;
		}
	}
	//�ý����û�еĻ�
	else{
		//������Ѿ�����Ҷ�ڵ㻹û��
		if (pNode->isLeaf) {
			return_node = pNode;
			return_index = index;
			return false;
		}
		else {
			//�ݹ�Ѱ����һ��
			findToLeaf(pNode->childs[index], return_node, return_index);
		}


	}
	return false;
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
inline void Tree<T>::dropTree(TreeNode tree_root)
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
inline void Tree<T>::searchRange(T & key1, T & key2, std::vector<int>& index_in_records, int flag)
{
	//����
	if (!root) {
		return;
	}
	else {
		int index1,index2;
		TreeNode pNode1, pNode2;
		findToLeaf(root, key1, pNode1, index1);
		findToLeaf(root, key2, pNode2, index2);
		bool finished = false;
		unsigned int index;

		if (key1 <= key2) {
			TreeNode pNode = pNode1;
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
			TreeNode pNode = pNode2;
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
		//��ȡ��ǰ��ľ��
		char* p = buffer_manager.getPage(fname, i);
		//char* t = p;
		//�����������м�¼

		readFromDisk(p, p + PAGESIZE);
	}
}

template<typename T>
inline void Tree<T>::writtenbackToDiskAll()
{
	std::string fname = "./database/index/" + file_name;
	//std::string fname = file_name;
	getFile(fname);
	int block_num = getBlockNum(fname);

	TreeNode ntmp = leafHead;
	int i, j;

	for (j = 0, i = 0; ntmp != NULL; j++) {
		char* p = buffer_manager.getPage(fname, j);
		int offset = 0;

		memset(p, 0, PAGESIZE);

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
		memset(p, 0, PAGESIZE);

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

	for (int i = 0; i < PAGESIZE; i++)
		if (p[i] != '#')
			return;
		else {
			i += 2;
			char tmp[100];
			int j;

			for (j = 0; i < PAGESIZE && p[i] != ' '; i++)
				tmp[j++] = p[i];
			tmp[j] = '\0';
			std::string s(tmp);
			std::stringstream stream(s);
			stream >> key;

			memset(tmp, 0, sizeof(tmp));

			i++;
			for (j = 0; i < PAGESIZE && p[i] != ' '; i++)
				tmp[j++] = p[i];
			tmp[j] = '\0';
			std::string s1(tmp);
			std::stringstream stream1(s1);
			stream1 >> index_in_record;

			insertKey(key, index_in_record);
		}
}
