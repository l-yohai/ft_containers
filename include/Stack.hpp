/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:32:34 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/31 15:32:55 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "List.hpp"

namespace ft
{

template <class T, class Container = List<T> >
class Stack
{
private:
	container_type _ctnr;

private:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;

public:
	explicit stack(const container_type& ctnr = container_type())
	{
		this->_ctnr = ctnr;
	}

	// template <class... Args>
	// void emplace(Args&&... args);

	bool empty() const
	{
		return (this->_ctnr.empty());
	}

	void pop();
	{
		this->_ctnr.pop_back();
	}

	void push(const value_type& val)
	{
		this->_ctnr.push_back();
	}

	size_type size()const
	{
		return (this->_ctnr.size());
	}

	// void swap(stack& x) noexcept(/*see below*/);

	value_type& top()
	{
		return (this->_ctnr.back());
	}

	const value_type& top() const
	{
		return (this->_ctnr.back());
	}

	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}

	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._ctnr != rhs._ctnr);
	}

	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cntr <= rhs._ctnr);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cntr > rhs._ctnr);
	}

	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.cntr >= rhs._ctnr);
	}

	// template <class T, class Container>
	// void swap (stack<T,Container>& x, stack<T,Container>& y) noexcept(noexcept(x.swap(y)))
	// {
	// 	stack<T, Container>& tmp = x;
	// 	x = y;
	// 	y = tmp;
	// }

	// template <class T, class Container, class Alloc>
	// struct uses_allocator<stack<T,Container>,Alloc>
};

}

#endif