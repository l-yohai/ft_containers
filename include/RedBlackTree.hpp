/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 08:24:51 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/17 08:35:58 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP

# include <iostream>
# include "Iterator.hpp"

namespace ft
{

template <class T, class Compare>
class MapIterator;

enum class Color
{
	RED,
	BLACK,
	DOUBLE_BLACK,
};

template <class T, class Compare>
class RedBlackTree
{
private:
	class Node
	{
	private:
		T _value;
		Color _color;
		Node* _left;
		Node* _right;
		Node* _parent;
		bool _is_left;

	public:
		explicit Node(T value)
		: _value(value), _color(Color::RED), _left(nullptr), _right(nullptr), _parent(nullptr), _is_left(true) {}

		Node(const Node& node, Node* parent = 0)
		: _value(node._value), _color(node._color), _left(node._left), _right(node._right), _parent(node._parent), _is_left(node._is_left) {}

		virtual ~Node() {}

		bool isRed(Node* node)
		{
			if (node == nullptr || node->_color != RED)
				return (false);
			return (true);
		}
	};

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
	typedef MapIterator<T, Compare> iterator;
	typedef const MapIterator<T, Compare> const_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
	explicit RedBlackTree(const Compare& comp) : _root(nullptr), _size(0), _comp(comp) {}

	RedBlackTree(const RedBlackTree& other)
	: _root(other._root), _size(other._size), _comp(other._comp)
	{
		*this = other;
	}

	RedBlackTree& operator=(const RedBlackTree& other)
	{
		this->_root = other._root;
		this->_size = other._size;
		this->_comp = other._comp;
		return (*this);
	}

	~RedBlackTree()
	{
		this->clear();
	}

	void swap(RedBlackTree& tree)
	{
		char buf[sizeof(RedBlackTree)];

		memcpy(buf, &tree, sizeof(RedBlackTree));
		memcpy(reinterpret_cast<void *>(&tree), this, sizeof(RedBlackTree));
		memcpy(reinterpret_cast<void *>(this), buf, sizeof(RedBlackTree));
	}

	size_t getSize() const
	{
		return (this->_size);
	}

	size_t getMaxSize() const
	{
		return (std::numeric_limits<difference_type>::max() / (sizeof(Node) / 2));
	}

	void clear()
	{
		this->deleteTree(this->_root);
		this->_root = nullptr;
		this->_size = 0;
	}

	Color getColor(Node*& node)
	{
		if (!node)
			return (Color::BLACK);
		return (node->_color);
	}

	void setColor(Node*& node, Color color)
	{
		if (!node)
			return ;
		node->_color = color;
	}

	Node* insertBST(Node*& node, Node*& new_node)
	{
		if (!node)
			return (new_node);
		if (new_node->_value < node->_value)
		{
			node->_left = insertBST(node->_left, new_node);
			node->_left->_parent = node;
		}
		else if (new_node->_value > node->_value)
		{
			node->_right = insertBST(node->_right, new_node);
			node->_right->_parent = node;
		}

		return (node);
	}
	
	void insertValue(T value)
	{
		Node* node = new Node(value);
		this->_root = insertBST(this->_root, node);
		fixInsertRedBlackTree(node);
	}

	void rotateLeft(Node*& node)
	{
		Node* right_child = node->_right;
		node->_right = right_child->_left;

		if (node->_right != nullptr)
			node->_right->_parent = node;

		right_child->_parent = node->_parent;

		if (node->_parent == nullptr)
			this->_root = right_child;
		else if (node == node->_parent->_left)
			node->_parent->_left = right_child;
		else
			node->_parent->_right = right_child;

		right_child->_left = node;
		node->_parent = right_child;
	}

	void rotateRight(Node*& node)
	{
		Node* left_child = node->_left;
		node->_left = left_child->_right;

		if (node->_left != nullptr)
			node->_left->_parent = node;

		left_child->_parent = node->_parent;

		if (node->_parent == nullptr)
			_root = left_child;
		else if (node == node->_parent->_left)
			node->_parent->_left = left_child;
		else
			node->_parent->_right = left_child;

		left_child->_right = node;
		node->_parent = left_child;
	}

	void fixInsertRedBlackTree(Node*& node)
	{
		Node* parent = nullptr;
		Node* grandparent = nullptr;

		while (node != _root &&
				getColor(node) == Color::RED &&
				getColor(node->_parent) == Color::RED)
		{
			parent = node->_parent;
			grandparent = parent->_parent;

			if (parent == grandparent->_left)
			{
				Node* uncle = grandparent->_right;

				if (getColor(uncle) == Color::RED)
				{
					setColor(uncle, Color::BLACK);
					setColor(parent, Color::BLACK);
					setColor(grandparent, Color::RED);

					node = grandparent;
				}
				else
				{
					if (node == parent->_right)
					{
						rotateLeft(parent);
						node = parent;
						parent = node->_parent;
					}

					rotateRight(grandparent);
					std::swap(parent->_color, grandparent->_color);

					node = parent;
				}
			}
			else
			{
				Node* uncle = grandparent->_left;

				if (getColor(uncle) == Color::RED)
				{
					setColor(uncle, Color::BLACK);
					setColor(parent, Color::BLACK);
					setColor(grandparent, Color::RED);

					node = grandparent;
				}
				else
				{
					if (node == parent->_left)
					{
						rotateRight(parent);

						node = parent;
						parent = node->_parent;
					}

					rotateLeft(grandparent);
					std::swap(parent->_color, grandparent->_color);

					node = parent;
				}
			}
		}
		setColor(this->_root, Color::BLACK);
	}

	void fixDeleteRedBlackTree(Node*& node)
	{
		if (node == nullptr)
			return;

		if (node == this->_root)
		{
			this->_root = nullptr;
			return;
		}

		if (getColor(node) == Color::RED ||
			getColor(node->_left) == Color::RED ||
			getColor(node->_right) == Color::RED)
		{
			Node* child = node->_left != nullptr ? node->_left : node->_right;

			if (node == node->_parent->_left)
			{
				node->_parent->_left = child;
				if (child != nullptr)
					child->_parent = node->_parent;
				setColor(child, Color::BLACK);
				delete (node);
			}
			else
			{
				node->_parent->_right = child;
				if (child != nullptr)
					child->_parent = node->_parent;
				setColor(child, Color::BLACK);
				delete (node);
			}
		}
		else
		{
			Node* sibling = nullptr;
			Node* parent = nullptr;
			Node* ptr = node;
			setColor(ptr, Color::DOUBLE_BLACK);

			while (ptr != this->_root && getColor(ptr) == Color::DOUBLE_BLACK)
			{
				parent = ptr->_parent;
				if (ptr == parent->_left)
				{
					sibling = parent->_right;
					if (getColor(sibling) == Color::RED)
					{
						setColor(sibling, Color::BLACK);
						setColor(parent, Color::RED);
						rotateLeft(parent);
					}
					else
					{
						if (getColor(sibling->_left) == Color::BLACK &&
							getColor(sibling->_right) == Color::BLACK)
						{
							setColor(sibling, Color::RED);
							if (getColor(parent) == Color::RED)
								setColor(parent, Color::BLACK);
							else
								setColor(parent, Color::DOUBLE_BLACK);
							ptr = parent;
						}
						else
						{
							if (getColor(sibling->_right) == Color::BLACK)
							{
								setColor(sibling->_left, Color::BLACK);
								setColor(sibling, Color::RED);
								rotateRight(sibling);
								sibling = parent->_right;
							}
							setColor(sibling, parent->_color);
							setColor(parent, Color::BLACK);
							setColor(sibling->_right, Color::BLACK);
							rotateLeft(parent);
							break;
						}
					}
				}
				else
				{
					sibling = parent->_left;
					if (getColor(sibling) == Color::RED)
					{
						setColor(sibling, Color::BLACK);
						setColor(parent, Color::RED);
						rotateRight(parent);
					}
					else
					{
						if (getColor(sibling->_left) == Color::BLACK &&
							getColor(sibling->_right) == Color::BLACK)
						{
							setColor(sibling, Color::RED);
							if (getColor(parent) == Color::RED)
								setColor(parent, Color::BLACK);
							else
								setColor(parent, Color::DOUBLE_BLACK);
							ptr = parent;
						}
						else
						{
							if (getColor(sibling->_left) == Color::BLACK)
							{
								setColor(sibling->_right, Color::BLACK);
								setColor(sibling, Color::RED);
								rotateLeft(sibling);
								sibling = parent->_left;
							}
							setColor(sibling, parent->_color);
							setColor(parent, Color::BLACK);
							setColor(sibling->_left, Color::BLACK);
							rotateRight(parent);
							break;
						}
					}
				}
			}
			if (node == node->_parent->_left)
				node->_parent->_left = nullptr;
			else
				node->_parent->_right = nullptr;
			delete (node);

			setColor(this->_root, Color::BLACK);
		}
	}

	Node* deleteBST(Node*& node, int value)
	{
		if (node == nullptr)
			return node;

		if (value < node->_value)
			return deleteBST(node->_left, value);

		if (value > node->_value)
			return deleteBST(node->_right, value);

		if (node->_left == nullptr || node->_right == nullptr)
			return node;

		Node* temp = minValueNode(node->_right);
		node->_value = temp->_value;
		return deleteBST(node->_right, temp->_value);
	}

	void deleteValue(T value)
	{
		Node* node = deleteBST(this->_root, value);
		fixDeleteRedBlackTree(node);
	}

	void inOrderBST(Node*& node)
	{
		if (node == nullptr)
			return;

		inOrderBST(node->_left);
		std::cout << node->_value << " " << static_cast<int>(node->_color) << std::endl;
		inOrderBST(node->_right);
	}

	void inOrder()
	{
		inOrderBST(this->_root);
	}


	void preOrderBST(Node*& node)
	{
		if (node == nullptr)
			return;

		std::cout << node->_value << " " << static_cast<int>(node->_color) << std::endl;
		preOrderBST(node->_left);
		preOrderBST(node->_right);
	}

	void preOrder()
	{
		preOrderBST(this->_root);
		std::cout << "---------" << std::endl;
	}

	Node* minValueNode(Node*& node)
	{
		Node* ptr = node;

		while (ptr->_left != nullptr)
			ptr = ptr->_left;

		return ptr;
	}

	Node* maxValueNode(Node*& node)
	{
		Node* ptr = node;

		while (ptr->_right != nullptr)
			ptr = ptr->_right;

		return ptr;
	}

	int getBlackHeight(Node* node)
	{
		int blackheight = 0;

		while (node != nullptr)
		{
			if (getColor(node) == Color::BLACK)
				blackheight++;
			node = node->_left;
		}
		return blackheight;
	}

	void merge(RedBlackTree Tree2)
	{
		int temp;
		Node* c, *temp_ptr;
		Node* root1 = this->_root;
		Node* root2 = Tree2._root;

		int initialblackheight1 = getBlackHeight(root1);
		int initialblackheight2 = getBlackHeight(root2);

		if (initialblackheight1 > initialblackheight2)
		{
			c = maxValueNode(root1);
			temp = c->_value;

			deleteValue(c->_value);
			root1 = this->_root;
		}
		else if (initialblackheight2 > initialblackheight1)
		{
			c = minValueNode(root2);
			temp = c->_value;

			Tree2.deleteValue(c->_value);
			root2 = Tree2._root;
		}
		else
		{
			c = minValueNode(root2);
			temp = c->_value;

			Tree2.deleteValue(c->_value);
			root2 = Tree2._root;

			if (initialblackheight1 != getBlackHeight(root2))
			{
				Tree2.insertValue(c->_value);
				root2 = Tree2._root;

				c = maxValueNode(root1);
				temp = c->_value;

				deleteValue(c->_value);
				root1 = this->_root;
			}
		}

		setColor(c, Color::RED);

		int finalblackheight1 = getBlackHeight(root1);
		int finalblackheight2 = getBlackHeight(root2);

		if (finalblackheight1 == finalblackheight2)
		{
			c->_left = root1;
			root1->_parent = c;
			c->_right = root2;
			root2->_parent = c;
			setColor(c, Color::BLACK);
			c->_value = temp;
			this->_root = c;
		}
		else if (finalblackheight2 > finalblackheight1)
		{
			Node* ptr = root2;

			while (finalblackheight1 != getBlackHeight(ptr))
			{
				temp_ptr = ptr;
				ptr = ptr->_left;
			}

			Node* ptr_parent;

			if (ptr == nullptr)
				ptr_parent = temp_ptr;
			else
				ptr_parent = ptr->_parent;

			c->_left = root1;
			if (root1 != nullptr)
				root1->_parent = c;
			c->_right = ptr;
			if (ptr != nullptr)
				ptr->_parent = c;
			ptr_parent->_left = c;

			c->_parent = ptr_parent;
			if (getColor(ptr_parent) == Color::RED)
			{
				fixInsertRedBlackTree(c);
			}
			else if (getColor(ptr) == Color::RED)
			{
				fixInsertRedBlackTree(ptr);
			}

			c->_value = temp;
			this->_root = root2;
		}
		else
		{
			Node* ptr = root1;

			while (finalblackheight2 != getBlackHeight(ptr))
			{
				ptr = ptr->_right;
			}

			Node* ptr_parent = ptr->_parent;

			c->_right = root2;
			root2->_parent = c;
			c->_left = ptr;
			ptr->_parent = c;
			ptr_parent->_right = c;

			c->_parent = ptr_parent;
			if (getColor(ptr_parent) == Color::RED)
				fixInsertRedBlackTree(c);
			else if (getColor(ptr) == Color::RED)
				fixInsertRedBlackTree(ptr);

			c->_value = temp;
			this->_root = root1;
		}
		return;
	}
};

template <class T, class Compare>
class MapIterator
{
private:
	friend class RedBlackTree<T, Compare>;
	typedef RedBlackTree<T, Compare>::Node Node;
	typedef RedBlackTree<T, Compare> Tree;

	Node* _node;
	Tree* _tree;

public:
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef ptrdiff_t difference_type;

	MapIterator(Node* node, Tree const* tree) : _node(nullptr), _tree(nullptr) {}

	MapIterator(MapIterator<T, Compare> const& other) : _node(other._node), _tree(other._tree) {}

	MapIterator& operator=(MapIterator<T, Compare> const& other)
	{
		MapIterator tmp(other);
		swap(tmp);
		return (*this);
	}

	MapIterator& operator++()
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
			while (this->_node && this->_node->_parent && !this->_node->isLeft)
				this->_node = this->_node->_parent;
			this->_node = this->_node->_parent;
		}
		return (*this);
	}

	MapIterator operator++(int)
	{
		MapIterator tmp(*this);
		operator++();

		return (tmp);
	}

	MapIterator& operator--()
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
			while (this->_node && this->_node->_parent && this->_node->isLeft)
				this->_node = this->_node->_parent;
			this->_node = this->_node->_parent;
		}
		return (*this);
	}

	MapIterator operator--(int)
	{
		MapIterator tmp(*this);
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

	friend bool operator==(const MapIterator& lhs, const MapIterator& rhs)
	{
		return lhs._node == rhs._node;
	}

	friend bool operator!=(const MapIterator& lhs, const MapIterator& rhs)
	{
		return lhs._node != rhs._node;
	}

	void swap(MapIterator& x)
	{
		char buf[sizeof(MapIterator)];

		memcpy(buf, &x, sizeof(MapIterator));
		memcpy(reinterpret_cast<void *>(&x), this, sizeof(MapIterator));
		memcpy(reinterpret_cast<void *>(this), buf, sizeof(MapIterator));
	}

};

template <class T, class Compare>
void swap(ft::RedBlackTree<T, Compare> &a, ft::RedBlackTree<T, Compare> &b)
{
	a.swap(b);
}

}

#endif
