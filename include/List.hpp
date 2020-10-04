/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:20:17 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/05 03:41:42 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include "Iterator.hpp"

namespace ft
{

template < class T, class Alloc = std::allocator<T> >
class List
{
	private:
		
	public:
		typedef T value_type;
		
		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		iterator
		const_iterator
		reverse_iterator
		const_reverse_iterator
		typedef std::ptrdiff_t difference_type;
		typedef std::size_t size_type;

		
};

}

#endif