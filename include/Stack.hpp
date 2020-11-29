/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:32:34 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/29 20:17:47 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template <class T, class Container = ft::vector<T> >
class stack
{
private:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;

protected:
	container_type _ctnr;

public:
	explicit stack(const container_type& ctnr = container_type())
	{
		this->_ctnr = ctnr;
	}

	bool empty() const
	{
		return (this->_ctnr.empty());
	}

	void pop()
	{
		this->_ctnr.pop_back();
	}

	void push(const value_type& val)
	{
		this->_ctnr.push_back(val);
	}

	size_type size()const
	{
		return (this->_ctnr.size());
	}

	value_type& top()
	{
		return (this->_ctnr.back());
	}

	const value_type& top() const
	{
		return (this->_ctnr.back());
	}

	friend bool operator==(const stack &lhs, const stack &rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}

	friend bool operator<(const stack &lhs, const stack &rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
	}

};

template <class T, class Container>
bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Container>
bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Container>
bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (rhs < lhs);
}

template <class T, class Container>
bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
{
	return (!(lhs < rhs));
}

}

#endif