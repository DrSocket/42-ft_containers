#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <cstddef>
#include <exception>
#include "iter_rbt.hpp"
#include "iter_tree.hpp"

namespace ft
{
	template < class Key,
		class T,
		class Compare = std::less<Key>,
		class Alloc = std::allocator< ft::pair<const Key, T> > >
	class map {
		public:
		/* member types */

			typedef				Key													key_type;
			typedef				T													mapped_type;
			typedef				ft::pair<const key_type, mapped_type>				value_type;
			typedef				Compare												key_compare;

			/* returns a comparison object that can be used to compare two elements
			 * finds whether the key of the first one goes before the second. */
			class value_compare : public std::binary_function<value_type, value_type, bool> {
				friend class map;
				protected:
					key_compare comp;
					value_compare(key_compare c) : comp(c) {}

				public:
					typedef bool 		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;

					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

			typedef				Alloc															allocator_type;
			typedef	typename	allocator_type::reference										reference;
			typedef	typename	allocator_type::const_reference									const_reference;
			typedef	typename	allocator_type::pointer											pointer;
			typedef	typename	allocator_type::const_pointer									const_pointer;
			
			/* usually the same as ptrdiff_t */
			typedef	typename	allocator_type::difference_type									difference_type;
			/* usually the same as size_t */
			typedef	typename	allocator_type::size_type										size_type;

			typedef				ft::treeIterator<value_type, ft::RBT_Node<value_type> >			iterator;
			typedef				ft::treeIterator<const value_type, ft::RBT_Node<value_type> >	const_iterator;
			typedef				ft::reverse_iterator<iterator>									reverse_iterator;
			typedef				ft::reverse_iterator<const_iterator>							const_reverse_iterator;

		private:
		/* attributes */
			ft::RBT<value_type, value_compare>	_rbt;
		
		public:
		/* member function: constructor / destructor */

		/* constructs an empty container, with no elements. */
			explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _rbt(value_compare(comp)) { (void)alloc; }
		
			/* constructs a container with as many elements as the range [first, last],
			 * with each element constructed from its corresponding element in that range. */
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _rbt(value_compare(comp)) {
					(void)alloc;
					insert(first, last);
			}

			/* constructs a container with a copy of each of the elements in x. */
			map(const map& x) : _rbt(value_compare(key_compare())) {
				insert(x.begin(), x.end());
			}
			
			/* destroys all container elements,
			 * and deallocates all the storage capacity allocated by the map using its allocator. */
   			~map(void) {
				clear();
				_rbt.destroyNull();
			}

			/* copies all the elements from x into the container, changing its size accordingly. */
			map& operator=(const map& x) {
				if (this == &x) return *this;

				this->~map();
				_rbt = ft::RBT<value_type, value_compare>(value_compare(key_compare()));
				insert(x.begin(), x.end());
				return *this;
			}

		/* member functions: iterators */

			/* returns an iterator referring to the first element in the map container. */
			iterator begin() { return iterator(_rbt.getRoot(), _rbt.min(), _rbt.getNull()); }
			const_iterator begin() const { return const_iterator(_rbt.getRoot(), _rbt.min(), _rbt.getNull()); }
			
			/* returns an iterator referring to the past-the-end element in the map container. */
			iterator end() { return iterator(_rbt.getRoot(), _rbt.getNull(), _rbt.getNull()); }
			const_iterator end() const { return const_iterator(_rbt.getRoot(), _rbt.getNull(), _rbt.getNull()); }

			/* returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning). */
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

			/* returns a reverse iterator pointing to the theoretical element right
			 * before the first element in the map container (which is considered its reverse end). */
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		/* member functions: capacity */
		
			/* returns whether the map container is empty (i.e. whether its size is 0). */
			bool		empty() const { return begin() == end(); }

			/* returns the number of elements in the map container. */
			size_type	size() const { return _rbt.size(); }

			/* returns the maximum number of elements that the map container can hold. */
			size_type	max_size(void) const { return _rbt.max_size(); }

		/* member functions: element access */
			
			/* if k matches the key of an element in the container,
			 * the function returns a reference to its mapped value. */
			mapped_type& operator[](const key_type& k) { return insert(ft::make_pair(k, mapped_type())).first->second; }

		/* member functions: modifiers */
		
			/* extends the container by inserting new elements,
			 * effectively increasing the container size by the number of elements inserted. */
			ft::pair<iterator, bool> insert(const value_type& val) {
				if (_rbt.insert(val) == false)
					return ft::make_pair(find(val.first), false);
				return ft::make_pair(find(val.first), true);
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

			/* removes from the map container either a single element or a range of elements ([first,last)). */
			void  erase(iterator position) {
				erase(position->first);
			}
			
			size_type erase(const key_type& k) {
				if (_rbt.deleteNode(ft::make_pair(k, mapped_type())) == false)
					return 0;
				return 1;
			}

			void  erase(iterator first, iterator last) {
				while (first != last) {
					// refix current ptr
					first = find(first->first);
					erase(first++);
				}
			}
	
			/* exchanges the content of the container by the content of x,
			 * which is another map of the same type. Sizes may differ. */
			void swap (map& x) { _rbt.swap(x._rbt); }

			/* removes all elements from the map container (which are destroyed),
			 * leaving the container with a size of 0. */
			void clear() { _rbt.destroyTree(); }

		/* member functions: observers */

			/* Returns a copy of the comparison object used by the container to compare keys. */
			key_compare	key_comp() const { return key_compare(); }
			
			/* Returns a comparison object that can be used to compare two elements to get whether
			 * the key of the first one goes before the second. */
			value_compare  value_comp() const { return value_compare(key_comp()); }

		/* member functions: operations */
		
			/* searches the container for an element with a key equivalent to k and
			 * returns an iterator to it if found, otherwise it returns an iterator to map::end.*/
			iterator find(const key_type& k) {
				return iterator(_rbt.getRoot(), _rbt.searchTree(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

			const_iterator find(const key_type& k) const {
				return const_iterator(_rbt.getRoot(), _rbt.searchTree(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

			/* searches the container for elements with a key equivalent to k and returns the number of matches. */
			size_type count(const key_type& k) const {
				if (find(k) == end())
					return 0;
				return 1;
			}
			
			/* returns an iterator pointing to the first element in the container
			 * whose key is not considered to go before k (i.e., either it is equivalent or goes after).
			 * the function uses its internal comparison object (key_comp) to determine this,
			 * returning an iterator to the first element for which key_comp(element_key,k) would return false. */
			iterator lower_bound(const key_type& k) {
				return iterator(_rbt.getRoot(), _rbt.lower_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}
			
			const_iterator lower_bound(const key_type& k) const {
				return const_iterator(_rbt.getRoot(), _rbt.lower_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

			/* returns an iterator pointing to the first element in the container
			 * whose key is considered to go after k.
			 * the function uses its internal comparison object (key_comp) to determine this,
			 * returning an iterator to the first element for which key_comp(k,element_key) would return true. */
			iterator upper_bound(const key_type& k) {
				return iterator(_rbt.getRoot(), _rbt.upper_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}
			
			const_iterator upper_bound(const key_type& k) const {
				return const_iterator(_rbt.getRoot(), _rbt.upper_bound(ft::make_pair(k, mapped_type())), _rbt.getNull());
			}

			/* returns the bounds of a range that includes
			 * all the elements in the container which have a key equivalent to k. */
			ft::pair<iterator, iterator> equal_range(const key_type& k) {
				return ft::make_pair<iterator, iterator>(lower_bound(k), upper_bound(k));
			}
			
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
				return ft::make_pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
			}

		/* member functions: allocator */
		
			/* returns a copy of the allocator object associated with the map. */
			allocator_type get_allocator() const { return allocator_type(); }
	};
	
	/* non-member function: map */

		/* performs the appropriate comparison operation between the map containers lhs and rhs.
		 * a != b : !(a == b)
		 * a > b  : b < a
		 * a <= b : !(b < a)
		 * a >= b : !(a < b)
		 */
		template <class Key, class T, class Compare, class Allocator>
		bool operator==(const ft::map<Key, T, Compare, Allocator>& lhs,
				const ft::map<Key, T, Compare, Allocator>& rhs) {
					if (lhs.size() != rhs.size())
						return false;
					return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template <class Key, class T, class Compare, class Allocator>
		bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return !(lhs == rhs); }

		template <class Key, class T, class Compare, class Allocator>
		bool operator< (const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) {
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		template <class Key, class T, class Compare, class Allocator>
		bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return !(rhs < lhs); }

		template <class Key, class T, class Compare, class Allocator>
		bool operator> (const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return rhs < lhs; }

		template <class Key, class T, class Compare, class Allocator>
		bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
				const map<Key, T, Compare, Allocator>& rhs) { return !(lhs < rhs); }

		template <class Key, class T, class Compare, class Allocator>
		void swap(map<Key, T, Compare, Allocator>& x,
			map<Key, T, Compare, Allocator>& y) { x.swap(y); }
}

#endif