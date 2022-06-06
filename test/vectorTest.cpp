#include "Test.hpp"
#include <deque>


template < class T >
void	printSize(ft::vector<T> vec) {
	std::cout << "size: " << vec.size() << std::endl;
	std::cout << "maxSize: " << vec.max_size() << std::endl;
	std::cout << "Capacity: " << vec.capacity() << std::endl;
	std::cout << std::endl;
}

/**
 * @brief constructor test
*/

void	constructTest(void) {

	std::cout << "empty test: int:\n";
	ft::vector<int> vecInt;
	printSize(vecInt);

	std::cout << "empty test: Test Class:\n";
	ft::vector<Test> vecTest;
	printSize(vecTest);

	std::cout << "fill test: int:\n";
	ft::vector<int> vecInt2(42);
	printSize(vecInt2);

	std::cout << "range test: int:\n";
	ft::vector<int> vecInt3(vecInt2.begin(), vecInt2.end());
	printSize(vecInt3);

	std::cout << "range test2: Test:\n";
	ft::vector<Test> vecTest2(10);
	ft::vector<Test>::iterator it = vecTest2.begin();
	ft::vector<Test>::iterator ite = vecTest2.end();

	it++;
	ite--;
	ft::vector<Test> vecTest3(it, ite);
	printSize(vecTest3);

	std::cout << "\ncopy test: Test:\n";
	ft::vector<Test> vecTest4(vecTest3);
	printSize(vecTest4);

	std::cout << "\noperator= test: Test:\n";
	vecTest4 = vecTest;
	printSize(vecTest4);
}

/**
 * @brief iterator test
*/

void	iteratorTest(void) {

	ft::vector<int> vecInt;
	vecInt.push_back(1);
	vecInt.push_back(2);
	vecInt.push_back(3);
	vecInt.push_back(4);
	vecInt.push_back(5);

	ft::vector<int>::iterator it = vecInt.begin();
	ft::vector<int>::iterator ite = vecInt.end();
	it++;
	it--;
	it += 1;
	it -= 1;

	it += 1;
	std::cout << "it + 1: " << *it << std::endl;;
	ft::vector<int>::const_iterator cit = it - 1;
	std::cout << "it - 1: " << *cit << std::endl;
	
	it[2] = 10;
	std::cout << "it[2] = 10: " << it[2] << std::endl;

	cit = it;
	if (it == cit)
		std::cout << "if it == cit: " << "Yes" << std::endl;
	else
		std::cout << "if it == cit: " << "No" << std::endl;

	for (; it != ite; it++)
		std::cout << "*it: " << *it << std::endl;
	printSize(vecInt);

	ft::vector<int>::reverse_iterator rit = vecInt.rbegin();
	ft::vector<int>::reverse_iterator rite = vecInt.rend();

	for (; rit != rite; rit++)
		std::cout << "*rit: " << *rit << std::endl;
	printSize(vecInt);
}

/**
 * @brief size/max_size/capacity test
*/

void	sizeTest(void) {
	
	ft::vector<int> vecInt;
	std::cout << "int: ";
	vecInt.push_back(42);
	printSize(vecInt);

	ft::vector<char> vecChar;
	std::cout << "char: ";
	printSize(vecChar);

	ft::vector<long> vecLong;
	std::cout << "long: ";
	vecLong.push_back(42);
	printSize(vecLong);

	ft::vector<long long> vecLongLong;
	std::cout << "longlong: ";
	printSize(vecLongLong);

	ft::vector<Test> vecCuston;
	std::cout << "Test: ";
	printSize(vecCuston);
}

/**
 * @brief resize test
*/

void	resizeTest(void) {

	std::cout << "int: ";
	ft::vector<int> vecInt;
	printSize(vecInt);

	std::cout << "add 1: ";
	vecInt.push_back(1);
	printSize(vecInt);

	std::cout << "resize(42): ";
	vecInt.resize(42);
	printSize(vecInt);

	std::cout << "resize(0): ";
	vecInt.resize(0);
	printSize(vecInt);

	std::cout << "reserve(42): ";
	vecInt.reserve(42);
	printSize(vecInt);

	std::cout << "add 0 -> 42: ";
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	printSize(vecInt);

	std::cout << "reserve(0): ";
	vecInt.reserve(0);
	printSize(vecInt);

	std::cout << "Test: ";
	ft::vector<Test> vecTest;
	printSize(vecTest);

	std::cout << "add 1: ";
	vecTest.push_back(Test(1, "Test"));
	printSize(vecTest);

	std::cout << "resize(42): ";
	vecTest.resize(42);
	printSize(vecTest);

	std::cout << "resize(0): ";
	vecTest.resize(0);
	printSize(vecTest);

	std::cout << "reserve(42): ";
	vecTest.reserve(42);
	printSize(vecTest);

	std::cout << "add 0 -> 42: ";
	for (int i = 0; i <= 42; i++)
		vecTest.push_back(Test(i, "Test"));
	printSize(vecTest);

	std::cout << "reserve(0): ";
	vecTest.reserve(0);
	printSize(vecTest);
}

/**
 * @brief empty test
*/

void	emptyTest(void) {

	std::cout << "int: ";
	ft::vector<int> vecInt;

	std::cout << "init: ";
	std::cout << (vecInt.empty() == true ? "vecInt is empty" : "vecInt is not empty") << std::endl;

	std::cout << "add 1: ";
	vecInt.push_back(1);

	std::cout << (vecInt.empty() == true ? "vecInt is empty\n" : "vecInt is not empty\n") << std::endl;

	std::cout << "Test: ";
	ft::vector<Test> vecTest;

	std::cout << "init: ";
	std::cout << (vecTest.empty() == true ? "vecTest is empty" : "vecTest is not empty") << std::endl;

	std::cout << "add 1: ";
	vecTest.push_back(Test(1, "Test"));

	std::cout << (vecTest.empty() == true ? "vecTest is empty" : "vecTest is not empty") << std::endl;
}

/**
 * @brief element access test
*/

void	elementAccessTest(void) {

	std::cout << "int: assign 0 -> 42";
	ft::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "assign +1 & print with operator[]: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		vecInt[i] += 1;
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	const int i = vecInt[0];
	std::cout << "const int i = vecInt[0]: " << i << std::endl;

	std::cout << "assign +1 & print with at: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		vecInt.at(i) += 1;
		std::cout << vecInt.at(i);
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	const int j = vecInt.at(0);
	std::cout << "const int j = vecInt.at(0): " << j << std::endl;

	std::cout << "first: " <<  *(vecInt.begin()) << " and front: " << vecInt.front() << std::endl;
	std::cout << "last: " <<  *(vecInt.end() - 1) << " and back: " << vecInt.back() << std::endl;

	std::cout << "Test1: + c u s t o m: ";
	ft::vector<Test> vecTest;
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	vecTest.push_back(Test(3, "s"));
	vecTest.push_back(Test(4, "t"));
	vecTest.push_back(Test(5, "o"));
	vecTest.push_back(Test(6, "m"));
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	std::cout << "assign Test -> motsuc with operator[]: ";
	vecTest[0] = (Test(1, "m"));
	vecTest[1] = (Test(2, "o"));
	vecTest[2] = (Test(3, "t"));
	vecTest[3] = (Test(4, "s"));
	vecTest[4] = (Test(5, "u"));
	vecTest[5] = (Test(6, "c"));
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	const Test c(vecTest[0]);
	std::cout << "const Test c(VecTest[0]): " << c.getStr() << std::endl;

	std::cout << "assign motsuc -> Test with at: ";
	vecTest.at(0) = (Test(1, "c"));
	vecTest.at(1) = (Test(2, "u"));
	vecTest.at(2) = (Test(3, "s"));
	vecTest.at(3) = (Test(4, "t"));
	vecTest.at(4) = (Test(5, "o"));
	vecTest.at(5) = (Test(6, "m"));
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	const Test c2(vecTest.at(0));
	std::cout << "const Test c2(vecTest.at(0)): " << c2.getStr() << std::endl;

	std::cout << "first: " <<  (*(vecTest.begin())).getStr() << " and front: " << vecTest.front().getStr() << std::endl;
	std::cout << "last: " <<  (*(vecTest.end() - 1)).getStr() << " and back: " << vecTest.back().getStr() << std::endl;
}

/**
 * @brief assign test
*/

void	assignTest(void) {

	std::cout << "int: \n";
	ft::vector<int> vecInt;

	std::cout << "assigne(42, 1): \n";
	vecInt.assign(42, 1);
	printSize(vecInt);

	std::cout << "Test: \n";
	ft::vector<Test> vecTest;
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	vecTest.push_back(Test(3, "s"));
	vecTest.push_back(Test(4, "t"));
	vecTest.push_back(Test(5, "o"));
	vecTest.push_back(Test(6, "m"));
	
	std::cout << "vecTest: ";
	for (int i = 0; i < vecTest.back().getI(); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	std::cout << "assign(it, ite): \n";
	ft::vector<Test> vecTest2;
	ft::vector<Test>::iterator it = vecTest.begin();
	ft::vector<Test>::iterator ite = vecTest.end();
	vecTest2.assign(it, ite);
	std::cout << "vecTest2: ";
	for (int i = 0; i < vecTest2.back().getI(); i++)
		std::cout << vecTest2[i].getStr();
	std::cout << std::endl;
	printSize(vecTest2);
}

/**
 * @brief push_back/pop_bak test
*/

void	pbTest(void) {

	std::cout << "int: \n";
	ft::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);

	std::cout << "vecInt: (after push_back) + 0 -> 42: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "vecInt: (after pop_back) - 42 -> 0:";
	int size = vecInt.size();
	for (int i = 0; i < size; i++)
		vecInt.pop_back();
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "Test: \n";
	ft::vector<Test> vecTest;
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	vecTest.push_back(Test(3, "s"));
	vecTest.push_back(Test(4, "t"));
	vecTest.push_back(Test(5, "o"));
	vecTest.push_back(Test(6, "m"));

	std::cout << "vecTest: (after push_back) + c u s t o m: ";
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	std::cout << "vecTest: (after pop_back) - m o t s u c:";
	int s = vecTest.size();
	for (int i = 0; i < s; i++)
		vecTest.pop_back();
	std::cout << std::endl;
	printSize(vecTest);
}

/**
 * @brief insert test
*/

void	insertTest(void) {

	std::cout << "Test: \n";
	ft::vector<Test> vecTest;
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	vecTest.push_back(Test(3, "s"));
	vecTest.push_back(Test(5, "o"));
	vecTest.push_back(Test(6, "m"));

	std::cout << "vecTest: + c u s o m: ";
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	std::cout << "insert \'t\' in \'cusom\': single: ";
	ft::vector<Test>::iterator it = vecTest.begin() + 3;
	vecTest.insert(it, Test(4, "t"));
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	std::cout << "int: \n";
	ft::vector<int> vecInt;
	vecInt.push_back(1);
	vecInt.push_back(42);

	std::cout << "VecInt: + 1 42: \n";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "insert 40 * 42 in \'1 42\': fill: ";
	vecInt.insert(vecInt.begin() + 1, 40, 41);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "inset \'1 [41 41 41 ... 41 41 41] 42\' in vecInt2: range:  \n";
	ft::vector<int> vecInt2;
	printSize(vecInt2);

	vecInt2.insert(vecInt2.begin(), vecInt.begin() + 1, vecInt.end() - 1);
	for (int i = 0; i < static_cast<int>(vecInt2.size()); i++) {
		std::cout << vecInt2[i];
		if (i < static_cast<int>(vecInt2.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt2);
}

/**
 * @brief erase test
*/

void	eraseTest(void) {

	std::cout << "int: + 0 -> 42\n";
	ft::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	printSize(vecInt);

	std::cout << "erase 1:\n";
	vecInt.erase(vecInt.begin() + 10);
	printSize(vecInt);

	std::cout << "erase range:\n";
	vecInt.erase(vecInt.begin() + 1, vecInt.end() - 1);
	printSize(vecInt);

	std::cout << "Test: + c u s t o m\n";
	ft::vector<Test> vecTest;
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	vecTest.push_back(Test(3, "s"));
	vecTest.push_back(Test(4, "t"));
	vecTest.push_back(Test(5, "o"));
	vecTest.push_back(Test(6, "m"));
	printSize(vecTest);

	std::cout << "erase 1:\n";
	vecTest.erase(vecTest.begin() + 3);
	printSize(vecTest);

	std::cout << "erase range:\n";
	vecTest.erase(vecTest.begin() + 1, vecTest.end() - 1);
	printSize(vecTest);
}

/**
 * @brief swap test
*/

void	swapTest(void) {

	std::cout << "int1: + 0 -> 42: ";
	ft::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "int2: + 0 -> 12: ";
	ft::vector<int> vecInt2;
	for (int i = 0; i <= 12; i++)
		vecInt2.push_back(i);
	for (int i = 0; i < static_cast<int>(vecInt2.size()); i++) {
		std::cout << vecInt2[i];
		if (i < static_cast<int>(vecInt2.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt2);

	std::cout << "swap int1 <-> int2:\n";
	vecInt.swap(vecInt2);
	std::cout << "int1: ";
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);
	std::cout << "int2: ";
	for (int i = 0; i < static_cast<int>(vecInt2.size()); i++) {
		std::cout << vecInt2[i];
		if (i < static_cast<int>(vecInt2.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt2);

	std::cout << "Test1: + c u s t o m: ";
	ft::vector<Test> vecTest;
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	vecTest.push_back(Test(3, "s"));
	vecTest.push_back(Test(4, "t"));
	vecTest.push_back(Test(5, "o"));
	vecTest.push_back(Test(6, "m"));
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	std::cout << "Test2: + n o t h i n g: ";
	ft::vector<Test> vecTest2;
	vecTest2.push_back(Test(1, "n"));
	vecTest2.push_back(Test(2, "o"));
	vecTest2.push_back(Test(3, "t"));
	vecTest2.push_back(Test(4, "h"));
	vecTest2.push_back(Test(5, "i"));
	vecTest2.push_back(Test(6, "n"));
	vecTest2.push_back(Test(7, "g"));
	for (int i = 0; i < static_cast<int>(vecTest2.size()); i++)
		std::cout << vecTest2[i].getStr();
	std::cout << std::endl;
	printSize(vecTest2);

	std::cout << "swap Test1 <-> Test2:\n";
	vecTest.swap(vecTest2);
	std::cout << "Test1: ";
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);
	std::cout << "Test2: ";
	for (int i = 0; i < static_cast<int>(vecTest2.size()); i++)
		std::cout << vecTest2[i].getStr();
	std::cout << std::endl;
	printSize(vecTest2);
}

/**
 * @brief clear test
*/

void	clearTest(void) {

	std::cout << "int: + 0 -> 42: ";
	ft::vector<int> vecInt;
	for (int i = 0; i <= 42; i++)
		vecInt.push_back(i);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "clear: \n";
	vecInt.clear();
	printSize(vecInt);

	std::cout << "add + 1 2: ";
	vecInt.push_back(1);
	vecInt.push_back(2);
	for (int i = 0; i < static_cast<int>(vecInt.size()); i++) {
		std::cout << vecInt[i];
		if (i < static_cast<int>(vecInt.size()) - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
	printSize(vecInt);

	std::cout << "Test1: + c u s t o m: ";
	ft::vector<Test> vecTest;
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	vecTest.push_back(Test(3, "s"));
	vecTest.push_back(Test(4, "t"));
	vecTest.push_back(Test(5, "o"));
	vecTest.push_back(Test(6, "m"));
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);

	std::cout << "clear: \n";
	vecTest.clear();
	printSize(vecTest);

	std::cout << "add + c u: ";
	vecTest.push_back(Test(1, "c"));
	vecTest.push_back(Test(2, "u"));
	for (int i = 0; i < static_cast<int>(vecTest.size()); i++)
		std::cout << vecTest[i].getStr();
	std::cout << std::endl;
	printSize(vecTest);
}

void vectorTest() {

	constructTest();
	iteratorTest();
	sizeTest();
	resizeTest();
	emptyTest();
	elementAccessTest();
	assignTest();
	pbTest();
	insertTest();
	eraseTest();
	swapTest();
	clearTest();
}