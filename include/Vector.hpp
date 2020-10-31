/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 08:58:20 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/31 15:32:59 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class Vector
{
public:
	typedef T value_type;
	typedef Alloc allocator_type;

	typedef typename Alloc::reference reference;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::pointer pointer;
	typedef typename Alloc::const_pointer const_pointer;

	typedef random_access_iterator<pointer> iterator;
	typedef random_access_iterator<const_pointer> const_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;

	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

public:
	/* ====================================================================== */
	/*           ___                _                   _                     */
	/*          / __\___  _ __  ___| |_ _ __ _   _  ___| |_ ___  _ __         */
	/*         / /  / _ \| '_ \/ __| __| '__| | | |/ __| __/ _ \| '__|        */
	/*        / /__| (_) | | | \__ \ |_| |  | |_| | (__| || (_) | |           */
	/*        \____/\___/|_| |_|___/\__|_|   \__,_|\___|\__\___/|_|           */
	/*                                                                        */
	/* ====================================================================== */

	/* Default */
	Vector();
	explicit Vector(const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0) {}
	
	/* Fill */
	explicit Vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0)
	{
		if (n) assign(n, val);
	}

	/* Range */
	template <class InputIterator>
	Vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0)
	{
		assign(first, last);
	}

	/* Copy */
	Vector(const Vector& x)
	: _allocator(x._allocator), _begin(0), _end(0), _end_capacity(0)
	{
		operator=(x);
	}

 vector& operator= (const vector& x);


	/* ====================================================================== */
	/*                  ___                 _                 _               */
	/*                 /___\__   _____ _ __| | ___   __ _  __| |              */
	/*                //  //\ \ / / _ \ '__| |/ _ \ / _` |/ _` |              */
	/*               / \_//  \ V /  __/ |  | | (_) | (_| | (_| |              */
	/*               \___/    \_/ \___|_|  |_|\___/ \__,_|\__,_|              */
	/*                                                                        */
	/* ====================================================================== */

	Vector& operator=(const Vector& x)
	{
		if (this != &x)
			assign(x.begin(), x.end());
		return (*this);
	}
reference operator[] (size_type n);
const_reference operator[] (size_type n) const;
	/* ====================================================================== */
	/*               ___          _                   _                       */
	/*              /   \___  ___| |_ _ __ _   _  ___| |_ ___  _ __           */
	/*             / /\ / _ \/ __| __| '__| | | |/ __| __/ _ \| '__|          */
	/*            / /_//  __/\__ \ |_| |  | |_| | (__| || (_) | |             */
	/*           /___,' \___||___/\__|_|   \__,_|\___|\__\___/|_|             */
	/*                                                                        */
	/* ====================================================================== */

	virtual ~Vector()
	{
		deallocate();
	}

	/* ====================================================================== */
	/*                                 _   _ _                                */
	/*                           /\ /\| |_(_) |___                            */
	/*                          / / \ \ __| | / __|                           */
	/*                          \ \_/ / |_| | \__ \                           */
	/*                           \___/ \__|_|_|___/                           */
	/*                                                                        */
	/* ====================================================================== */

	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{

	}

	void assign(size_type n, const value_type& val)
	{
		
	}

	reference at(size_type n);
	const_reference at(size_type n) const;

	reference back();
	const_reference back() const;

	iterator begin();
	const_iterator begin() const;
	
	size_type capacity() const;

	const_iterator cbegin() const noexcept;

	const_iterator cend() const noexcept;

	void clear();

	const_reverse_iterator crbegin() const noexcept;
	const_reverse_iterator crend() const noexcept;
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

