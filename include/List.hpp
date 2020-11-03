/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 03:20:17 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/03 09:31:31 by yohlee           ###   ########.fr       */
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
private:
	typedef ft::Node<T> _node;
	typedef typename Alloc::template rebind<Node>::other NodeAlloc;
	NodeAlloc _allocator;
	NodeAlloc _node_allocator;
	Node _base;

public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef bidirectinal_iterator::value_type iterator;
	typedef const bidirectinal_iterator::value_type const_iterator;
	typedef reverse_iterator<iterator> reverse_iterator;
	typedef reverse_iterator<const_iterator> const_reverse_iterator;
	typedef std::ptrdiff_t difference_type;
	typedef std::size_t size_type;

public:

	explicit List(const allocator_type& alloc = allocator_type()) : _allocator(alloc)
	{
		
	}

	explicit List(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
	{
		
	}

	template <class InputIterator>
	List(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
	{

	}

	List(const List& x)
	{

	}

	~List()
	{

	}

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last)
	{

	}
	
	void assign (size_type n, const value_type& val)
	{

	}

	reference back()
	{

	}

	const_reference back() const
	{

	}

	iterator begin()
	{

	}

	const_iterator begin() const
	{

	}

	const_iterator cbegin() const noexcept
	{

	}

	const_iterator cend() const noexcept
	{

	}

	void clear()
	{

	}

	const_reverse_iterator crbegin() const noexcept;
	{

	}

	const_reverse_iterator crend() const noexcept
	{

	}

	template <class... Args>
	iterator emplace (const_iterator position, Args&&... args)
	{

	}

	template <class... Args>
	void emplace_back (Args&&... args)
	{

	}

	template <class... Args>
	void emplace_front (Args&&... args)
	{

	}

	bool empty() const
	{

	}

	iterator end()
	{

	}
	const_iterator end() const
	{

	}

	iterator erase (iterator position)
	{

	}
	iterator erase (iterator first, iterator last)
	{

	}

	reference front()
	{

	}
	const_reference front() const
	{

	}

	allocator_type get_allocator() const
	{

	}

	// single element (1)
	iterator insert (iterator position, const value_type& val)
	{

	}
	// fill (2)
	void insert (iterator position, size_type n, const value_type& val)
	{

	}
	// range (3)
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last)
	{

	}

	size_type max_size() const
	{

	}

	// (1)
	void merge (List& x)
	{

	}
	// (2)
	template <class Compare>
	void merge (List& x, Compare comp)
	{

	}


	// copy (1)
	List& operator= (const List& x)
	{

	}

	void pop_back()
	{

	}

	void pop_front()
	{

	}

	void push_back (const value_type& val)
	{

	}

	void push_front (const value_type& val)
	{

	}

	reverse_iterator rbegin()
	{

	}
	const_reverse_iterator rbegin() const
	{

	}

	void remove (const value_type& val)
	{

	}

	template <class Predicate>
	void remove_if (Predicate pred)
	{

	}

	reverse_iterator rend()
	{

	}
	const_reverse_iterator rend() const
	{

	}

	void resize (size_type n, value_type val = value_type())
	{

	}

	void reverse()
	{

	}

	size_type size() const
	{

	}

	// (1)
	void sort()
	{

	}
	// (2)
	template <class Compare>
	void sort (Compare comp)
	{

	}

	// entire List (1)
	void splice (iterator position, List& x)
	{

	}
	// single element (2)
	void splice (iterator position, List& x, iterator i)
	{

	}
	// element range (3)
	void splice (iterator position, List& x, iterator first, iterator last)
	{

	}

	void swap (List& x)
	{

	}

	// (1)
	void unique()
	{

	}
	// (2)
	template <class BinaryPredicate>
	void unique (BinaryPredicate binary_pred)
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