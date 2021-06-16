#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_ 1

#include <exception>

class table_does_not_exist : public std::exception {

};

class attr_does_not_exist : public std::exception {

};

class index_does_not_exist : public std::exception {

};

class attr_does_not_unique : public std::exception {

};

class index_already_exist : public std::exception {

};

class illegal_data : public std::exception {

};

#endif #pragma once
