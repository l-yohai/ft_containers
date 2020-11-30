/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 08:24:51 by yohlee            #+#    #+#             */
/*   Updated: 2020/12/01 01:03:53 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <iostream>
# include "iterator.hpp"

namespace ft
{

template <class T, class Compare, bool flag = false>
class TreeIterator;

enum Color
{
	RED,
	BLACK,
};

template <class T, class Compare>
class RedBlackTree
{
private:
	template <class U, class Comp, bool flag>
	friend class TreeIterator;

	struct Node
	{
		T _value;
		Node* _parent;
		Node* _left;
		Node* _right;
		Color _color;
		bool _is_left;

		Node(T value, Node* _parent = 0, bool is_left = true, Color color = RED) : _value(value), _parent(_parent), _left(0), _right(0), _color(color), _is_left(is_left) {}

		Node(Node const& x, Node* parent = 0) : _value(x._value), _parent(parent), _left(0), _right(0), _color(x._color), _is_left(x._is_left) {}
	};

	bool isRed(Node* node)
	{
		if (node == nullptr || node->_color != RED)
			return (false);
		return (true);
	}

private:
	Node* _root;
	size_t _size;
	Compare _comp;

public:
	typedef Compare value_compare;
	typedef T value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef TreeIterator<T, Compare> iterator;
	typedef TreeIterator<T, Compare, true> const_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
	explicit RedBlackTree(const Compare& comp)
	: _root(0), _size(0), _comp(comp) {}

	RedBlackTree(const RedBlackTree& x) : _root(0), _size(x._size), _comp(x._comp)
	{
		if (_size)
		{
			_root = new Node(*x._root);
			copy(_root, x._root);
		}
	}

	RedBlackTree& operator=(const RedBlackTree& x)
	{
		RedBlackTree ret(x);
		swap(ret);
		return (*this);
	}

	~RedBlackTree()
	{
		deleteTree(_root);
		_root = nullptr;
		_size = 0;
	}

	void swap(RedBlackTree& x)
	{
		char buf[sizeof(RedBlackTree)];

		memcpy(buf, &x, sizeof(RedBlackTree));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(RedBlackTree));
		memcpy(reinterpret_cast<char *>(this), buf, sizeof(RedBlackTree));
	}

	void clear()
	{
		deleteTree(_root);
		_root = nullptr;
		_size = 0;
	}

	size_t size() const
	{
		return (_size);
	}

	size_t max_size() const
	{
		return (std::numeric_limits<difference_type>::max() / (sizeof(Node) / 2));
	}

	Node* search(const value_type& key) const
	{
		return (search(_root, key));
	}

	Node* search(Node* node, const value_type& key) const
	{
		while (node)
		{
			if (!_comp(node->_value, key) && !_comp(key, node->_value))
			{
				iterator it(node, this);
				iterator next(node, this);
				for (--next; next._node && (!_comp(*next, key) && !_comp(key, *next)); --next)
					--it;
				return (it._node);
			}
			if (!_comp(node->_value, key))
				node = node->_left;
			else
				node = node->_right;
		}
		return (nullptr);
	}

	Node* lower_bound(const value_type& key) const
	{
		iterator it(min(), this);
		while (it._node && _comp(*it, key))
			++it;
		return (it._node);
	}

	Node* upper_bound(const value_type& key) const
	{
		iterator it(min(), this);
		while (it._node && !_comp(key, *it))
			++it;
		return (it._node);
	}

	Node* insert(value_type toAdd)
	{
		Node* added;

		_root = insert(0, _root, toAdd, true, &added);
		_root->_color = BLACK;
		return (added);
	}

	Node* insert(iterator it, value_type value)
	{
		return (insert(it._node, value));
	}

	Node* insert(Node* preceding, value_type value)
	{
		bool first = false;
		iterator it(preceding, this);
		while (it._node)
		{
			if (_comp(value, *it))
			{
				first = true;
				--it;
			}
			else if (_comp(*it, value))
			{
				if (first)
					break;
				++it;
			}
			else
			{
				Node* added = new Node(value, it._node->_parent, it._node->_is_left);
				if (added->_parent)
					added->_is_left ? added->_parent->_left = added : added->_parent->_right = added;
				else
					_root = added;
				added->_left = it._node->_left;
				if (added->_left)
					added->_left->_parent = added;
				it._node->_left = 0;
				it._node->_is_left = false;
				added->_right = it._node;
				it._node->_parent = added;
				++_size;
				return (added);
			}
		}
		return (insert(value));
	}

	Node* insert(Node* parent, Node* x, value_type &value, bool left, Node* *added)
	{
		if (x == 0)
		{
			++_size;
			*added = new Node(value, parent, left);
			return (*added);
		}
		if (!this->_comp(x->_value, value) && !this->_comp(value, x->_value))
			*added = x;
		else if (!this->_comp(value, x->_value))
			x->_right = insert(x, x->_right, value, false, added);
		else
			x->_left = insert(x, x->_left, value, true, added);

		if (isRed(x->_right) && !isRed(x->_left))
			x = rotateLeft(x);
		if (isRed(x->_left) && isRed(x->_left->_left))
			x = rotateRight(x);
		if (isRed(x->_left) && isRed(x->_right))
			colorFlip(x);
		return (x);
	}

	bool deleteKey(value_type value)
	{
		if (!search(_root, value))
		{
			return (false);
		}
		if (_size < 2)
		{
			_size = 0;
			delete _root;
			_root = nullptr;
			return (true);
		}
		if (!isRed(_root->_left) && !isRed(_root->_right))
			_root->_color = RED;
		_root = deleteKey(_root, value);
		if (_root)
			_root->_color = BLACK;
		return (true);
	}

	Node* deleteKey(Node* x, value_type &value)
	{
		if (_comp(value, x->_value))
		{
			if (!isRed(x->_left) && x->_left && !isRed(x->_left->_left))
				x = moveRedLeft(x);
			x->_left = deleteKey(x->_left, value);
		}
		else
		{
			if (isRed(x->_left))
				x = rotateRight(x);
			if (!_comp(x->_value, value) && !x->_right)
			{
				--_size;
				delete x;
				return (0);
			}
			if (!isRed(x->_right) && x->_right && !isRed(x->_right->_left))
				x = moveRedRight(x);
			if (!_comp(x->_value, value) && !_comp(value, x->_value))
			{
				Node* h = min(x->_right);
				x->_value = h->_value;
				x->_right = deleteMin(x->_right);
			}
			else
				x->_right = deleteKey(x->_right, value);
		}
		return (balance(x));
	}

	Node* deleteKey(iterator it)
	{
		return (deleteKey(it._node));
	}

	Node* deleteKey(Node* x)
	{
		Node* ret = 0;
		if (!x)
			return (x);
		if (_size == 1)
			_root = nullptr;
		else if (!x->_right)
		{
			if (!x->_parent)
			{
				_root = x->_left;
				_root->_parent = 0;
			}
			else
			{
				(x->_is_left) ? x->_parent->_left = x->_left : x->_parent->_right = x->_left;
				if (x->_left)
				{
					x->_left->_is_left = x->_is_left;
					x->_left->_parent = x->_parent;
				}
				if (x->_is_left)
					ret = x->_parent;
				else
				{
					iterator it(x, this);
					++it;
					ret = it._node;
				}
			}
		}
		else
			ret = eraseRight(x);
		--_size;
		delete x;
		return (ret);
	}

	Node* eraseRight(Node* x)
	{
		Node* h = min(x->_right);

		h->_is_left ? h->_parent->_left = h->_right : h->_parent->_right = h->_right;
		if (h->_parent->_left)
		{
			h->_parent->_left->_parent = h->_parent;
			h->_parent->_left->_is_left = true;
		}
		if (h->_parent->_right)
			h->_parent->_right->_parent = h->_parent;
		h->_is_left = x->_is_left;
		h->_color = x->_color;
		h->_parent = x->_parent;
		if (!h->_parent)
			_root = h;
		else
			x->_is_left ? h->_parent->_left = h : h->_parent->_right = h;
		if (x->_right)
		{
			h->_right = x->_right;
			h->_right->_parent = h;
		}
		h->_left = x->_left;
		h->_left ? h->_left->_parent = h : 0;
		return (h);
	}

	void deleteMin()
	{
		if (_root == 0)
			return ;
		if (!isRed(_root->_left && !isRed(_root->_right)))
			_root->_color = RED;
		_root = deleteMin(_root);
		if (_root)
			_root->_color = BLACK;
	}

	Node* deleteMin(Node* h)
	{
		if (!h->_left)
		{
			--_size;
			delete h;
			return (0);
		}
		if (!isRed(h->_left) && !isRed(h->_left->_left))
			h = moveRedLeft(h);
		h->_left = deleteMin(h->_left);
		return (balance(h));
	}

	void deleteMax()
	{
		if (_root == 0)
			return ;
		if (!isRed(_root->_left && !isRed(_root->_right)))
			_root->_color = RED;

		_root = deleteMax(_root);
		if (_root)
			_root->_color = BLACK;
	}

	Node* deleteMax(Node* h)
	{
		if (isRed(h->_left))
			h = rotateRight(h);
		if (h->_right == 0)
		{
			--_size;
			delete h;
			return (0);
		}
		if (!isRed(h->_right) && !isRed(h->_right->_left))
			h = moveRedRight(h->_right);

		h->_right = deleteMax(h->_right);
		return (balance(h));
	}

	void colorFlip(Node* node)
	{
		if (node->_color == RED)
			node->_color = BLACK;
		else
			node->_color = RED;

		if (node->_left->_color == RED)
			node->_left->_color = BLACK;
		else
			node->_left->_color = RED;
		
		if (node->_right->_color == RED)
			node->_right->_color = BLACK;
		else
			node->_right->_color = RED;
	}

	Node* rotateLeft(Node* h)
	{
		Node* x = h->_right;
		h->_right = x->_left;
		if (h->_right)
		{
			h->_right->_parent = h;
			h->_right->_is_left = false;
		}
		x->_parent = h->_parent;
		x->_is_left = h->_is_left;
		x->_color = h->_color;
		x->_left = h;
		h->_is_left = true;
		h->_parent = x;
		h->_color = RED;
		return (x);
	}

	Node* rotateRight(Node* h)
	{
		Node* x = h->_left;
		h->_left = x->_right;
		if (h->_left)
		{
			h->_left->_parent = h;
			h->_left->_is_left = true;
		}
		x->_parent = h->_parent;
		x->_is_left = h->_is_left;
		x->_color = h->_color;
		x->_right = h;
		h->_is_left = false;
		h->_parent = x;
		h->_color = RED;
		return (x);
	}

	Node* moveRedLeft(Node* h)
	{
		colorFlip(h);
		if (isRed(h->_right->_left))
		{
			h->_right = rotateRight(h->_right);
			h = rotateLeft(h);
			colorFlip(h);
		}
		return (h);
	}

	Node* moveRedRight(Node* h)
	{
		colorFlip(h);
		if (isRed(h->_left->_left))
		{
			h = rotateRight(h);
			colorFlip(h);
		}
		return (h);
	}

	Node* balance(Node* h)
	{
		if (isRed(h->_right))
			h = rotateLeft(h);
		if (isRed(h->_left) && isRed(h->_left->_left))
			h = rotateRight(h);
		if (isRed(h->_left) && isRed(h->_right))
			colorFlip(h);

		return (h);
	}

	void deleteTree(Node* node)
	{
		if (node == 0)
			return ;
		deleteTree(node->_left);
		deleteTree(node->_right);
		delete node;
	}

	void copy(Node* dest, Node* src)
	{
		if (src->_left)
		{
			dest->_left = new Node(*src->_left, dest);
			copy(dest->_left, src->_left);
		}
		if (src->_right)
		{
			dest->_right = new Node(*src->_right, dest);
			copy(dest->_right, src->_right);
		}
	}

	inline Node* min() const
	{
		return (min(_root));
	}

	inline Node* min(Node* node) const
	{
		while (node && node->_left)
			node = node->_left;
		return (node);
	}

	inline Node* max() const
	{
		return (max(_root));
	}

	inline Node* max(Node* node) const
	{
		while (node && node->_right)
			node = node->_right;
		return (node);
	}

};

template <class T, class Compare, bool flag>
class TreeIterator
{
private:
	friend class RedBlackTree<T, Compare>;
	friend class TreeIterator<T, Compare, false>;
	friend class TreeIterator<T, Compare, true>;

	typedef typename ft::is_const<flag, typename RedBlackTree<T, Compare>::Node const, typename RedBlackTree<T, Compare>::Node>::type Node;
	typedef typename ft::is_const<flag, const RedBlackTree<T, Compare>, RedBlackTree<T, Compare> >::type Tree;

	Node* _node;
	const Tree* _tree;

public:
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef typename ft::is_const<flag, const T &, T &>::type reference;
	typedef typename ft::is_const<flag, const T *, T *>::type pointer;
	typedef ptrdiff_t difference_type;

	TreeIterator(Node* node = 0, Tree const* tree = 0) : _node(node), _tree(tree) {}

	TreeIterator(TreeIterator<T, Compare> const& other) : _node(other._node), _tree(other._tree) {}

	TreeIterator& operator=(TreeIterator<T, Compare> const& other)
	{
		TreeIterator tmp(other);
		swap(tmp);
		return (*this);
	}

	TreeIterator& operator++()
	{
		if (this->_node == nullptr)
			this->_node = this->_tree->min();
		else if (this->_node->_right)
		{
			this->_node = this->_node->_right;
			while (this->_node && this->_node->_left)
				this->_node = this->_node->_left;
		}
		else
		{
			while (this->_node && this->_node->_parent && !this->_node->_is_left)
				this->_node = this->_node->_parent;
			this->_node = this->_node->_parent;
		}
		return (*this);
	}

	TreeIterator operator++(int)
	{
		TreeIterator tmp(*this);
		operator++();

		return (tmp);
	}

	TreeIterator& operator--()
	{
		if (this->_node == 0)
			this->_node = this->_tree->max();
		else if (this->_node->_left)
		{
			this->_node = this->_node->_left;
			while (this->_node && this->_node->_right)
				this->_node = this->_node->_right;
		}
		else
		{
			while (this->_node && this->_node->_parent && this->_node->_is_left)
				this->_node = this->_node->_parent;
			this->_node = this->_node->_parent;
		}
		return (*this);
	}

	TreeIterator operator--(int)
	{
		TreeIterator tmp(*this);
		operator--();

		return (tmp);
	}

	reference operator*() const
	{
		return (this->_node->_value);
	}

	pointer operator->() const
	{
		return (&(this->_node->_value));
	}

	friend bool operator==(const TreeIterator& lhs, const TreeIterator& rhs)
	{
		return lhs._node == rhs._node;
	}

	friend bool operator!=(const TreeIterator& lhs, const TreeIterator& rhs)
	{
		return lhs._node != rhs._node;
	}

	void swap(TreeIterator& x)
	{
		char buf[sizeof(TreeIterator)];

		memcpy(buf,& x, sizeof(TreeIterator));
		memcpy(reinterpret_cast<void *>(&x), this, sizeof(TreeIterator));
		memcpy(reinterpret_cast<void *>(this), buf, sizeof(TreeIterator));
	}

};

template <class T, class Compare>
void swap(ft::RedBlackTree<T, Compare> &a, ft::RedBlackTree<T, Compare> &b)
{
	a.swap(b);
}

}

#endif
