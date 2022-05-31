#ifndef UTILS_MAP_HPP
#define UTILS_MAP_HPP

#include <iostream>
#include <cstddef>
#include <memory>
#include <functional>
#include <map>

namespace ft {

/* Pair class couples together a pair of values, which may be of different types (T1 and T2). */
	template < class T1, class T2 >
	struct pair {
		typedef T1	first_type;
		typedef T2	second_type;
	
		first_type	first;
		second_type second;
		pair(void) :
			first(),
			second() {}
		
		/* The object is iniialized with the contents of the pr pair object.
		 * the corresponding member of pr is passed to the constructor of each of its members. */
		template< class U, class V >
		pair(const pair<U, V> & pr) :
			first(pr.first),
			second(pr.second) {}
		
		/* member first is constructed with a and member second with b. */
		pair(const first_type & a, const second_type & b) :
			first(a),
			second(b) {}

		pair& operator= (const pair & pr) {
			if (this == &pr) return *this;

			first = pr.first;
			second = pr.second;
			return *this;
		}
	};
	
	/* non-member functions pair */
	/* performs the appropriate comparison operation between pair objects lhs and rhs.*/
	template < class T1, class T2 >
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template < class T1, class T2 >
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	template < class T1, class T2 >
	bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template < class T1, class T2 >
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(rhs < lhs);
	}

	template < class T1, class T2 >
	bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return rhs < lhs;
	}

	template < class T1, class T2 >
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}

/* constricts a pair object with its first element set to x and its second element set to y. */
	template < class T1, class T2 >
	pair<T1, T2> make_pair (T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}
}

#endif