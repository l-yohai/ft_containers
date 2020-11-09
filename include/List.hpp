/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:20:17 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/10 07:37:54 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include "Allocator.hpp"
# include "Iterator.hpp"
# include "Node.hpp"

namespace ft
{

template < class T, class Alloc = ft::Allocator<T> >
class List
{
public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef list_iterator::value_type iterator;
	typedef const list_iterator::value_type const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

private:
	allocator_type _allocator;
	Node<T>* _node;
	size_type _size;

public:

	explicit List(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _size(0)
	{
		this->_node = new Node<T>();
		this->_node->_prev = this->_node;
		this->_node->_next = this->_node;
	}

	explicit List(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _size(0)
	{
		this->_node = new Node<T>();
		this->_node->_prev = this->_node;
		this->_node->_next = this->_node;
		insert(begin(), n, value);
	}

	template <class InputIterator>
	List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _size(0)
	{
		this->_node = new Node<T>();
		this->_node->_prev = this->_node;
		this->_node->_next = this->_node;
		insert(begin(), first, last);
	}

	List(const List& x) : _allocator(x._allocator), _size(x._size)
	{
		this->_node = new Node<T>();
		this->_node->_prev = this->_node;
		this->_node->_next = this->_node;
		insert(begin(), x.begin(), x.end());
	}

	~List()
	{
		clear();
		delete[] this->_node;
	}

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		clear();
		insert(begin(), first, last);
	}
	
	void assign(size_type n, const value_type& val)
	{
		clear();
		insert(begin(), n, val);
	}

	reference back()
	{
		return (this->_node->_prev->_data);
	}

	const_reference back() const
	{
		return (this->_node->_prev->_data);
	}

	iterator begin()
	{
		return (iterator(this->_node->_next));
	}

	const_iterator begin() const
	{
		return (const_iterator(this->_node->_next));
	}

	void clear()
	{
		erase(begin(), end());
	}

	bool empty() const
	{
		(this->_size) ? return (false) : return (true);
	}

	iterator end()
	{
		return (iterator(this->_node));
	}

	const_iterator end() const
	{
		return (const_iterator(this->_node));
	}

	iterator erase(iterator position)
	{
		iterator it(position);
		return (erase(position, ++it));
	}

	iterator erase(iterator first, iterator last)
	{
		iterator it = iterator(first);

		while (it != last)
		{
			Node *new = it.getNode();
			it++;
		}
	}

	reference front()
	{
		return (this->_node->_next->_data);
	}

	const_reference front() const
	{
		return (this->_node->_next->_data);
	}

	// single element (1)
	iterator insert(iterator position, const value_type& val)
	{
		insert(position, 1, val);
		return (iterator(position.getNode()->next()));
	}
	// fill (2)
	void insert(iterator position, size_type n, const value_type& val)
	{
		if (n)
		{
			List new;
			iterator it = begin();

			while (it != position)
				new.push_back(*it++);
			
			while (n--)
				new.push_back(val);

			iterator ite = end();
			while (it != ite)
				new.push_back(*it++);

			swap(new);
		}
	}
	// range (3)
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		if (first != last)
		{
			List new;
			iterator it = begin();

			while (it != position)
				new.push_back(*it++);

			while (first != last)
				new.push_back(*first++);

			iterator ite = end();
			while (it != ite)
				new.push_back(*it++);

			swap(new);
		}
	}

	size_type max_size() const
	{
		return (std::numeric_limits<size_type>::max() / sizeof(Node<T>));
	}

	void merge(List& x)
	{
		iterator i1 = begin();
		iterator i2 = x.begin();

		while (i1 != end() && i2 != x.end())
		{
			if (*i1 > *i2)
				insert(i1, *it2++);
			else
				++i1;
		}
		if (i2 != x.end())
			insert(end(), i2, x.end());
		x.clear();
	}

	template <class Compare>
	void merge(List& x, Compare comp)
	{
		iterator i1 = begin();
		iterator i2 = x.begin();

		while (i1 != end() && i2 != x.end())
		{
			if (comp(*i2, *i1))
				insert(i1, *it2++);
			else
				++i1;
		}
		if (i2 != x.end())
			insert(end(), i2, x.end());
		x.clear();
	}

	// copy (1)
	List& operator=(const List& x)
	{
		clear();
		insert(begin(), x.begin(), x.end());
		return (*this);
	}

	void pop_back()
	{
		iterator it(end());
		erase(--it);
	}

	void pop_front()
	{
		erase(begin());
	}

	void push_back(const value_type& val)
	{
		insert(end(), val);
	}

	void push_front(const value_type& val)
	{
		insert(begin(), val);
	}

	reverse_iterator rbegin()
	{
		return (reverse_iterator(end()));
	}

	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(end()));
	}

	void remove(const value_type& val)
	{
		for (iterator it = begin(); it != end(); ++it)
		{
			if (*it == val)
				it = erase(it);
		}
	}

	template <class Predicate>
	void remove_if(Predicate pred)
	{
		for (iterator it = begin(); it != end(); ++it)
		{
			if (pred(*it))
				it = erase(it);
		}
	}

	reverse_iterator rend()
	{
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(begin()));
	}

	void resize(size_type n, value_type val = value_type())
	{
		int diff = n - this->len;
		if (!diff)
			return ;
		else if (diff > 0)
		{
			for (int i = 0; i < diff; ++i)
				push_back(val);
		}
		else
		{
			for (int i = 0; i < diff * (-1); ++i)
				pop_back();
		}
	}

	void reverse()
	{
		iterator i1 = begin();
		iterator i2 = end()._node->prev;

		for (size_t i = 1; i <= this->_size / 2; ++i)
		{
			swap(*i1, *i2);
			++i1;
			--i2;
		}
	}

	size_type size() const
	{
		return (this->_size);
	}

	// (1)
	void sort()
	{

	}
	// (2)
	template <class Compare>
	void sort(Compare comp)
	{

	}

	// entire List (1)
	void splice(iterator position, List& x)
	{

	}
	// single element (2)
	void splice(iterator position, List& x, iterator i)
	{

	}
	// element range (3)
	void splice(iterator position, List& x, iterator first, iterator last)
	{

	}

	void swap(List& x)
	{

	}

	// (1)
	void unique()
	{

	}
	// (2)
	template <class BinaryPredicate>
	void unique(BinaryPredicate binary_pred)
	{

	}

	// (1)
	template <class T, class Alloc>
	bool operator==(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{

	}
	// (2)
	template <class T, class Alloc>
	bool operator!=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{

	}
	// (3)
	template <class T, class Alloc>
	bool operator<(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{

	}
	// (4)
	template <class T, class Alloc>
	bool operator<=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
	}
	// (5)
	template <class T, class Alloc>
	bool operator>(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
	}
	// (6)
	template <class T, class Alloc>
	bool operator>=(const List<T,Alloc>& lhs, const List<T,Alloc>& rhs)
	{
	}

	template <class T, class Alloc>
	void swap (List<T,Alloc>& x, List<T,Alloc>& y)
	{
	}

};

}

#endif