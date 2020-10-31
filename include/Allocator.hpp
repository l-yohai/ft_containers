/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Allocator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 09:15:17 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/31 15:32:42 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

# include <iostream>

namespace ft
{

template <class T>
class Allocator
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef std::ptrdiff_t difference_type;
	template <class U>
	struct rebind { typedef Allocator<U> other; };
	Allocator() throw() {};
	Allocator(const Allocator& alloc) throw() {};
	template <class U>
	Allocator(const Allocator<U>& alloc) throw() {};
	~Allocator() throw() {};
	pointer address(reference x) const { return &x; }
	const_pointer address(const_reference x) const { return &x; }
	pointer allocate(size_type n, Allocator<void>::const_pointer hint=0) {
		pointer ret = (pointer)(operator new(n * sizeof(T)));
		return ret;
	}
	void deallocate(pointer p, size_type n) {
		(void)n;
		operator delete((void *)p);
	}
	size_type max_size() const throw() { return std::numeric_limits<size_t>::max() / sizeof(T); }
	void construct(pointer p, const_reference val) { new ((void *)p T(value)); }
	void destroy(pointer p) { p->~T(); }
};

}

#endif