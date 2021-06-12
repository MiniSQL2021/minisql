#pragma once

#include <exception>


class addKey_already_in : public std::exception {
	//插入的key已存在
};


class addKeyInLeafButNotLeaf : public std::exception {
	//向用叶子结点插入命令向非叶子结点插入
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
