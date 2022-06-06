#include "Test.hpp"
#include <iostream>
#include <string>

template < class T >
void	setprintSize(ft::set<T> s) {
	std::cout << "size: " << s.size() << std::endl;
	std::cout << "maxSize: " << s.max_size() << std::endl;
	std::cout << std::endl;
}

template < class T, class Compare >
void	setprintSize(ft::set<T, Compare> s) {
	std::cout << "size: " << s.size() << std::endl;
	std::cout << "maxSize: " << s.max_size() << std::endl;
	std::cout << std::endl;
}

bool	fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp { bool operator() (const int& lhs, const int& rhs) const { return lhs < rhs; } };

/**
 * @brief constructor test
 */

void	setconstructTest(void) {

	std::cout << "empty construct:\n";
	ft::set<int> s1;
	setprintSize(s1);
	
    int i[] = {10, 20, 30, 40, 50};
	std::cout << "range: i -> i + 5:\n";
	ft::set<int> s2(i, i + 5);
	setprintSize(s2);
	
	std::cout << "copy: s3(s2):\n";
	ft::set<int> s3(s2);
	setprintSize(s3);

	std::cout << "range with iterator\n";
	ft::set<int> s4(s2.begin(), s2.end());
	setprintSize(s4);

	std::cout << "class as Compare\n";
	ft::set<int, classcomp> s5; 
	setprintSize(s5);

	std::cout << "function pointer as Compare\n";
	bool (*fn_pt)(int, int) = fncomp;
	ft::set<int, bool (*)(int, int)> s6(fn_pt);
	setprintSize(s6);

	std::cout << "s1 = s2\n";
	s1 = s2;
	std::cout << "clear s2\n";
	s2.clear();

	std::cout << "s1:\n";
	setprintSize(s1);
	std::cout << "s2:\n";
	setprintSize(s2);
}

/**
 * @brief iterator test
*/

void	setiteratorTest(void) {

	int i[] = {10, 20, 30, 40, 50};
	std::cout << "range: i -> i + 5:\n";
	ft::set<int> s1(i, i + 5);
	setprintSize(s1);

	ft::set<int>::iterator it = s1.begin();
	std::cout << "begin -> end:\n";
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	it = s1.begin();

	ft::set<int>::const_iterator cit = it;

	std::cout << "cmp it == const it: ";
	if (cit == it)
		std::cout << "Yes" << std::endl;
	else
		std::cout << "No" << std::endl;

	std::cout << "rbegin -> rend:\n";
	ft::set<int>::reverse_iterator rit = s1.rbegin();
	ft::set<int>::reverse_iterator rite = s1.rend();
	for (; rit != rite; rit++)
		std::cout << *rit << std::endl;
	std::cout << std::endl;
}

/**
 * @brief empty test
*/

void	setemptyTest(void) {

	std::cout << "set<int>\n";
	ft::set<int> s1;
	std::cout << (s1.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	setprintSize(s1);

	std::cout << "set<int> + 1: ";
	s1.insert(1);
	std::cout << (s1.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	setprintSize(s1);

	std::cout << "set<Test>\n";
	ft::set<Test> s2;
	std::cout << (s2.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	setprintSize(s2);

	std::cout << "set<Test> + 1: ";
	s2.insert(Test(1, "Test"));
	std::cout << (s2.empty() == true ? "s1 is empty" : "s1 is not empty") << std::endl;
	setprintSize(s2);
}

/**
 * @brief size/max_size test
*/

void	setsizeTest(void) {

	std::cout << "set<int>\n";
	ft::set<int> s1;
	setprintSize(s1);

	std::cout << "set<char>\n";
	ft::set<char> s2;
	setprintSize(s2);

	std::cout << "set<short>\n";
	ft::set<short> s3;
	setprintSize(s3);

	std::cout << "set<long long>\n";
	ft::set<long long> s4;
	setprintSize(s4);

	std::cout << "set<double>\n";
	ft::set<double> s5;
	setprintSize(s5);

	std::cout << "set<float>\n";
	ft::set<float> s6;
	setprintSize(s6);

	std::cout << "set<Test>\n";
	ft::set<Test> s7;
	setprintSize(s7);
}

/**
 * @brief insert test
*/

void	setinsertTest(void) {

	std::cout << "set<int>\n";
	ft::set<int> s1;
	setprintSize(s1);

	std::cout << "insert 100\n";
	s1.insert(100);
	setprintSize(s1);
	std::cout << "insert 200\n";
	s1.insert(200);
	setprintSize(s1);
	std::cout << "insert 300\n";
	s1.insert(300);
	setprintSize(s1);
	std::cout << "insert 400\n";
	s1.insert(400);
	setprintSize(s1);

	std::cout << "show content:\n";
	ft::set<int>::iterator it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	std::cout << "set<Test>\n";
	ft::set<Test> s2;
	setprintSize(s2);

	std::cout << "insert Test(1, \"c\")\n";
	s2.insert(Test(1, "c"));
	setprintSize(s2);
	std::cout << "insert Test(2, \"u\")\n";
	s2.insert(Test(2, "u"));
	setprintSize(s2);
	std::cout << "insert Test(3, \"s\")\n";
	s2.insert(Test(3, "s"));
	setprintSize(s2);
	std::cout << "insert Test(4, \"t\")\n";
	s2.insert(Test(4, "t"));
	setprintSize(s2);
	std::cout << "insert Test(5, \"o\")\n";
	s2.insert(Test(5, "o"));
	setprintSize(s2);
	std::cout << "insert Test(6, \"m\")\n";
	s2.insert(Test(6, "m"));
	setprintSize(s2);

	std::cout << "show content:\n";
	ft::set<Test>::iterator it2 = s2.begin();
	for (; it2 != s2.end(); it2++)
		std::cout << it2->getStr() << std::endl;
	std::cout << std::endl;

	std::cout << "insert Test(1, 'c') again (single insert):\n";
	ft::pair<ft::set<Test>::iterator, bool> get = s2.insert(Test(1, "c"));
	std::cout << std::boolalpha;
	std::cout << "iterator ret: \'" << get.first->getStr() << "\' and bool ret: " << get.second << std::endl;
	setprintSize(s2);
	
	std::cout << "insert Test(7, \"something\") (hint insert):\n";
	ft::set<Test>::iterator itc = s2.begin();
	itc++;
	itc++;

	s2.insert(itc, Test(7, "something"));
	std::cout << "show content:\n";
	it2 = s2.begin();
	for (; it2 != s2.end(); it2++)
		std::cout << it2->getStr() << std::endl;
	std::cout << std::endl;
	
	std::cout << "insert content of s2 (2u 3s 4t 5o) -> s3 (range):\n";
	ft::set<Test> s3;
	setprintSize(s3);
	itc = s2.begin();
	ft::set<Test>::iterator itc2 = s2.end();

	itc++;
	itc2--;
	itc2--;
	s3.insert(itc, itc2);

	std::cout << "show content:\n";
	itc = s3.begin();
	for (; itc != s3.end(); itc++)
		std::cout << itc->getStr() << std::endl;
	std::cout << std::endl;
}


/**
 * @brief erase test
*/

void	seteraseTest(void) {

	std::cout << "set<int>\n";
	ft::set<int> s1;

	std::cout << "+ 100\n";
	s1.insert(100);
	std::cout << "+ 200\n";
	s1.insert(200);
	std::cout << "+ 300\n";
	s1.insert(300);
	std::cout << "+ 400\n";
	s1.insert(400);
	setprintSize(s1);

	std::cout << "show content:\n";
	ft::set<int>::iterator it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	std::cout << "erase by val: \'200\'\n";
	s1.erase(200);
	setprintSize(s1);

	std::cout << "show content:\n";
	it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;

	std::cout << "erase by position: \'begin\'\n";
	s1.erase(s1.begin());
	setprintSize(s1);

	std::cout << "show content:\n";
	it = s1.begin();
	for (; it != s1.end(); it++)
		std::cout << *it << std::endl;
	std::cout << std::endl;
	
	std::cout << "erase by range: begin -> end\n";
	s1.erase(s1.begin(), s1.end());
	std::cout << "show content:\n";
	if (s1.empty() == true)
		std::cout << "s1 is empty" << std::endl;
	else {
		it = s1.begin();
		for (; it != s1.end(); it++)
			std::cout << *it << std::endl;
		std::cout << std::endl;
	}
}

/**
 * @brief swap test
*/

void	setswapTest(void) {

	std::cout << "set<int>\n";
	ft::set<int> s1;
	ft::set<int> s2;
	
	std::cout << "s1 + 100\n";
	s1.insert(100);
	std::cout << "s1 + 200\n";
	s1.insert(200);
	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "s2 + 11\n";
	s2.insert(11);
	std::cout << "s2 + 22\n";
	s2.insert(22);
	std::cout << "s2 + 33\n";
	s2.insert(33);
	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s2.begin(); it != s2.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s2);

	std::cout << "swap s1 and s2\n";
	s1.swap(s2);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s2.begin(); it != s2.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s2);
}

/**
 * @brief clear test
*/

void	setclearTest(void) {

	ft::set<int> s1;

	std::cout << "+ 100\n";
	s1.insert(100);
	std::cout << "+ 200\n";
	s1.insert(200);
	std::cout << "+ 300\n";
	s1.insert(300);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "s1 clear:\n";
	s1.clear();
	std::cout << "show content:\n";
	if (s1.empty() == true)
		std::cout << "s1 is empty\n";
	else {
		for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	}
	setprintSize(s1);

	std::cout << "+ 1101\n";
	s1.insert(1101);
	std::cout << "+ 2202\n";
	s1.insert(2202);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);
}

/**
 * @brief keyComp test
*/

void	setkeyCompTest(void) {

	ft::set<int> s1;
	ft::set<int>::key_compare s1Comp = s1.key_comp();

	std::cout << "+ 0 -> 5\n";
	for (int i = 0; i <= 5; i++)
		s1.insert(i);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	int highest = *s1.rbegin();

	std::cout << "show content with comp:\n";
	ft::set<int>::iterator it = s1.begin();
	do {
		std::cout << *it << '\n';
	} while (s1Comp(*(++it), highest));

	std::cout << std::endl;
}

/**
 * @brief valueComp test
*/

void	setvalueCompTest(void) {

	ft::set<int> s1;
	ft::set<int>::key_compare s1Comp = s1.value_comp();

	std::cout << "+ 0 -> 5\n";
	for (int i = 0; i <= 5; i++)
		s1.insert(i);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	int highest = *s1.rbegin();

	std::cout << "show content with comp:\n";
	ft::set<int>::iterator it = s1.begin();
	do {
		std::cout << *it << '\n';
	} while (s1Comp(*(++it), highest));

	std::cout << std::endl;
}

/**
 * @brief find test
*/

void	setfindTest(void) {
	
	ft::set<int> s1;
	ft::set<int>::iterator it;

	std::cout << "+ 10 -> 50\n";
	for (int i = 1; i <= 5; i++)
		s1.insert(i * 10);

	std::cout << "show content:\n";
	for (it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "find \'20\' and erase it\n";
	it = s1.find(20);
	if (it != s1.end())
		s1.erase (it);
	
	std::cout << "show content:\n";
	for (it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "find element and print it:\n";
	std::cout << "find 10 => " << *s1.find(10) << '\n';
	std::cout << "find 30 => " << *s1.find(30) << '\n';
	std::cout << "find 40 => " << *s1.find(40)<< '\n';
	std::cout << "find 50 => " << *s1.find(50)<< '\n';
}

/**
 * @brief count test
*/

void	setcountTest(void) {

	ft::set<int> s1;

	std::cout << "+ 3 6 9 12\n";
	for (int i = 1; i < 5; i++)
		s1.insert(i * 3);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "check element with a loop a -> h:\n";
	for (int i = 0; i <= 12; i++) {
		std::cout << i;
		if (s1.count(i) != 0)
			std::cout << " is an element of s1.\n";
		else 
			std::cout << " is not an element of s1.\n";
	}
}

/**
 * @brief bound test
*/

void	setboundTest(void) {

	ft::set<int> s1;
	ft::set<int>::iterator itlow;
	ft::set<int>::iterator itup;

	std::cout << "+ 10 -> 100\n";
	for (int i = 1; i <= 10; i++)
		s1.insert(i * 10);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "set lower_bound(\'30\') and upper_bound(\'60\')\n";
	itlow = s1.lower_bound (30);
	itup = s1.upper_bound (60);

	std::cout << "erase range of itlow -> itup\n";
	s1.erase(itlow, itup);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);
}

/**
 * @brief equalRange test
*/

void	setequalRangeTest(void) {

	ft::set<int> s1;

	std::cout << "+ 10 -> 100\n";
	for (int i = 1; i <= 10; i++)
		s1.insert(i * 10);

	std::cout << "show content:\n";
	for (ft::set<int>::iterator it = s1.begin(); it != s1.end(); ++it)
		std::cout << *it << '\n';
	setprintSize(s1);

	std::cout << "set equal_range(\'30\')\n";
	ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> ret;
	ret = s1.equal_range(30);

	std::cout << "lower bound points to: ";
	std::cout << *ret.first << '\n';

	std::cout << "upper bound points to: ";
	std::cout << *ret.second << '\n';
}

/**
 * @brief main
 */

void setTest() {

	setconstructTest();
	setiteratorTest();
	setemptyTest();
	setsizeTest();
	setinsertTest();
	seteraseTest();
	setswapTest();
	setclearTest();
	setkeyCompTest();
	setvalueCompTest();
	setfindTest();
	setcountTest();
	setboundTest();
	setequalRangeTest();
}