#pragma once

#include <exception>


class addKey_already_in : public std::exception {
	//�����key�Ѵ���
};


class addKeyInLeafButNotLeaf : public std::exception {
	//����Ҷ�ӽ������������Ҷ�ӽ�����
};


class dropIndex_cannot_find_index : public std::exception {
};

class findIndex_cannot_find_index: public std::exception {
	//
};

class insertIndex_cannot_find_file_path  : public std::exception {
	//
};

class deleteIndex_cannot_find_with_file_path : public std::exception {
	//
};
class searchIndex_cannot_find_with_file_path : public std::exception {
	//
};
class getKeySize_wrong: public std::exception {
	//
};
class deleteKey_no_node_in_tree : public std::exception {
	//
};
class deleteKey_no_keys_in_tree : public std::exception {
	//
};
class adjustAfterinser_can_not_allocate_the_new_root : public std::exception {
	//
};
