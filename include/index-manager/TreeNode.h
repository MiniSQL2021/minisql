#pragma once

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include "basic.h"
#include "exception.h"

template<typename T>
class TreeNode {
private:
    //该结点内key数量
    int num;
    //指向父节点指针
    TreeNode *parent;
    //存放key容器
    std::vector<T> keys;
    //指向子结点的指针容器
    std::vector<TreeNode *> childs;
    std::vector<int> index_in_records;
    //指向下一个叶结点的指针
    TreeNode *nextLeafNode;
    //此结点是否是叶结点的标志
    bool isLeaf;
    //此树的度
    int degree;

public:

    TreeNode(int in_degree, bool Leaf = false);

    //析构函数
    ~TreeNode();

    bool isRoot();

    bool findKey1(T key, int &index);

    bool findKey2(T key, int &index);

    TreeNode *splitNode(T &key);

    int addKey(T &key);

    int addKey(T &key, int index_in_records);

    bool deleteKeyByIndex(int index);

    TreeNode *nextLeaf();

    bool findRange(int index, T &key, std::vector<int> &index_in_records);

    bool findRange1(int index, T &key, std::vector<int> &index_in_records);

    bool findRange2(int index, std::vector<int> &index_in_records);

};

//创建一个TreeNode，如果是叶子节点，Leaf=True
template<typename T>
inline TreeNode<T>::TreeNode(int in_degree, bool Leaf):
        num(0),
        parent(NULL),
        nextLeafNode(NULL),
        isLeaf(Leaf),
        degree(in_degree) {
    for (int i = 0; i < degree + 1; i++) {
        childs.push_back(NULL);
        keys.push_back(T());
        index_in_records.push_back(int());
    }
    //结尾指针
    childs.push_back(NULL);
}

template<typename T>
//析构
inline TreeNode<T>::~TreeNode() {
}

//判断是否为根节点
template<typename T>
inline bool TreeNode<T>::isRoot() {
    if (parent != NULL) {
        return false;
    } else {
        return false;
    }
}

//在Node中查找key值，利用index带回树中的位置
template<typename T>
inline bool TreeNode<T>::findKey1(T key, int &index) {
    if (num == 0) { //结点内key数量为0
        index = 0;
        return false;
    } else {
        //判断key值是否超过本结点内最大值(key不在本结点内)
        if (keys[num - 1] < key) {
            index = num;
            return false;
            //判断key值是否小于本结点内最小值(key不在本结点内)
        } else if (keys[0] > key) {
            index = 0;
            return false;
        } else if (num <= 20) {
            //结点内key数量较少时直接线性遍历搜索即可
            for (int i = 0; i < num; i++) {
                if (keys[i] == key) {
                    index = i;
                    return true;
                } else if (keys[i] < key)
                    continue;
                else if (keys[i] > key) {
                    index = i;
                    return false;
                }
            }
        } else if (num > 20) {
            //结点内key数量过多时采用二分搜索
            int left = 0, right = num - 1, pos = 0;

            while (right > left + 1) {
                pos = (right + left) / 2;
                if (keys[pos] == key) {
                    index = pos;
                    return true;
                } else if (keys[pos] < key) {
                    left = pos;
                } else if (keys[pos] > key) {
                    right = pos;
                }
            }

            if (keys[left] >= key) {
                index = left;
                return (keys[left] == key);
            } else if (keys[right] >= key) {
                index = right;
                return (keys[right] == key);
            } else if (keys[right] < key) {
                index = right++;
                return false;
            }
        }//二分搜索结束
    }

    return false;

}

//在Node中查找key值，利用index带回树中的位置
template<typename T>
inline bool TreeNode<T>::findKey2(T key, int &index) {
    if (num == 0) { //结点内key数量为0
        index = 0;
        return false;
    } else {
        //判断key值是否超过本结点内最大值(key不在本结点内)
        if (keys[num - 1] < key) {
            index = num;
            return false;
            //判断key值是否小于本结点内最小值(key不在本结点内)
        } else if (keys[0] > key) {
            index = 0;
            return false;
        } else if (num <= 20) {
            //结点内key数量较少时直接线性遍历搜索即可
            for (int i = 0; i < num; i++) {
                if (keys[i] == key) {
                    index = i;
                    return true;
                } else if (keys[i] < key)
                    continue;
                else if (keys[i] > key) {
                    index = i - 1;
                    return false;
                }
            }
        } else if (num > 20) {
            //结点内key数量过多时采用二分搜索
            int left = 0, right = num - 1, pos = 0;

            while (right > left + 1) {
                pos = (right + left) / 2;
                if (keys[pos] == key) {
                    index = pos;
                    return true;
                } else if (keys[pos] < key) {
                    left = pos;
                } else if (keys[pos] > key) {
                    right = pos;
                }
            }

            if (keys[right] <= key) {
                index = right;
                return (keys[right] == key);
            } else if (keys[left] <= key) {
                index = left;
                return (keys[left] == key);
            } else if (keys[left] > key) {
                index = left--;
                return false;
            }
        }//二分搜索结束
    }

    return false;

}

//结点分裂
template<typename T>
inline TreeNode<T> *TreeNode<T>::splitNode(T &key) {
    //最小结点数量
    int minmumNodeNum = (degree - 1) / 2;
    TreeNode *newnode = new TreeNode(degree, this->isLeaf);

    //如果是叶节点
    if (isLeaf) {
        key = keys[minmumNodeNum + 1];
        //将右半部分填入新节点
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
    } else {
        key = keys[minmumNodeNum];
        //拷贝孩子指针，修改孩子的父指针
        for (int i = minmumNodeNum + 1; i < degree + 1; i++) {
            newnode->childs[i - minmumNodeNum - 1] = this->childs[i];
            newnode->childs[i - minmumNodeNum - 1]->parent = newnode;
            this->childs[i] = NULL;
        }
        //拷贝key值至新结点
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

//非叶子节点添加key
template<typename T>
inline int TreeNode<T>::addKey(T &key) {
    if (num == 0) {
        keys[0] = key;
        num++;
        return 0;
    } else {
        int index = 0;
        bool exist = findKey(key, index);
        if (exist == 1) {
            throw addKey_already_in();
        } else {
            //调整其他key值
            for (int i = num; i > index; i--)
                keys[i] = keys[i - 1];
            keys[index] = key;

            //调整子结点指针情况
            for (int i = num + 1; i > index + 1; i--)
                childs[i] = childs[i - 1];
            childs[index + 1] = NULL;
            num++;
            return index;
        }
    }
}

//叶子结点添加key
template<typename T>
inline int TreeNode<T>::addKey(T &key, int index_in_record) {
    if (!isLeaf) {
        return -1;
    }
    //结点内没有key值
    if (num == 0) {
        keys[0] = key;
        index_in_records[0] = index_in_record;
        num++;
        return 0;
    } else {
        int index = 0;
        bool a = findKey(key, index_in_record);
        if (a) {
            throw addKey_already_in();
        } else {
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

//删除key
template<typename T>
inline bool TreeNode<T>::deleteKeyByIndex(int index) {
    //index错误
    if (index > num) {
        return false;
    } else {
        if (isLeaf) {

            for (int i = index; i < num - 1; i++) {
                keys[i] = keys[i + 1];
                index_in_records = index_in_records[i + 1];
            }
            keys[num - 1] = T();
            index_in_records[num - 1] = int();

        }
            //非叶子结点
        else {
            for (unsigned int i = index; i < num - 1; i++) {
                keys[i] = keys[i + 1];
            }
            //调整子结点指针
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

template<typename T>
inline TreeNode<T> *TreeNode<T>::nextLeaf() {
    return nextLeafNode;
}

//查找起始index到等于key停止，返回一个装有index_in_record的数组：return_index_in_records
template<typename T>
inline bool TreeNode<T>::findRange(int index, T &key, std::vector<int> &return_index_in_records) {
    int i;
    for (i = index; i < num && keys[i] <= key; i++) {
        return_index_in_records.push_back(index_in_records[i]);
    }
    if (keys[i] > key)
        return true;
    else
        return false;
}

template<typename T>
inline bool TreeNode<T>::findRange2(int index, std::vector<int> &return_index_in_records) {
    int i;
    for (i = index; i < num; i++) {
        return_index_in_records.push_back(index_in_records[i]);
    }
    return true;

}
