#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cstddef>
#include <memory>
#include <map>
#include "utils_map.hpp"

namespace ft {

	/* Enable type if condition is met. `Cond` is a bool const and `T` a type. */
	template <bool Cond, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type;};

	/* Provides compile-time constants. */
	template< class T, T v >
	struct integral_constant {
		typedef T 							value_type;
		typedef integral_constant<T, v> 	type;
		static const value_type value = 	v;

		operator value_type() const
		{
			return (value);
		}
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type;

	/* Identifies if T is an integral type. */
	template<class Obj> struct is_integral						:	ft::false_type{};
	template<> 			struct is_integral<int>					:	ft::true_type {};
	template<> 			struct is_integral<bool>				:	ft::true_type {};
	template<> 			struct is_integral<char>				:	ft::true_type {};
	template<> 			struct is_integral<long>				:	ft::true_type {};
	template<> 			struct is_integral<short>				:	ft::true_type {};
	template<> 			struct is_integral<wchar_t> 			:	ft::true_type {};
	template<> 			struct is_integral<char16_t> 			:	ft::true_type {};
	template<> 			struct is_integral<char32_t> 			:	ft::true_type {};
	template<> 			struct is_integral<long long>			:	ft::true_type {};
	template<> 			struct is_integral<signed char>			:	ft::true_type {};
	template<> 			struct is_integral<unsigned int>		:	ft::true_type {};
	template<> 			struct is_integral<unsigned long>		:	ft::true_type {};
	template<> 			struct is_integral<unsigned char>		:	ft::true_type {};
	template<> 			struct is_integral<unsigned short>		:	ft::true_type {};
	template<> 			struct is_integral<unsigned long long>	:	ft::true_type {};

	template < class InputIterator1, class InputIterator2 >
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (*first1 != *first2) {
				return false;
			}
		}
		return true;
	}

	template < class InputIt1, class InputIt2 >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1); ++first1, (void) ++first2 ) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return ((first2 != last2));
	}

	struct  nullptr_s {
		void *_ptr;

		struct __nat { int __for_bool_; };

		nullptr_s() : _ptr(0) {}
		nullptr_s(int __nat::*) : _ptr(0) {}

		operator int __nat::*() const { return 0; }

		template <class _T>
		operator _T* () const {return 0;}

		template <class _T, class _U>
		operator _T _U::* () const {return 0;}

		friend bool operator==(nullptr_s, nullptr_s) { return true; }
		friend bool operator!=(nullptr_s, nullptr_s) { return false; }
	};

	#define nullptr_t nullptr_s(0)
}

#endif