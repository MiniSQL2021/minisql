#pragma once
#include <sstream>
#include <string>
#include <map>
#include "buffer_manager.h"
#include "Tree.h"


struct Data {
	int type;
	int datai;
	float dataf;
	std::string datas;
};
class Index{

public :
	//���캯��
	Index(std::string table_name, Attribute attr);  //���attr��API�����catlog��ȡ�ı���Ϣ
	//��������
	~Index();
	//���룺Index�ļ���(·��)��������key������
	//�����void
	//���ܣ����������ļ���B+��
	//�쳣��
	void createIndex(std::string file_path, int type);
	//���룺Index�ļ���(·��)��������key������
	//�����void
	//���ܣ�ɾ��������B+�����ļ�
	//�쳣��
	void dropIndex(std::string file_path, int type);
	//���룺Index�ļ���(·��)��������key(��������)
	//�����void
	//���ܣ����������ļ���B+��
	//�쳣��
	int findIndex(std::string file_path, Data data);
	//���룺Index�ļ���(·��)��������key(��������)��block_id
	//�����void
	//���ܣ���ָ�������в���һ��key
	//�쳣��
	void insertIndex(std::string file_path, Data data, int block_id);
	//���룺Index�ļ���(·��)��������key(��������)
	//�����void
	//���ܣ���������ɾ����Ӧ��Key
	//�쳣��
	void deleteIndexByKey(std::string file_path, Data data);
	//���룺Index�ļ���(·��)��������key1(��������)��������key2(��������)�����ص�index_in_records����
	//�����void
	//���ܣ���Χ���ң�����һ����Χ�ڵ�index_in_record
	//�쳣��
	void searchRange(std::string file_path, Data data1, Data data2, std::vector<int>& index_in_records);

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


	//����B+���ʺϵ�degree
	int getDegree(int type);

	//���㲻ͬ����Key��size
	int getKeySize(int type);

};
