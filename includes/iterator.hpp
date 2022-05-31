#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>
#include "utils.hpp"
/**
 * https://en.cppreference.com/w/cpp/header/iterator
 */

namespace ft {
/**
 * https://www.cplusplus.com/reference/iterator/
 */

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/**
 * https://en.cppreference.com/w/cpp/iterator/iterator_traits
 */
	template < class Iterator >
	struct iterator_traits {

		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template < class T >
	struct iterator_traits<T*> {

		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template < class T >
	struct iterator_traits<const T*> {

		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		typename ft::iterator_traits<InputIterator>::difference_type res = 0;
		while (first != last)
		{
			first++;
			res++;
		}
		return (res);
	}

	/**
	 * @class template: iterator
	 * @brief iterator base class.
	 * @param Category: category to which the iterator belongs to. It must be one of the followng iterator tags:
	 * intput_iterator_tag:	input iterator
	 * output_iterator_tag: output iterator
	 * forward_iterator_tag: forward iterator
	 * bidirectional_iterator_tag: bidirectional iterator
	 * random_access_iterator_tage: random-access iterator
	 * @param T: type of elements pointer by the iterator.
	 * @param Distance: type to represent the difference between two iterators.
	 * @param Pointer: type to represent a pointer to an element pointed by the iterator.
	 * @param Reference: type to represent a reference to an element pointed by the iterator.
	 */
	template < class Category,
		class T,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T& >
	struct iterator {

		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

/**
 *	reverse_iterator
 *	https://en.cppreference.com/w/cpp/iterator/reverse_iterator
 */

	template<class Iterator>
	class reverse_iterator {

	public:

		typedef Iterator														iterator_type;
		typedef typename ft::iterator_traits<Iterator>::iterator_category		iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type				value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type			difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer					pointer;
		typedef typename ft::iterator_traits<Iterator>::reference				reference;
		
	private:
		Iterator	_it;

	public:

	/* Contructs reverse iterator that points to no object*/
		reverse_iterator() : _it() {}
	/* Contructs reverse iterator from an original iterator it. `it` is inverted in the constructed object. */
		reverse_iterator (iterator_type it) : _it(it) {}
	/* Constructs a reverse iterator from another reverse iterator. `it` sense of iteration is preserved. */
		template <class Iter>
		reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it.base()) {}

	/* Returns a copy of base iterator which iterates in opposite direction. */
		iterator_type	base () const { return (_it);}

	/* Returns a reference to the element pointed to by iterator. */
		reference		operator*() const { iterator_type tmp = _it; return (*--tmp);}
	/* Returns a pointer to the element pointed to by iterator. */
		pointer			operator->() const { return &(operator*());}

	/* Advances the reverse_iterator by one position. pre-increment: return *this. */
		reverse_iterator&	operator++() { --_it; return (*this);}
	/* Advances the reverse_iterator by one position. post-increment: returns value *this before the call. */
		reverse_iterator	operator++(int) {
			reverse_iterator tmp = (*this);
			++(*this);
			return (tmp);
		}

	/* Decreases the reverse_iterator by one position. pre-decrement: return *this. */
		reverse_iterator&	operator--() { ++_it; return (*this);}
	/* Decreases the reverse_iterator by one position. post-decrement: returns value *this before the call. */
		reverse_iterator	operator--(int) {
			reverse_iterator tmp = (*this);
			--(*this);
			return (tmp);
		}

	/* Returns a reverse_iterator pointing to the element n positions away. */
		reverse_iterator  operator+ (difference_type n) const { return (reverse_iterator(_it - n));}
	/* Advances reverse_iterator by n positions. returns reverse_iterator itself *this. */
		reverse_iterator& operator+=(difference_type n) { _it -= n; return (*this);}

	/* Returns a reverse_iterator pointing to the element n positions before the current possition. */
		reverse_iterator  operator- (difference_type n) const { return (reverse_iterator(_it + n));}
	/* Decreases reverse_iterator by n positions. returns reverse_iterator itself *this. */
		reverse_iterator& operator-=(difference_type n) { _it += n; return (*this);}
	/* Returns a reference to the element n positions away from the element currently pointed by the iterator. */
		reference operator[] (difference_type n) const { return _it[-n - 1]; }

	/* non-member functions */

		friend bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return lhs.base() == rhs.base();
		}

		template < class _IteratorR >
		friend bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
			return lhs.base() == rhs.base();
		}

		friend bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return lhs.base() != rhs.base();
		}

		template < class _IteratorR >
		friend bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
			return lhs.base() != rhs.base();
		}

		friend bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return lhs.base() > rhs.base();
		}

		template < class _IteratorR >
		friend bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
			return lhs.base() > rhs.base();
		}

		friend bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return lhs.base() >= rhs.base();
		}

		template < class _IteratorR >
		friend bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
			return lhs.base() >= rhs.base();
		}

		friend bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return lhs.base() < rhs.base();
		}

		template < class _IteratorR >
		friend bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
			return lhs.base() < rhs.base();
		}

		friend bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
			return lhs.base() <= rhs.base();
		}

		template < class _IteratorR >
		friend bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
			return lhs.base() <= rhs.base();
		}

		friend reverse_iterator<Iterator> operator+ (difference_type n, const reverse_iterator<Iterator>& rev_it) {
			return rev_it + n;
		}

		friend difference_type operator- (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) {
			return rhs.base() - lhs.base();
		}

		template < class _IteratorR >
		friend difference_type operator- (const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<_IteratorR>& rhs) {
			return rhs.base() - lhs.base();
		}
	};
}

#endif