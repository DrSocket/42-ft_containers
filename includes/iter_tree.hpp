
#ifndef ITER_TREE_HPP
#define ITER_TREE_HPP

#include <iostream>
#include "iter_rbt.hpp"
#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{
	template < class T, class Node >
	class treeIterator : public ft::iterator<bidirectional_iterator_tag, T> {
		public:
		/* member types */

			typedef				T														value_type;
			typedef typename	ft::iterator<bidirectional_iterator_tag, value_type>	iterator;
			typedef typename	iterator::difference_type								difference_type;
			typedef typename	iterator::pointer										pointer;
			typedef typename	iterator::reference										reference;
			typedef typename	iterator::iterator_category								iterator_category;
			typedef Node		node_type;
			typedef Node*		node_pointer;

		private:
			node_pointer _root;
			node_pointer _node;
			node_pointer _null;

		public:
			treeIterator() : _root(nullptr_t), _node(nullptr_t), _null(nullptr_t) {}
			treeIterator(node_pointer root, node_pointer node, node_pointer null) : _root(root), _node(node), _null(null) {}
			treeIterator(treeIterator const & src) : _root(src._root), _node(src._node), _null(src._null) {}
			~treeIterator() {}

			treeIterator & operator= (treeIterator const & rhs) {
				if (this == &rhs) return *this;

				_root = rhs._root;
				_node = rhs._node;
				_null = rhs._null;
				return *this;
			}

			node_pointer getRoot() const { return _root; };
			node_pointer getNode() const { return _node; };
			node_pointer getNull() const { return _null; };

		/* operator */
			reference	operator* () const { return _node->val; }
			pointer		operator->() const { return &(operator*()); }

		/* increment node position*/
			treeIterator &	operator++ () {
				if (_node == max(_root)) {
					_node = _null;
					return *this;
				}
				else if (_node == _null) {
					_node = nullptr_t;
					return *this;
				}
				_node = successor(_node);
				return *this;
			}
			
			treeIterator	operator++ (int) {
				treeIterator tmp(_root, _node, _null);
				operator++();
				return tmp;
			}

			/* decrease node position*/
			treeIterator &	operator-- () {
				if (_node == _null) {
					_node = max(_root);
					return *this;
				}
				_node = predecessor(_node);
				return *this;
			}
			
			treeIterator	operator-- (int) {
				treeIterator tmp(_root, _node, _null);
				operator--();
				return tmp;
			}

			operator treeIterator<const T, Node> () {
				return treeIterator<const T, Node>(_root, _node, _null);
			}

		private:
			node_pointer	min(node_pointer s) {
				while (s->left != _null)
					s = s->left;
				return s;
			}

			node_pointer	max(node_pointer s) {
				while (s->right != _null)
					s = s->right;
				return s;
			}

			node_pointer	successor(node_pointer x) {
				if (x->right != _null)
					return min(x->right);

				node_pointer y = x->parent;
				while (y != _null && x == y->right) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			node_pointer	predecessor(node_pointer s) {
				if (s->left != _null)
					return max(s->left);

				node_pointer	tmp = s->parent;
				while (tmp != _null && s == tmp->left) {
					s = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}
	};

	template < class _T, class _Node >
	bool operator== (const treeIterator<_T, _Node> & lhs, const treeIterator<_T, _Node> & rhs) {
		return lhs.getNode() == rhs.getNode();
	}

	template < class _TL, class _TR, class _Node >
	bool operator== (const treeIterator<_TL, _Node> & lhs, const treeIterator<_TR, _Node> & rhs) {
		return lhs.getNode() == rhs.getNode();
	}

	template < class _T, class _Node >
	bool operator!= (const treeIterator<_T, _Node> & lhs, const treeIterator<_T, _Node> & rhs) {
		return lhs.getNode() != rhs.getNode();
	}

	template < class _TL, class _TR, class _Node >
	bool operator!= (const treeIterator<_TL, _Node> & lhs, const treeIterator<_TR, _Node> & rhs) {
		return lhs.getNode() != rhs.getNode();
	}

}

#endif