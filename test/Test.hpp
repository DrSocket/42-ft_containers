#ifndef TEST_HPP
# define TEST_HPP
#include <iostream>
#include <string>

#ifndef STD
#define STD 0
#endif
#if STD
	#include <vector>
	#include <stack>
	#include <map>
	// #include <set>
	namespace ft = std;
#else
	#include "vector.hpp"
	#include "stack.hpp"
	#include "map.hpp"
	// #include "set.hpp"
#endif

void vectorTest();
void stackTest();
void mapTest();
// void setTest();

class Test {
	public:
		Test(void) {}
		Test(Test const & src) : _i(src._i), _str(src._str) {}
		Test(int const i, std::string const & str) : _i(i), _str(str) {}
		~Test(void) {}

		Test & operator=(Test const & rhs);

		int getI(void) const;
		std::string getStr(void) const;

	private:
		int _i;
		std::string _str;
};

bool operator== (Test const & lhs, Test const & rhs);

bool operator!= (Test const & lhs, Test const & rhs);

bool operator< (Test const & lhs, Test const & rhs);

bool operator<= (Test const &lhs, Test const & rhs);

bool operator> (Test const & lhs, Test const & rhs);

bool operator>= (Test const &lhs, Test const & rhs);

#endif