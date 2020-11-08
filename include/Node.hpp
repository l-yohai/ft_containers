/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:30:14 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/08 12:50:33 by yohlee           ###   ########.fr       */
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
	Node() : _next(0), _prev(0), _data(0) {}

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

	virtual ~Node() {}

	Node*& next()
	{
		return (this->_next);
	}

	const Node* next() const
	{
		return (this->_next);
	}

	Node*& previous()
	{
		return (this->_prev);
	}

	const Node* previous() const
	{
		return (this->_prev);
	}

	T& getData()
	{
		return (this->_data);
	}

	const T& getData() const
	{
		return (this->_data);
	}

	void insert_before(Node* node)
	{
		if (this->_prev)
		{
			node->_prev = this->_prev;
			this->_prev->_next = node;
		}
		node->_next = this;
		this->_prev = node;
	}

	void insert_after(Node* node)
	{
		if (this->_next)
		{
			node->_next = this->_next;
			this->_next->_prev = node;
		}
		node->_prev = this;
		this->_next = node;
	}

	void reverse(void)
	{
		Node<T> *tmp = this->_prev;
		this->_prev = this->_next;
		this->_next = tmp;
	}

	void disconnect()
	{
		if (this->_prev)
			this->_prev->_next = this->_next;
		if (this->_next)
			this->_next->_prev = this->_prev;
	}

};

template <class Iterator>
class list_iterator
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
	list_iterator() : _node() {}
	explicit list_iterator(Node* node) : _node(node) {}

	list_iterator(const list_iterator<Iterator>& node) : _node(node._node)
	{
		*this = node;
	}

	list_iterator& operator=(const list_iterator<Iterator>& node)
	{
		if (*this != node)
			this->_node = node._node;
		return (*this);
	}

	~list_iterator() {}

	reference operator*() const
	{
		return (static_cast<Node*>(this->_node)->getData());
	}

	list_iterator& operator++()
	{
		this->_node = static_cast<Node*>(this->_node->next());
		return (*this);
	}

	list_iterator operator++(int)
	{
		list_iterator tmp = *this;
		this->_node = static_cast<Node*>(this->_node->next());
		return (tmp);
	}

	list_iterator& operator--()
	{
		this->_node = static_cast<Node*>(this->_node->previous());
		return (*this);
	}

	list_iterator operator--(int)
	{
		list_iterator tmp = *this;
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
bool operator==(const list_iterator<T>& lhs, const list_iterator<T>& rhs)
{
	return (lhs._node() == rhs._node());
}

template <class T>
bool operator!=(const list_iterator<T>& lhs, const list_iterator<T>& rhs)
{
	return (lhs._node() != rhs._node());
}

}

#endif