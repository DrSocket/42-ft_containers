#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <limits>
#include "vecIterator.hpp"

/*
 * https://en.cppreference.com/w/cpp/memory/allocator
 */
namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		/* member types */
		typedef 			T										value_type;
		typedef 			Alloc									allocator_type;

		typedef typename	allocator_type::reference				reference;
		typedef typename	allocator_type::const_reference			const_reference;
		typedef typename	allocator_type::pointer					pointer;
		typedef typename	allocator_type::const_pointer			const_pointer;
		typedef typename	allocator_type::difference_type			difference_type;
		typedef typename	allocator_type::size_type				size_type;

		typedef typename	ft::vecIterator<value_type> 			iterator;
		typedef typename	ft::vecIterator<const value_type>		const_iterator;

		typedef typename	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef typename	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private:
		/* attributes */
		allocator_type	_alloc;
		pointer			_begin;
		pointer			_end;
		pointer			_capacity;

	public:
	/* member function: constructor / destructor */
		vector(const allocator_type & alloc = allocator_type()) :
			_alloc(alloc),
			_begin(nullptr_t),
			_end(nullptr_t),
			_capacity(nullptr_t) {}

		vector(size_type n,
			const value_type & val = value_type(),
			const allocator_type & alloc = allocator_type()) :
			_alloc(alloc),
			_begin(nullptr_t),
			_end(nullptr_t),
			_capacity(nullptr_t) {
				try {
					_begin = _alloc.allocate(n);
				}
				catch (std::length_error &e) {
					throw std::length_error("vector");
				}

				_end = _begin;
				_capacity = _begin + n;

				while (n--)
					_alloc.construct(_end++, val);
		}

	/* 
	 * Construct container with as many elements as the range [first, last].
	 * Each element is constructed from its corresponding element in that range, in the same order.
	 */
		template < class InputIterator >
		vector(InputIterator first, InputIterator last,
			const allocator_type & alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr_t) :
			_alloc(alloc) {
			size_type n = static_cast<size_type>(ft::distance(first, last));

			_begin = _alloc.allocate(n);
			_end = _begin;
			_capacity = _begin + n;

			while (n--)
				_alloc.construct(_end++, *first++);
		}

	/* Constructs a container with a copy of each of the elements in x, in the same order. */
		vector(const vector & x) {
			size_type n = x.size();

			this->_begin = this->_alloc.allocate(n);
			this->_end = this->_begin;
			this->_capacity = this->_end + n;
			
			pointer tmp = x._begin;
			while (n--)
				this->_alloc.construct(this->_end++, *tmp++);
		}
		
	/* Destroys all container elements & deallocates storage capacity. */
		~vector(void) {
			clear();
			_alloc.deallocate(_begin, this->capacity());
		}

	/* Copies all the elements from x into the container. */
		vector &	operator= (vector const & x) {
			if (this == &x)
				return (*this);
			clear();

			size_type n = x.size();
			if (n > this->capacity())
				reserve(n);
			pointer tmp = x._begin;
			while (n--)
				this->_alloc.construct(this->_end++, *tmp++);
			return (*this);
		}

	/* get */
		allocator_type get_allocator() const { return _alloc; }

	/* iterators */
		iterator				begin(void)			{ return iterator(_begin); }
		const_iterator			begin(void) const	{ return const_iterator(_begin); }
		iterator				end(void)			{ return iterator(_end); }
		const_iterator			end(void) const		{ return const_iterator(_end); }
		reverse_iterator		rbegin(void)		{ return reverse_iterator(end()); }
		const_reverse_iterator	rbegin(void) const	{ return const_reverse_iterator(end()); }
		reverse_iterator		rend(void)			{ return reverse_iterator(begin()); }
		const_reverse_iterator	rend(void) const	{ return const_reverse_iterator(begin()); }

	/* Capacity functions */

	/* Returns the number of elements in the vector. */
		size_type	size(void) const { return _end - _begin; }
	/* Returns the size of the storage space currently allocated for the vector, expressed in terms of elements. */
		size_type	capacity(void) const { return _capacity - _begin; }
	/* Return whether the vector is empty. */
		bool		empty(void) const { return size() == 0; }

	/* Return the maximum number of elements that the vector can hold. */
		size_type	max_size(void) const {
		#if defined(__APPLE__) && defined(__MACH__)
			size_type ret1 = allocator_type().max_size();
			size_type ret2 = std::numeric_limits<difference_type>::max();
			return ((ret1 < ret2) ? ret1 : ret2);
		#else
			return (allocator_type().max_size());
		#endif
		}

	/* Requests that the vector capacity be at least enough to contain n elements. */
		void		reserve(size_type n) {
			if (n > max_size())
				throw std::length_error("vector");

			if (capacity() < n) {
				pointer oldStart = _begin;
				pointer oldEnd = _end;
				size_type oldN = size();
				size_type oldCap = capacity();
				try {
					_begin = _alloc.allocate(n);
				}
				catch (std::length_error &e) {
					throw std::length_error("vector");
				}
				_end = _begin;
				_capacity = _begin + n;
				while (oldStart != oldEnd)
					_alloc.construct(_end++, *oldStart++);
				_alloc.deallocate(oldStart - oldN, oldCap);
			}
		}

	/* Resizes the container so that it contains n elements
	 * val: the value to initialize the new elements with
	 */
		void		resize(size_type n, value_type val = value_type()) {
			if (n > max_size())
				throw std::length_error("vector");

			size_type oldN = size();
			size_type oldCap = capacity();

			if (n < oldN) {
				while (n < size())
					_alloc.destroy(--_end);
			}
			else if (n <= oldCap)
				;
			else {
				if (n <= oldCap * 2)
					this->reserve(oldCap * 2);
				else
					this->reserve(n);
			}
			for (; oldN < n; oldN++)
				_alloc.construct(_end++, val);
		}

	/* Element Access */

	/* Returns a reference to the element at position n in the vector container. */
		reference			operator[](size_type n) { return (_begin[n]); }
		const_reference		operator[](size_type n) const { return (_begin[n]); }

	/* Returns a reference to the first element in the vector. */
		reference			front(void) { return *_begin; }
		const_reference		front(void) const { return *_begin; }

	/* Returns a reference to the last element in the vector. */
		reference			back(void) { return *(_end - 1); }
		const_reference		back(void) const { return *(_end - 1); }

	/* Returns a refenrece to the element at position n in the vector. */
		reference			at(size_type n) {
			if (n >= size())
				throw std::out_of_range("vector");
			return (_begin[n]);
		}
		const_reference		at(size_type n) const {
			if (n >= size())
				throw std::out_of_range("vector");
			return (_begin[n]);
		}

	/* member functions: modifiers */
		
	/* Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly. */
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr_t) {
			clear();

			size_type n = static_cast<size_type>(ft::distance(first, last));
			reserve(n);

			for (; first != last; first++) {
				_alloc.construct(_end++, *first);
			}
		}

		void assign(size_type n, const value_type & val) {
			clear();
			reserve(n);
			
			while (n--) {
				_alloc.construct(_end++, val);
			}
		}

	/* Add a new element at the end of the vector, after its current last element. */
		void push_back(const value_type & val) {
			if (_end == _capacity)
				reserve(size() > 0 ? size() * 2 : 1);
			_alloc.construct(_end, val);
			++_end;
		}

	/* Removes the last element in the vector, effectively reducing the container size by one. */
		void pop_back(void) {
			_alloc.destroy(_end - 1);
			--_end;
		}

	/* Removes all elements from the vector, leaving the container with a size of 0. */
		void	clear(void) {
			size_type len = size();

			for (size_type i = 0; i < len; i++)
				_alloc.destroy(--_end);
		}

	/* Extends the vector by inserting new elements before the element at the specified position.
	 * Increases the container size by n
	 */
		iterator insert(iterator position, const value_type & val) {
			insert(position, 1, val);
			return iterator(position);
		}

		void insert(iterator position, size_type n, const value_type & val)  {
			size_type pos = ft::distance(begin(), position);

			resize(size() + n);
			position = begin() + pos;
			
			size_type toMoveRight = ft::distance(position, end() - n);
			pointer oldEnd = _end - n - 1;
			for (size_type i = 0; i < toMoveRight; i++) {
				*(_end - i - 1) = *oldEnd--;
			}
			for (size_type i = 0; i < n; i++) {
				*(position + i) = val;
			}
		}

		template < class InputIterator >
		void insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = nullptr_t) {
			size_type pos = ft::distance(begin(), position);
			size_type n = ft::distance(first, last);

			resize(size() + n);
			position = begin() + pos;
			
			size_type toMoveRight = ft::distance(position, end() - n);
			pointer oldEnd = _end - n - 1;
			for (size_type i = 0; i < toMoveRight; i++) {
				*(_end - i - 1) = *oldEnd--;
			}
			for (size_type i = 0; i < n && first != last; i++, first++) {
				*(position + i) = *first;
			}
		}

	/* Removes from the vector either a single element or a range of elements. */
		iterator erase(iterator position) {
			iterator pos = position;
			size_type toDestroyPos = ft::distance(begin(), position);

			_alloc.destroy(_begin + toDestroyPos);

			for (; pos + 1 != end(); ++pos)
				*pos = *(pos + 1);
			--_end;
			return iterator(position);
		}

		iterator erase(iterator first, iterator last) {
			for (; first != last; --last)
				erase(first);
			return iterator(first);
		}

	/* Exchanges the content of the container by the content of x. */
		void swap(vector & x) {
			pointer beginTmp = _begin;
			pointer endTmp = _end;
			pointer capacityTmp = _capacity;
			allocator_type allocTmp = _alloc;

			_begin = x._begin;
			_end = x._end;
			_capacity = x._capacity;
			_alloc = x._alloc;

			x._begin = beginTmp;
			x._end = endTmp;
			x._capacity = capacityTmp;
			x._alloc = allocTmp;
		}

	};

	template < class T, class Alloc >
	bool operator== (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template < class T, class Alloc >
	bool operator!= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
		return !(lhs == rhs);
	}

	/** @brief lexicographically compares the values in the vector */
	template < class T, class Alloc> 
	bool operator< (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	/** @brief lexicographically compares the values in the vector */
	template < class T, class Alloc >
	bool operator<= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
		return !(rhs < lhs);
	}

	/** @brief lexicographically compares the values in the vector */
	template < class T, class Alloc >
	bool operator> (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
		return rhs < lhs;
	}

	/** @brief lexicographically compares the values in the vector */
	template < class T, class Alloc >
	bool operator>= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
		return !(lhs < rhs);
	}

	template < class T, class Alloc >
	void swap (vector<T, Alloc> & x, vector<T, Alloc> & y) {
		x.swap(y);
	}
}

#endif