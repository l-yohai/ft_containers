/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 08:58:20 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/19 09:38:55 by yohlee           ###   ########.fr       */
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
	explicit Vector(size_type n, const value_type& val = value_type(),
					const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0)
	{ if (n) assign(n, val); }

	/* Range */
	template <class InputIterator>
	Vector(InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type())
	: _allocator(alloc), _begin(0), _end(0), _end_capacity(0)
	{ assign(first, last); }

	/* Copy */
	Vector(const Vector& x)
	: _allocator(x._allocator), _begin(0), _end(0), _end_capacity(0) { operator=(x); }

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
	/*                          ___     _   _                                 */
	/*                         / _ \___| |_| |_ ___ _ __                      */
	/*                        / /_\/ _ \ __| __/ _ \ '__|                     */
	/*                       / /_\\  __/ |_| ||  __/ |                        */
	/*                       \____/\___|\__|\__\___|_|                        */
	/*                                                                        */
	/* ====================================================================== */

	/* ====================================================================== */
	/*                         __      _   _                                  */
	/*                        / _\ ___| |_| |_ ___ _ __                       */
	/*                        \ \ / _ \ __| __/ _ \ '__|                      */
	/*                        _\ \  __/ |_| ||  __/ |                         */
	/*                        \__/\___|\__|\__\___|_|                         */
	/*                                                                        */
	/* ====================================================================== */

	/* ====================================================================== */
	/*                  __                    _   _                           */
	/*                 /__\_  _____ ___ _ __ | |_(_) ___  _ __                */
	/*                /_\ \ \/ / __/ _ \ '_ \| __| |/ _ \| '_ \               */
	/*               //__  >  < (_|  __/ |_) | |_| | (_) | | | |              */
	/*               \__/ /_/\_\___\___| .__/ \__|_|\___/|_| |_|              */
	/*                                 |_|                                    */
	/* ====================================================================== */

	/* ====================================================================== */
	/*                                 _   _ _                                */
	/*                           /\ /\| |_(_) |___                            */
	/*                          / / \ \ __| | / __|                           */
	/*                          \ \_/ / |_| | \__ \                           */
	/*                           \___/ \__|_|_|___/                           */
	/*                                                                        */
	/* ====================================================================== */


};

}

#endif

