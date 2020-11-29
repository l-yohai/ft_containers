/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 08:24:51 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/29 23:52:03 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <iostream>
# include "iterator.hpp"

namespace ft
{

template <class T, class Compare, bool flag = false>
class tree_iterator;

enum Color
{
	RED,
	BLACK,
};

template <class T, class Compare>
class red_black_tree
{
private:
	template <class U, class Comp, bool flag>
	friend class tree_iterator;

	struct Node
	{
		T _value;
		Node *_parent;
		Node *_left;
		Node *_right;
		Color _color;
		bool _is_left;

		Node(T value, Node *_parent = 0, bool left = true, Color color = RED) : _value(value),
																			   _parent(_parent),
																			   _left(0),
																			   _right(0),
																			   _color(color),
																			   _is_left(left) {}
		Node(Node const &x, Node *parent = 0) : _value(x._value),
												_parent(parent),
												_left(0),
												_right(0),
												_color(x._color),
												_is_left(x._is_left) {}
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
	typedef value_type &reference;
	typedef const value_type &const_reference;
	typedef value_type *pointer;
	typedef const value_type *const_pointer;
	typedef tree_iterator<T, Compare> iterator;
	typedef tree_iterator<T, Compare, true> const_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
	explicit red_black_tree(const Compare &comp)
	: _root(0), _size(0), _comp(comp) {}

	red_black_tree(const red_black_tree &x) : _root(0), _size(x._size), _comp(x._comp)
	{
		if (_size)
		{
			_root = new Node(*x._root);
			copyTree(_root, x._root);
		}
	}

	~red_black_tree()
	{
		deleteTree(_root);
		_root = 0;
		_size = 0;
	}

	red_black_tree &operator=(const red_black_tree &x)
	{
		red_black_tree ret(x);
		swap(ret);
		return *this;
	}

	void swap(red_black_tree &x)
	{
		char buffer[sizeof(red_black_tree)];

		memcpy(buffer, &x, sizeof(red_black_tree));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(red_black_tree));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(red_black_tree));
	}

	void clear()
	{
		deleteTree(_root);
		_root = 0;
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

	Node *find(const value_type &k) const
	{
		return (find(_root, k));
	}

	Node *find(Node *node, const value_type &k) const
	{
		while (node)
		{
			if (!_comp(node->_value, k) && !_comp(k, node->_value))
			{
				iterator it(node, this);
				iterator next(node, this);
				for (--next; next._node && (!_comp(*next, k) && !_comp(k, *next)); --next)
					--it;
				return (it._node);
			}
			if (!_comp(node->_value, k))
				node = node->_left;
			else
				node = node->_right;
		}
		return (nullptr);
	}

	Node *lower_bound(const value_type &k) const
	{
		iterator it(min(), this);
		while (it._node && _comp(*it, k))
			++it;
		return (it._node);
	}

	Node *upper_bound(const value_type &k) const
	{
		iterator it(min(), this);
		while (it._node && !_comp(k, *it))
			++it;
		return (it._node);
	}

	size_type count(const value_type &k) const
	{
		size_type count = 0;

		for (red_black_tree<T, Compare> it(find(_root, k), this);
			 it._node && !_comp(*it, k) && !_comp(k, *it); ++it)
			++count;
		return (count);
	}

	Node *add(value_type toAdd)
	{
		Node *added;  // sending address to this pointer so that I can ft::is_const it even with the recursive

		_root = add(0, _root, toAdd, true, &added);
		_root->_color = BLACK;
		return (added);
	}

	Node *add(iterator it, value_type value) { return (add(it._node, value)); }

	Node *add(Node *preceding, value_type value)
	{
		bool first = false;
		iterator it(preceding, this);
		while (it._node)
		{
			if (_comp(value, *it))
			{  // --> value < it
				first = true;
				--it;
			}
			else if (_comp(*it, value))
			{  // --> value > it
				if (first)
					break;
				++it;
			}
			else
			{
				Node *added = new Node(value, it._node->_parent, it._node->_is_left);
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
		return (add(value));
	}

	Node *add(Node *parent, Node *x, value_type &value, bool left, Node **added)
	{
		if (x == 0)
		{
			++_size;
			*added = new Node(value, parent, left);
			return (*added);
		}
		if (!this->_comp(x->_value, value) && !this->_comp(value, x->_value))	// ---> EQUAL
			*added = x;
		else if (!this->_comp(value, x->_value))
			x->_right = add(x, x->_right, value, false, added);
		else
			x->_left = add(x, x->_left, value, true, added);  // if comp gives false

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
		if (!find(_root, value))
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

	Node *deleteKey(Node *x, value_type &value)
	{
		if (comp(value, x->_value))
		{
			if (!isRed(x->_left) && x->_left && !isRed(x->_left->_left))
				x = moveRedLeft(x);
			x->_left = deleteKey(x->_left, value);
		}
		else
		{
			if (isRed(x->_left))
				x = rotateRight(x);
			if (!comp(x->_value, value) && !x->_right)
			{  // EQUAL
				--_size;
				delete x;
				return (0);
			}
			if (!isRed(x->_right) && x->_right && !isRed(x->_right->_left))
				x = moveRedRight(x);
			if (!comp(x->_value, value) && !comp(value, x->_value))
			{
				Node *h = min(x->_right);
				x->_value = h->_value;
				x->_right = deleteMin(x->_right);
			}
			else
				x->_right = deleteKey(x->_right, value);
		}
		return (balance(x));
	}

	Node *deleteKey(iterator it)
	{
		return (deleteKey(it._node));
	}

	Node *deleteKey(Node *x)
	{
		Node *ret = 0;
		if (!x)
			return (x);
		if (_size == 1)
			_root = 0;
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

	Node *eraseRight(Node *x)
	{
		Node *h = min(x->_right);

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
		{  // x->right wasn't h or it was but h had a right child
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

	Node *deleteMin(Node *h)
	{
		if (!h->_left)
		{
			// std::cout << "delete no left child "  << h->_value << std::endl;
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
		// if (_root == 0) throw
		if (_root == 0)
			return ;
		if (!isRed(_root->_left && !isRed(_root->_right)))
			_root->_color = RED;

		_root = deleteMax(_root);
		if (_root)
			_root->_color = BLACK;
	}

	Node *deleteMax(Node *h)
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

	void colorFlip(Node *node)
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

	Node *rotateLeft(Node *h)
	{
		Node *x = h->_right;
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

	Node *rotateRight(Node *h)
	{
		Node *x = h->_left;
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

	Node *moveRedLeft(Node *h)
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

	Node *moveRedRight(Node *h)
	{
		colorFlip(h);
		if (isRed(h->_left->_left))
		{
			h = rotateRight(h);
			colorFlip(h);
		}
		return (h);
	}

	Node *balance(Node *h)
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

	void copyTree(Node *dest, Node *src)
	{
		if (src->_left)
		{
			dest->_left = new Node(*src->_left, dest);
			copyTree(dest->_left, src->_left);
		}
		if (src->_right)
		{
			dest->_right = new Node(*src->_right, dest);
			copyTree(dest->_right, src->_right);
		}
	}

	inline Node *min() const
	{
		return (min(_root));
	}

	inline Node *min(Node *node) const
	{
		while (node && node->_left)
			node = node->_left;
		return (node);
	}

	inline Node *max() const
	{
		return (max(_root));
	}

	inline Node *max(Node *node) const
	{
		while (node && node->_right)
			node = node->_right;
		return (node);
	}

	size_t heigth()
	{
		if (!_root)
			return (0);
		return (height(_root) - 1);
	}

	size_t heigth(Node *node)
	{
		if (node == 0)
			return (0);
		size_t left = height(node->_left);
		size_t right = height(node->_right);
		if (left > right)
			return (left + 1);
		return (right + 1);
	}

	int blackNodes(Node *node)
	{
		if (node == 0)
			return (1);
		int left = blackNodes(node->_left);
		int right = blackNodes(node->_right);
		if (left < right)
			fixUnevenBlack(node);
		if (node->_color)
			return (left + right);
		return (left + right + 1);
	}

};

template <class T, class Compare, bool flag>
class tree_iterator
{
private:
	friend class red_black_tree<T, Compare>;
	friend class tree_iterator<T, Compare, false>;
	friend class tree_iterator<T, Compare, true>;

	typedef typename ft::is_const<flag, typename red_black_tree<T, Compare>::Node const, typename red_black_tree<T, Compare>::Node>::type Node;
	typedef typename ft::is_const<flag, const red_black_tree<T, Compare>, red_black_tree<T, Compare> >::type Tree;

	Node* _node;
	const Tree* _tree;

public:
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef typename ft::is_const<flag, const T &, T &>::type reference;
	typedef typename ft::is_const<flag, const T *, T *>::type pointer;
	typedef ptrdiff_t difference_type;

	tree_iterator(Node* node = 0, Tree const* tree = 0) : _node(node), _tree(tree) {}

	tree_iterator(tree_iterator<T, Compare> const& other) : _node(other._node), _tree(other._tree) {}

	tree_iterator& operator=(tree_iterator<T, Compare> const& other)
	{
		tree_iterator tmp(other);
		swap(tmp);
		return (*this);
	}

	tree_iterator& operator++()
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

	tree_iterator operator++(int)
	{
		tree_iterator tmp(*this);
		operator++();

		return (tmp);
	}

	tree_iterator& operator--()
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

	tree_iterator operator--(int)
	{
		tree_iterator tmp(*this);
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

	friend bool operator==(const tree_iterator& lhs, const tree_iterator& rhs)
	{
		return lhs._node == rhs._node;
	}

	friend bool operator!=(const tree_iterator& lhs, const tree_iterator& rhs)
	{
		return lhs._node != rhs._node;
	}

	void swap(tree_iterator& x)
	{
		char buf[sizeof(tree_iterator)];

		memcpy(buf, &x, sizeof(tree_iterator));
		memcpy(reinterpret_cast<void *>(&x), this, sizeof(tree_iterator));
		memcpy(reinterpret_cast<void *>(this), buf, sizeof(tree_iterator));
	}

};

template <class T, class Compare>
void swap(ft::red_black_tree<T, Compare> &a, ft::red_black_tree<T, Compare> &b)
{
	a.swap(b);
}

}

#endif