#include "Test.hpp"
#include <deque>
#include <list>

template < class T, class Container >
void	stack_printSize(ft::stack<T, Container> stack) {
	std::cout << "size: " << stack.size() << std::endl;
	std::cout << std::endl;
}

/**
 * @brief constructor test
 */

void	stack_constructTest(void) {

	std::cout << "construct empty stk:\n";
	ft::stack<int> stk;
	stack_printSize(stk);

	std::cout << "stack initialized to copy of vector(42, 42):\n";
	ft::vector<int> vec(42, 42);
	ft::stack<int, ft::vector<int> > stk2(vec);
	stack_printSize(stk2);

	std::cout << "stack initialized to copy of deque(42, 42):\n";
	std::deque<int> deq(42, 42);
	ft::stack<int, std::deque<int> > stk3(deq);
	stack_printSize(stk3);

	std::cout << "stack initialized to copy of list(+ 1 2):\n";
	std::list<int> lst;
	lst.push_back(1);
	lst.push_back(2);
	ft::stack<int, std::list<int> > stk4(lst);
	stack_printSize(stk4);
}

/**
 * @brief empty test
 */

void	stack_emptyTest(void) {

	std::cout << "construct empty stk:\n";
	ft::stack<int> stk;
	std::cout << (stk.empty() == true ? "stk is empty" : "stk is not empty") << std::endl;
	stack_printSize(stk);

	std::cout << "stack initialized to copy of vector(42, 42):\n";
	ft::vector<int> vec(42, 42);
	ft::stack<int, ft::vector<int> > stk2(vec);
	std::cout << (stk2.empty() == true ? "stk is empty" : "stk is not empty") << std::endl;
	stack_printSize(stk2);
}

/**
 * @brief size test
 */

void	stack_sizeTest(void) {

	std::cout << "construct empty stk:\n";
	ft::stack<int> stk;
	stack_printSize(stk);

	std::cout << "+ 1\n";
	stk.push(1);
	stack_printSize(stk);

	std::cout << "+ 2\n";
	stk.push(2);
	stack_printSize(stk);
}

/**
 * @brief top test
 */

void	stack_topTest(void) {

	std::cout << "construct empty stk:\n";
	ft::stack<int> stk;
	stack_printSize(stk);

	std::cout << "+ 2 4\n";
	stk.push(2);
	stk.push(4);
	std::cout << "top: " << stk.top() << std::endl;
	stack_printSize(stk);
}

/**
 * @brief push/pop test
 */

void	stack_pbTest(void) {

	std::cout << "construct empty stk:\n";
	ft::stack<int> stk;
	stack_printSize(stk);

	std::cout << "+ 1\n";
	stk.push(1);
	stack_printSize(stk);

	std::cout << "- 1\n";
	stk.pop();
	stack_printSize(stk);

	std::cout << "+ 1\n";
	stk.push(1);
	std::cout << "top: " << stk.top() << std::endl;
	stack_printSize(stk);

	std::cout << "+ 2\n";
	stk.push(2);
	std::cout << "top: " << stk.top() << std::endl;
	stack_printSize(stk);

	std::cout << "+ 3\n";
	stk.push(3);
	std::cout << "top: " << stk.top() << std::endl;
	stack_printSize(stk);

	std::cout << "- 3\n";
	stk.pop();
	std::cout << "top: " << stk.top() << std::endl;
	stack_printSize(stk);

	std::cout << "- 2\n";
	stk.pop();
	std::cout << "top: " << stk.top() << std::endl;
	stack_printSize(stk);

	std::cout << "- 1\n";
	stk.pop();
	stack_printSize(stk);
}

/**
 * @brief main
 */

void stackTest(void) {
	
	stack_constructTest();
	stack_emptyTest();
	stack_sizeTest();
	stack_topTest();
	stack_pbTest();
}