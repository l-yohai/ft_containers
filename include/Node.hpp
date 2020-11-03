/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:30:14 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/03 09:27:15 by yohlee           ###   ########.fr       */
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
	Node() : _next(this), _prev(this), _data(0) {}

	Node(const Node& node) : _next(node._next), _prev(node._prev), _data(node._data)
	{
		*this = node;
	}

	Node& operator=(const Node& node)
	{
		this->_next = node._next;
		this->_prev = node._prev;
		this->_data = node._data;
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

	T& getData() { return (this->_data); }
	const T& getData() const { return (this->_data); }

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
class bidirectional_iterator
{
private:
	typedef Node<Iterator>	Node;
	Node*					_node;

public:
	typedef ft::bidirectional_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef ptrdiff_t						difference_type;
	typedef T&								reference;
	typedef T*								pointer;

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

	reference operator*() const
	{
		return (static_cast<Node*>(this->_node)->getData());
	}

	bidirectional_iterator& operator++()
	{
		this->_node = static_cast<Node*>(this->_node->next());
		return (*this);
	}

	bidirectional_iterator operator++(int)
	{
		bidirectional_iterator tmp = *this;
		this->_node = static_cast<Node*>(this->_node->next());
		return (tmp);
	}

	bidirectional_iterator& operator--()
	{
		this->_node = static_cast<Node*>(this->_node->previous());
		return (*this);
	}

	bidirectional_iterator operator--(int)
	{
		bidirectional_iterator tmp = *this;
		this->_node = static_cast<Node*>(this->_node->previous());
		return (tmp);
	}

	pointer operator->() const
	{
		return (&static_cast<Node*>(this->_node)->getData());
	}

	Node* getNode() const
	{
		return (this->_node);
	}
};

template <class T>
bool operator==(const bidirectional_iterator<T>& lhs, const bidirectional_iterator<T>& rhs)
{
	return (lhs._node() == rhs._node());
}

template <class T>
bool operator!=(const bidirectional_iterator<T>& lhs, const bidirectional_iterator<T>& rhs)
{
	return (lhs._node() != rhs._node());
}

}

#endif