/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 08:58:20 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/01 12:24:58 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "Iterator.hpp"
# include "Allocator.hpp"
# include <iostream>

namespace ft
{

template < class T, class Alloc = ft::Allocator<T> >
class Vector
{
private:
	allocator_type	_allocator;
	pointer			_begin;
	pointer			_end;
	pointer			_end_capacity;

public:
	typedef T value_type;
	typedef Alloc allocator_type;

	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;

	typedef ft::random_access_iterator<pointer> iterator;
	typedef ft::random_access_iterator<const_pointer> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
	explicit Vector(const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0) {}

	explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0)
	{
		if (n)
			assign(n, val);
	}

	template <class InputIterator>
	Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0)
	{
		assign(first, last);
	}

	Vector(const Vector& x)
	: _allocator(x._allocator), _begin(0), _end(0), _end_capacity(0)
	{
		operator=(x);
	}

	Vector& operator=(const Vector& x)
	{
		if (this != &x)
			assign(x.begin(), x.end());
		return (*this);
	}

	~Vector()
	{
		deallocate();
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

	reference at(size_type n)
	{
		if (n >= size())
			throw "Out of Bound";
		return (this->_begin[n]);
	}

	const_reference at(size_type n) const
	{
		if (n >= size())
			throw "Out of Bound";
		return (this->_begin[n]);
	}

	reference back()
	{
		return (*(this->_end - 1));
	}

	const_reference back() const
	{
		return (*(this->_end - 1));
	}

	iterator begin()
	{
		return (iterator(&(front())));
	}

	const_iterator begin() const
	{
		return (const_iterator(&(front())));
	}
	
	size_type capacity() const
	{
		return (static_cast<size_type>(this->_end_capacity - this->_begin));
	}

	// const_iterator cbegin() const noexcept;

	// const_iterator cend() const noexcept;

	void clear()
	{
		erase(begin(), end());
	}

	// const_reverse_iterator crbegin() const noexcept;
	// const_reverse_iterator crend() const noexcept;

	value_type* data() noexcept;
	const value_type* data() const noexcept;

	template <class... Args>
	iterator emplace (const_iterator position, Args&&... args);

	template <class... Args>
	void emplace_back (Args&&... args);

	bool empty() const;

	iterator end();
	const_iterator end() const;

	iterator erase (iterator position);
	iterator erase (iterator first, iterator last);

	reference front();
	const_reference front() const;

	allocator_type get_allocator() const;


// single element (1)
	iterator insert (iterator position, const value_type& val);
// fill (2)	
	void insert (iterator position, size_type n, const value_type& val);
// range (3)	
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last);

	size_type max_size() const;

reference operator[] (size_type n);

const_reference operator[] (size_type n) const;

	void pop_back();

	void push_back (const value_type& val);

	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;

	reverse_iterator rend();
	const_reverse_iterator rend() const;

	void reserve (size_type n);

	void resize (size_type n, value_type val = value_type());
	void shrink_to_fit();
	size_type size() const;
	void swap (vector& x);


};

// (1)
template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// (2)
template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// (3)
template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// (4)
template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// (5)
template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

// (6)
template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
}

#endif

