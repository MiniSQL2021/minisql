#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "basic.h"
#include "exception.h"

template <typename T>
class TreeNode {
private:
	//�ý����key����
	int num;
	//ָ�򸸽ڵ�ָ��
	TreeNode* parent;
	//���key����
	std::vector <T> keys;
	//ָ���ӽ���ָ������
	std::vector <TreeNode*> childs;
	std::vector <int> index_in_records;
	//ָ����һ��Ҷ����ָ��
	TreeNode* nextLeafNode;
	//�˽���Ƿ���Ҷ���ı�־
	bool isLeaf;
	//�����Ķ�
	int degree;

public:

	TreeNode(int in_degree, bool Leaf = false);
	//��������
	~TreeNode();
	bool isRoot();
	bool findKey(T key, int &index);
	TreeNode* splitNode(T &key);
	int addKey(T &key);
	int addKey(T &key, int index_in_records);
	bool deleteKeyByIndex(int index);
	TreeNode* nextLeaf();
	bool findRange(int index, T& key, std::vector<int>& index_in_records);

};



//����һ��TreeNode�������Ҷ�ӽڵ㣬Leaf=True
template<typename T>
inline TreeNode<T>::TreeNode(int in_degree, bool Leaf):
	num(0),
	parent(NULL),
	nextLeafNode(NULL),
	isLeaf(Leaf),
	degree(in_degree)
{
	for (int i = 0; i < degree + 1; i++) {
		childs.push_back(NULL);
		keys.push_back(T());
		index_in_records.push_back(int());
	}
	//��βָ��
	childs.push_back(NULL);
}
template<typename T>
//����
inline TreeNode<T>::~TreeNode()
{
}


//�ж��Ƿ�Ϊ���ڵ�
template<typename T>
inline bool TreeNode<T>::isRoot()
{
	if (parent != NULL) {
		return false;
	}
	else {
		return false;
	}
}

//��Node�в���keyֵ������index�������е�λ��
template<typename T>
inline bool TreeNode<T>::findKey(T key, int & index)
{
	if (num == 0) { //�����key����Ϊ0
		index = 0;
		return false;
	}
	else {
		//�ж�keyֵ�Ƿ񳬹�����������ֵ(key���ڱ������)
		if (keys[num - 1] < key) {
			index = num;
			return false;
			//�ж�keyֵ�Ƿ�С�ڱ��������Сֵ(key���ڱ������)
		}
		else if (keys[0] > key) {
			index = 0;
			return false;
		}
		else if (num <= 20) {
			//�����key��������ʱֱ�����Ա�����������
			for (int i = 0; i < num; i++) {
				if (keys[i] == key) {
					index = i;
					return true;
				}
				else if (keys[i] < key)
					continue;
				else if (keys[i] > key) {
					index = i;
					return false;
				}
			}
		}
		else if (num > 20) {
			//�����key��������ʱ���ö�������
			int left = 0, right = num - 1, pos = 0;

			while (right > left + 1) {
				pos = (right + left) / 2;
				if (keys[pos] == key) {
					index = pos;
					return true;
				}
				else if (keys[pos] < key) {
					left = pos;
				}
				else if (keys[pos] > key) {
					right = pos;
				}
			}

			if (keys[left] >= key) {
				index = left;
				return (keys[left] == key);
			}
			else if (keys[right] >= key) {
				index = right;
				return (keys[right] == key);
			}
			else if (keys[right] < key) {
				index = right++;
				return false;
			}
		}//������������
	}

	return false;

}


//������
template<typename T>
inline TreeNode<T> * TreeNode<T>::splitNode(T & key)
{
	//��С�������
	int minmumNodeNum = (degree - 1) / 2;
	TreeNode* newnode = new TreeNode(degree, this->isLeaf);

	//�����Ҷ�ڵ�
	if (isLeaf) {
		key = keys[minmumNodeNum + 1];
		//���Ұ벿�������½ڵ�
		for (int i = minmumNodeNum + 1; i < degree; i++) {
			newnode->keys[i - minmumNodeNum - 1] = keys[i];
			keys[i] = T();
			newnode->index_in_records[i - minmumNodeNum - 1] = index_in_records[i];
			index_in_records[i] = int();
		}
		newnode->nextLeafNode = this->nextLeafNode;
		this->nextLeafNode = newnode;
		newnode->parent = this->parent;

		newnode->num = minmumNodeNum;
		this->num = minmumNodeNum + 1;
	}
	else {
		key = keys[minmumNodeNum];
		//��������ָ�룬�޸ĺ��ӵĸ�ָ��
		for (int i = minmumNodeNum + 1; i < degree + 1; i++) {
			newnode->childs[i - minmumNodeNum - 1] = this->childs[i];
			newnode->childs[i - minmumNodeNum - 1]->parent = newnode;
			this->childs[i] = NULL;
		}
		//����keyֵ���½��
		for (int i = minmumNodeNum + 1; i < degree; i++) {
			newnode->keys[i - minmumNodeNum - 1] = this->keys[i];
			this->keys[i] = T();
		}
		this->keys[minmumNodeNum] = T();
		newnode->parent = this->parent;
		newnode->num = minmumNodeNum;
		this->num = minmumNodeNum;
	}

	return newnode;

}

//��Ҷ�ӽڵ����key
template<typename T>
inline int TreeNode<T>::addKey(T & key)
{
	if (num == 0) {
		keys[0] = key;
		num++;
		return 0;
	}
	else {
		int index = 0;
		bool exist = findKey(key, index);
		if (exist == 1){
			throw addKey_already_in();
		}
		else {
			//��������keyֵ
			for (int i = num; i > index; i--)
				keys[i] = keys[i - 1];
			keys[index] = key;

			//�����ӽ��ָ�����
			for (int i = num + 1; i > index + 1; i--)
				childs[i] = childs[i - 1];
			childs[index + 1] = NULL;
			num++;
			return index;
		}
	}
}

//Ҷ�ӽ�����key
template<typename T>
inline int TreeNode<T>::addKey(T & key, int index_in_record)
{
	if (!isLeaf) {
		return -1;
	}
	//�����û��keyֵ
	if (num == 0) {
		keys[0] = key;
		index_in_records[0] = index_in_record;
		num++;
		return 0;
	}
	else {
		int index = 0;
		bool a = findKey(key, idnex_in_record);
		if (a) {
			throw addKey_already_in();
		}
		else {
			int i;
			for (i = num; i > index; i--) {
				keys[i] = keys[i - 1];
				index_in_records[i] = index_in_records[i - 1];
			}
			keys[i] = key;
			index_in_records[i] = index_in_record;
			num++;
			return index;
		}
	}
	return 0;
}

//ɾ��key
template<typename T>
inline bool TreeNode<T>::deleteKeyByIndex(int index)
{
	//index����
	if(index>num){
		return false;
	}
	else {
		if (isLeaf) {
			
			for (int i = index; i < num - 1; i++) {
				keys[i] = keys[i + 1];
				index_in_records = index_in_records[i + 1];
			}
			keys[num - 1] = T();
			index_in_records[num - 1] = int();

		}
		//��Ҷ�ӽ��
		else {
			for (unsigned int i = index; i < num - 1; i++) {
				keys[i] = keys[i + 1];
			}
			//�����ӽ��ָ��
			for (unsigned int i = index + 1; i < num; i++) {
				childs[i] = childs[i + 1];
			}
			keys[num - 1] = T();
			childs[num] = NULL;
		}
		num--;
		return true;
	}
	return false;
}

template <typename T>
inline TreeNode<T>* TreeNode<T>::nextLeaf()
{
	return nextLeafNode;
}


//������ʼindex������keyֹͣ������һ��װ��index_in_record�����飺return_index_in_records
template<typename T>
inline bool TreeNode<T>::findRange(int index, T & key, std::vector<int>& return_index_in_records)
{
	int i;
	for ( i = index; i < num && keys[i] <= key; i++) {
		return_index_in_records.push_back(index_in_records[i]);
	}
	if (keys[i] > key)
		return true;
	else
		return false;
}




