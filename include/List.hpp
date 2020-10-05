/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:20:17 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/05 10:21:08 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

#include "Allocator.hpp"

# include "Iterator.hpp"

namespace ft
{

template < class T, class Alloc >
class List
{
	public:
		typedef T value_type;
		typedef const T value_type;
		typedef Alloc allocator_type;
		typedef T& reference;
		typedef const T& const_reference;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

	protected:
		typedef ft::lst_node<T> Node;

};

}

#endif