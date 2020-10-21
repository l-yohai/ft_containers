/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:41:33 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/21 09:45:04 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <iostream>

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator
{
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
	typedef Category iterator_category;
};

template <class Iterator>
class iterator_traits
{
public:
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<T*>
{
public:
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
public:
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
class random_access_iterator
{

};

class Iterator
{
public:

};

}

#endif