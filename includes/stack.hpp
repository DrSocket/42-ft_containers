#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack {

	public:

		typedef Container 							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference const_reference;

	protected:

		container_type c;
	public:

		stack(const container_type& cont = container_type()) : c(cont) {}

		stack(const stack & src) : c(src.c) {}

		stack & operator=(const stack &src)
		{
			if (this == &src)
				return (*this);
			c = src.c;
			return (*this);
		}

		~stack() {}

		bool			empty() const	{ return c.empty(); }
		size_type		size()  const	{ return c.size(); }
		reference		top()			{ return c.back(); }
		const_reference	top() const		{ return c.back(); }

		void push(const value_type& x) { c.push_back(x); }
		void pop() { c.pop_back(); }

		friend bool operator== (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c == rhs.c; }
		friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c != rhs.c; }
		friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c < rhs.c; }
		friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c <= rhs.c; }
		friend bool operator>  (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c > rhs.c; }
		friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs.c >= rhs.c; }
	};
}
#endif