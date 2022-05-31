#include "Test.hpp"

Test & Test::operator=(Test const & rhs) {
	if (this == &rhs) return *this;

	_i = rhs._i;
	_str = rhs._str;
	return *this;
}

int			Test::getI(void) const { return _i; };
std::string	Test::getStr(void) const { return _str; };

bool operator== (Test const & lhs, Test const & rhs) {
	if (lhs.getI() == rhs.getI())
		return true;
	return false;
}

bool operator!= (Test const & lhs, Test const & rhs) {
	if (lhs.getI() != rhs.getI())
		return true;
	return false;
}

bool operator< (Test const & lhs, Test const & rhs) {
	if (lhs.getI() < rhs.getI())
		return true;
	return false;
}

bool operator<= (Test const &lhs, Test const & rhs) {
	if (lhs.getI() <= rhs.getI())
		return true;
	return false;
}

bool operator> (Test const & lhs, Test const & rhs) {
	if (lhs.getI() > rhs.getI())
		return true;
	return false;
}

bool operator>= (Test const &lhs, Test const & rhs) {
	if (lhs.getI() >= rhs.getI())
		return true;
	return false;
}