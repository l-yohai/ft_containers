/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:41:33 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/29 08:25:32 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag {};
struct random_access_iterator_tag : bidirectional_iterator_tag {};

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef T			value_type;
	typedef Distance 	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category 	iterator_category;
};

template <class iterator>
class iterator_traits
{
public:
	typedef typename iterator::difference_type		difference_type;
	typedef typename iterator::value_type			value_type;
	typedef typename iterator::pointer				pointer;
	typedef typename iterator::reference			reference;
	typedef typename iterator::iterator_category	iterator_category;
};

template <class T>
class iterator_traits<T*>
{
public:
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
public:
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

template<class T>
class random_access_iterator
{

};

class Iterator
{
public:

};





template <class Iterator>
class reverse_iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, typename ft::iterator_traits<Iterator>::value_type, typename ft::iterator_tarits<Iterator>::difference_type, typename ft::iterator_traits<Iterator>::pointer, typename ft::iterator_traits<Iterator>::reference>
{
private:
	typedef Iterator												iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

public:
	reverse_iterator() {}
	// reverse_iterator(Iterator const& iterator);
	// reverse_iterator(reverse_iterator const& other);
	// reverse_iterator& operator=(reverse_iterator const& other);
	// virtual ~reverse_iterator();

	iterator_type base() const
	{
		iterator_type it(*this);
		return it;
	}

	reference& operator*()
	{
		iterator_type it(*this);
		return *(--it);
	}

	reverse_iterator operator+(difference_type n) const
	{
		reverse_iterator<iterator_type> it(*this);
		return it - n;
	}

	reverse_iterator& operator++()
	{
		this->Iterator::operator--();
		return *this;
	}
	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		++(*this);
		return tmp;
	}

	reverse_iterator& operator+=(difference_type n)
	{
		reverse_iterator<iterator_type> it(*this);
		it -= n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const;

	reverse_iterator& operator--();
	reverse_iterator  operator--(int);

	reverse_iterator& operator-=(difference_type n);

	pointer operator->() const;

	template <class Iter>
	reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it) : it(rev_it.it) {}

	reference operator[](difference_type n) const;
};

}

#endif