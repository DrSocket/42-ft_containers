#ifndef VECITERATOR_HPP
#define VECITERATOR_HPP

#include "iterator.hpp"
#include "utils.hpp"

namespace ft {

	template < class T >
	class vecIterator : public ft::iterator<random_access_iterator_tag, T> {
	public:

		typedef typename ft::iterator<random_access_iterator_tag, T>::value_type			value_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type		difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, T>::pointer				pointer;
		typedef typename ft::iterator<random_access_iterator_tag, T>::reference				reference;
		typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category		iterator_category;
	private:
		pointer		_ptr;

	public:

		vecIterator(void) : _ptr(nullptr_t) {}
		vecIterator(pointer val) : _ptr(val) {}
		vecIterator(vecIterator const & src) : _ptr(src._ptr) {}
		~vecIterator(void) {}

		vecIterator & operator= (vecIterator const & rhs) {
			if (this == &rhs) return *this;

			this->_ptr = rhs._ptr;
			return *this;
		}

		pointer base(void) const { return _ptr; }

		/* cast vecIterator<T> to vecIterator<const T> */
		operator vecIterator<const T> (void) {
			return vecIterator<const T>(_ptr);
		}

		/* add value */
		vecIterator	operator+ (difference_type const &n) const {
			return (_ptr + n);
		}

		/* increment value position */
		vecIterator &	operator++ (void) {
			++_ptr;
			return (*this);
		}
		
		vecIterator	operator++ (int) {
			vecIterator tmp(*this);
			++_ptr;
			return (tmp);
		}

		/* advance value by n */
		vecIterator &	operator+= (difference_type const &n) {
			_ptr += n;
			return (*this);
		}

		/* subtract value */
		vecIterator	operator- (difference_type const &n) const {
			return (_ptr - n);
		}

		/* decrease value position*/
		vecIterator &	operator-- (void) {
			--_ptr;
			return (*this);
		}
		
		vecIterator	operator-- (int) {
			vecIterator tmp(*this);
			--_ptr;
			return (tmp);
		}

		/* retrocede value */
		vecIterator &	operator-= (difference_type const &n) {
			_ptr -= n;
			return (*this);
		}

		/* derefence value ( return &(operator*()); ) */
		pointer	operator-> (void) const { return (_ptr); }
		/* reference */
		reference	operator* (void) const { return (*_ptr); }
		// /* dereference value offset by n */
		reference	operator[] (difference_type const n) const { return (_ptr[n]); }

		/* non-member functions */
		friend bool operator== (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
			return lhs.base() == rhs.base();
		}

		/* no const -> const case */
		template < class _TR >
		friend bool operator== (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
			return lhs.base() == rhs.base();
		}

		friend bool operator!= (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
			return lhs.base() != rhs.base();
		}

		/* no const -> const case */
		template < class _TR >
		friend bool operator!= (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
			return lhs.base() != rhs.base();
		}

		friend bool operator<  (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
			return lhs.base() < rhs.base();
		}

		/* no const -> const case */
		template < class _TR >
		friend bool operator<  (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
			return lhs.base() < rhs.base();
		}

		friend bool operator<= (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
			return lhs.base() <= rhs.base();
		}

		/* no const -> const case */
		template < class _TR >
		friend bool operator<= (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
			return lhs.base() <= rhs.base();
		}

		friend bool operator>  (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
			return lhs.base() > rhs.base();
		}

		/* no const -> const case */
		template < class _TR >
		friend bool operator>  (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
			return lhs.base() > rhs.base();
		}

		friend bool operator>= (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
			return lhs.base() >= rhs.base();
		}

		/* no const -> const case */
		template < class _TR >
		friend bool operator>= (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
			return lhs.base() >= rhs.base();
		}

		friend vecIterator<T> operator+ (difference_type n, const vecIterator<T> & it) {
			return it + n;
		}

		friend difference_type operator- (const vecIterator<T> lhs, const vecIterator<T> rhs) {
			return lhs.base() - rhs.base();
		}

		/* no const -> const case */
		template < class _TR >
		friend difference_type operator- (const vecIterator<T> lhs, const vecIterator<_TR> rhs) {
			return lhs.base() - rhs.base();
		}
	};
}

#endif