/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:32:52 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/29 16:31:09 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "list.hpp"

namespace ft
{

template <class T, class Container = ft::list<T> >
class queue
{
public:
	typedef T value_type;
	typedef Container container_type;
	typedef size_t size_type;

protected:
	container_type _ctnr;

public:
	explicit queue(const container_type& ctnr = container_type()) : _ctnr(ctnr) {}

	value_type& back()
	{
		return (this->_ctnr.back());
	}

	const value_type& back() const
	{
		return (this->_ctnr.back());
	}

	bool empty() const
	{
		return (this->_ctnr.empty());
	}

	value_type& front()
	{
		return (this->_ctnr.front());
	}

	const value_type& front() const
	{
		return (this->_ctnr.front());
	}

	void pop()
	{
		this->_ctnr.pop_front();
	}

	void push (const value_type& val)
	{
		this->_ctnr.push_back(val);
	}

	size_type size() const
	{
		return (this->_ctnr.size());
	}

	friend bool operator==(const queue& lhs, const queue& rhs)
	{
		return (lhs._ctnr == rhs._ctnr);
	}

	friend bool operator<(const queue& lhs, const queue& rhs)
	{
		return (lhs._ctnr < rhs._ctnr);
	}

};

template <class T, class Container>
bool operator!=(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Container>
bool operator<=(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Container>
bool operator>(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Container>
bool operator>=(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (!(lhs < rhs));
}

}

#endif