/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:30:14 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/01 15:04:04 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include "Iterator.hpp"

namespace ft
{

template <typename T>
class Node
{
private:
	Node*	_next;
	Node*	_prev;
	T		_data;

public:
	Node() : _next(this), _prev(this), _data(nullptr) {}
	// {
	// 	this->_next = this;
	// 	this->_prev = this;
	// }

	Node(const Node& node) : _next(node._next), _prev(node._prev)
	{
		*this = node;
	}

	Node& operator=(const Node& node)
	{
		this->_next = node._next;
		this->_prev = node._prev;
		return (*this);
	}

	Node*& next()
	{
		return (this->_next);
	}

	Node* next() const
	{
		return (this->_next);
	}

	Node*& previous()
	{
		return (this->_prev);
	}

	Node* previous() const
	{
		return (this->_prev);
	}

	void connect(Node* to)
	{
		this->next() = to;
		this->previous() = to->previous();

		to->previous()->next() = this;
		to->previous() = this;
	}

	Node* disconnect()
	{
		Node* const node = next();
		
		this->previous()->next() = node;
		node->previous() = this->previous();
		return (this);
	}

};

// template<>
void swap(Node& x, Node& y)
{
	if (x.next() != &x)
	{
		if (y.next() != &y)
		{
			ft::swap(x.next(), y.next());
			ft::swap(x.previous(), y.previous());
			x.next()->previous() = x.previous()->next() = &x;
			y.next()->previous() = y.previous()->next() = &y;
		}
		else
		{
			y.next() = x.next();
			y.previous() = x.previous();
			y.next()->previous() = y.previous()->next() = &y;
			x.next() = x.previous() = &x;
		}
	}
	else if (y.next() != &y)
	{
		x.next() = y.next();
		x.previous() = y.previous();
		x.next()->previous() = x.previous()->next() = &x;
		y.next() = y.previous() = &y;
	}
}

template <class Iterator>
class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Iterator>
{
private:
	typedef Node<Iterator>	Node;
	Node*					_node;

public:
	typedef Iterator											iterator_type;
	typedef ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef ft::iterator_traits<Iterator>::value_type			value_type;
	typedef ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef ft::iterator_traits<Iterator>::reference			reference;
	typedef ft::iterator_traits<Iterator>::pointer				pointer;

public:
	bidirectional_iterator() : _node() {}
	explicit bidirectional_iterator(Node* node) : _node(node) {}

	bidirectional_iterator(const bidirectional_iterator<Iterator>& node) : _node(node._node)
	{
		*this = node;
	}

	bidirectional_iterator& operator=(const bidirectional_iterator<Iterator>& node)
	{
		if (*this != node)
			this->_node = node._node;
		return (*this);
	}

	~bidirectional_iterator() {}

	iterator_type base() const
	{
		return (this->_it);
	}

	reference operator*() const
	{
		iterator_type it = this->_it;
		return (*(--it));
	}

	bidirectional_iterator operator+(difference_type n) const
	{
		return (this->_it + n);
	}

	bidirectional_iterator& operator++()
	{
		++(this->_it);
		return (*this);
	}

	bidirectional_iterator operator++(int)
	{
		bidirectional_iterator tmp = *this;
		++(*this);
		return (tmp);
	}

	bidirectional_iterator& operator+=(difference_type n)
	{
		bidirectional_iterator<iterator_type> it(*this);
		it += n;
		return (*this);
	}

	bidirectional_iterator operator-(difference_type n) const
	{
		return (this->_it - n);
	}

	bidirectional_iterator& operator--()
	{
		--(this->_it);
		return (*this);
	}

	bidirectional_iterator operator--(int)
	{
		bidirectional_iterator tmp = *this;
		--(this->_it);
		return (tmp);
	}

	bidirectional_iterator& operator-=(difference_type n)
	{
		this->_it -= n;
		return (*this);
	}

	pointer operator->() const
	{
		return (this->_it);
	}

	reference operator[](difference_type n) const
	{
		return (*(this->_it + n));
	}
};

template <class Iterator>
bool operator==(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!=(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator<=(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
bool operator>(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator>=(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
typename bidirectional_iterator<Iterator>::difference_type operator-(const bidirectional_iterator<Iterator>& lhs, const bidirectional_iterator<Iterator>& rhs)
{
	return (lhs.base() + rhs.base());
}

template <class Iterator>
bidirectional_iterator<Iterator> operator+(typename bidirectional_iterator<Iterator>::difference_type n, const bidirectional_iterator<Iterator>& rev_it)
{
	return (bidirectional_iterator<Iterator> (rev_it.base() - n));
}

}

#endif