#ifndef SET_HPP
# define SET_HPP

#include <memory>
#include <cstddef>
#include <exception>
#include "iter_tree.hpp"

namespace ft {

/* sets are containers that store unique elements following a specific order. */
	template < class T,
		class Compare = std::less<T>,
		class Alloc = std::allocator<T> >
	class set {
		public:
		/* member types */

			typedef				T													key_type;
			typedef				T													value_type;
			typedef				Compare												key_compare;
			typedef				Compare												value_compare;

			typedef				Alloc															allocator_type;
			typedef	typename	allocator_type::reference										reference;
			typedef	typename	allocator_type::const_reference									const_reference;
			typedef	typename	allocator_type::pointer											pointer;
			typedef	typename	allocator_type::const_pointer									const_pointer;
			
			/** @note usually the same as ptrdiff_t */
			typedef	typename	allocator_type::difference_type									difference_type;
			/** @note usually the same as size_t */
			typedef	typename	allocator_type::size_type										size_type;

			typedef				ft::treeIterator<const value_type, ft::RBT_Node<value_type> >	iterator;
			typedef				ft::treeIterator<const value_type, ft::RBT_Node<value_type> >	const_iterator;
			typedef				ft::reverse_iterator<iterator>									reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		private:
		/* attributes */
			ft::RBT<value_type, value_compare>	_RBT;

		public:
		/* member functions: constructor / destructor / operator= */

			/* constructs an empty container, with no elements. */
			explicit set(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _RBT(comp) { (void)alloc; }
		
			/* constructs a container with as many elements as the range [first, last],
			 * with each element constructed from its corresponding element in that range. */
			template <class InputIterator>
			set(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _RBT(comp) {
					(void)alloc;
					insert(first, last);
			}

			/* constructs a container with a copy of each of the elements in x. */
			set(const set& x) : _RBT(value_compare()) {
				insert(x.begin(), x.end());
			}
			
			/* destroys the container object. */
   			~set(void) {
				clear();
				_RBT.destroyNull();
			}

			/* @note copies all the elements from x into the container, changing its size accordingly. */
			set& operator=(const set& x) {
				if (this == &x) return *this;

				this->~set();
				_RBT = ft::RBT<value_type, value_compare>(value_compare());
				insert(x.begin(), x.end());
				return *this;
			}

		/* returns an iterator referring to the first element in the set container. */
			iterator begin() { return iterator(_RBT.getRoot(), _RBT.min(), _RBT.getNull()); }
			const_iterator begin() const { return const_iterator(_RBT.getRoot(), _RBT.min(), _RBT.getNull()); }
			
			/* returns an iterator referring to the past-the-end element in the set container. */
			iterator end() { return iterator(_RBT.getRoot(), _RBT.getNull(), _RBT.getNull()); }
			const_iterator end() const { return const_iterator(_RBT.getRoot(), _RBT.getNull(), _RBT.getNull()); }

			/* returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning). */
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

			/* returns a reverse iterator pointing to the theoretical element right
			 * before the first element in the set container (which is considered its reverse end). */
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* member functions: capacity */
		
			/* returns whether the set container is empty (i.e. whether its size is 0). */
			bool		empty() const { return begin() == end(); }

			/* returns the number of elements in the set container. */
			size_type	size() const { return _RBT.size(); }

			/* returns the maximum number of elements that the set container can hold. */
			size_type	max_size(void) const { return _RBT.max_size(); }

		/* member functions: modifiers */
		
			/* extends the container by inserting new elements,
			 * effectively increasing the container size by the number of elements inserted. */
			ft::pair<iterator, bool> insert(const value_type& val) {
				if (_RBT.insert(val) == false)
					return ft::make_pair(find(val), false);
				return ft::make_pair(find(val), true);
			}

			iterator insert(iterator position, const value_type& val) {
				(void)position;
				return insert(val).first;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				for (; first != last; first++)
					insert(*first);
			}

			/* removes from the set container either a single element or a range of elements ([first,last)). */
			void  erase(iterator position) {
				erase(*position);
			}
			
			size_type erase(const value_type& val) {
				if (_RBT.deleteNode(val) == false)
					return 0;
				return 1;
			}

			void  erase(iterator first, iterator last) {
				while (first != last) {
					// refix current ptr
					first = find(*first);
					erase(first++);
				}
			}
	
			/* exchanges the content of the container by the content of x,
			 * which is another set of the same type. Sizes may differ. */
			void swap (set& x) { _RBT.swap(x._RBT); }

			/* removes all elements from the set container (which are destroyed),
			 * leaving the container with a size of 0. */
			void clear() { _RBT.destroyTree(); }

		/* member functions: observers */

			/* returns a copy of the comparison object used by the container. */
			key_compare	key_comp() const { return key_compare(); }
			
			/* Returns a copy of the comparison object used by the container. */
			value_compare  value_comp() const { return value_compare(); }

		/* member functions: operations */
		
			/* searches the container for an element equivalent to val and
			 * returns an iterator to it if found, otherwise it returns an iterator to set::end. */
			iterator find(const value_type& val) {
				return iterator(_RBT.getRoot(), _RBT.searchTree(val), _RBT.getNull());
			}

			const_iterator find(const value_type& val) const {
				return const_iterator(_RBT.getRoot(), _RBT.searchTree(val), _RBT.getNull());
			}

			/* searches the container for elements equivalent to val and returns the number of matches. */
			size_type count(const value_type& val) const {
				if (find(val) == end())
					return 0;
				return 1;
			}
			
			/* Returns an iterator pointing to the first element in the container
			 * which is not considered to go before val (i.e., either it is equivalent or goes after).
			 * The function uses its internal comparison object (key_comp) to determine this,
			 * returning an iterator to the first element for which key_comp(element,val) would return false. */
			iterator lower_bound(const value_type& val) {
				return iterator(_RBT.getRoot(), _RBT.lower_bound(val), _RBT.getNull());
			}
			
			const_iterator lower_bound(const value_type& val) const {
				return const_iterator(_RBT.getRoot(), _RBT.lower_bound(val), _RBT.getNull());
			}

			/* returns an iterator pointing to the first element in the container which is considered to go after val.
			 * the function uses its internal comparison object (key_comp) to determine this,
			 * returning an iterator to the first element for which key_comp(val,element) would return true. */
			iterator upper_bound(const value_type& val) {
				return iterator(_RBT.getRoot(), _RBT.upper_bound(val), _RBT.getNull());
			}
			
			const_iterator upper_bound(const value_type& val) const {
				return const_iterator(_RBT.getRoot(), _RBT.upper_bound(val), _RBT.getNull());
			}

			/* returns the bounds of a range that includes all the elements in the container that are equivalent to val. */
			ft::pair<iterator, iterator> equal_range(const value_type& val) {
				return ft::make_pair<iterator, iterator>(lower_bound(val), upper_bound(val));
			}
			
			ft::pair<const_iterator, const_iterator> equal_range(const value_type& val) const {
				return ft::make_pair<const_iterator, const_iterator>(lower_bound(val), upper_bound(val));
			}

		/* member functions: allocator */
		
			/**
			 * @brief get allocator
			 * @note returns a copy of the allocator object associated with the set.
			 * 
			 * @return the allocator.
			 */
			allocator_type get_allocator() const { return allocator_type(); }
	};
	
	/* non-member function: set */

		/* performs the appropriate comparison operation between the set containers lhs and rhs.
		 * a != b : !(a == b)
		 * a > b  : b < a
		 * a <= b : !(b < a)
		 * a >= b : !(a < b) */
		template <class T, class Compare, class Allocator>
		bool operator==(const ft::set<T, Compare, Allocator>& lhs,
				const ft::set<T, Compare, Allocator>& rhs) {
					if (lhs.size() != rhs.size())
						return false;
					return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <class T, class Compare, class Allocator>
		bool operator!=(const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return !(lhs == rhs); }

		template <class T, class Compare, class Allocator>
		bool operator< (const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) {
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class T, class Compare, class Allocator>
		bool operator<=(const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return !(rhs < lhs); }

		template <class T, class Compare, class Allocator>
		bool operator> (const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return rhs < lhs; }

		template <class T, class Compare, class Allocator>
		bool operator>=(const set<T, Compare, Allocator>& lhs,
				const set<T, Compare, Allocator>& rhs) { return !(lhs < rhs); }

		template <class T, class Compare, class Allocator>
		void swap(set<T, Compare, Allocator>& x,
			set<T, Compare, Allocator>& y) { x.swap(y); }

}

#endif
