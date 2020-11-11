/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:16:14 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/11 09:33:49 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "Iterator.hpp"
# include "RedBlackTree.hpp"

namespace ft
{

template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
};

template <class Key>
struct less
{
	bool operator()(const Key& x, const Key& y) const
	{
		return (x < y);
	}
};

template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
class Map
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<const key_type, mapped_type> value_type;
	typedef Compare key_compare;
	// typedef  value_compare
	typedef Alloc allocator_type;
	typedef allocator_type::reference reference;
	typedef allocator_type::const_reference const_reference;	//	for the default allocator: const value_type&
	typedef allocator_type::pointer pointer; //	for the default allocator: value_type*
	typedef allocator_type::const_pointer const_pointer; //	for the default allocator: const value_type*
	typedef ft::bidirectional_iterator iterator;	// a bidirectional iterator to value_type	convertible to const_iterator
	typedef const ft::bidirectional_iterator const_iterator;	// a bidirectional iterator to const value_type	
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef const ft::reverse_iterator<const_iterator> reverse_iterator;
	typedef ft::iterator_traits<iterator>::difference_type difference_type; //	a signed integral type, identical to: iterator_traits<iterator>::difference_type	usually the same as ptrdiff_t
	typedef size_t size_type; //	an unsigned integral type that can represent any non-negative value of difference_type	usually the same as size_t

public:

	Map(/* args*/);
	Map(const Map &);

empty (1)	
explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());
range (2)	
template <class InputIterator>
  map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type());
copy (3)	
map (const map& x);


	Map& operator=(const Map &x);
mapped_type& operator[] (const key_type& k);


	~Map();

mapped_type& at (const key_type& k);
const mapped_type& at (const key_type& k) const;

iterator begin();
const_iterator begin() const;

const_iterator cbegin() const noexcept;

const_iterator cend() const noexcept;

void clear();

size_type count (const key_type& k) const;

const_reverse_iterator crbegin() const noexcept;

const_reverse_iterator crend() const noexcept;

template <class... Args>
  pair<iterator,bool> emplace (Args&&... args);

template <class... Args>
  iterator emplace_hint (const_iterator position, Args&&... args);

bool empty() const;

iterator end();
const_iterator end() const;

pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
pair<iterator,iterator>             equal_range (const key_type& k);

(1)	
     void erase (iterator position);
(2)	
size_type erase (const key_type& k);
(3)	
     void erase (iterator first, iterator last);

iterator find (const key_type& k);
const_iterator find (const key_type& k) const;

allocator_type get_allocator() const;

single element (1)	
pair<iterator,bool> insert (const value_type& val);
with hint (2)	
iterator insert (iterator position, const value_type& val);
range (3)	
template <class InputIterator>
  void insert (InputIterator first, InputIterator last);

key_compare key_comp() const;

iterator lower_bound (const key_type& k);
const_iterator lower_bound (const key_type& k) const;

size_type max_size() const;

reverse_iterator rbegin();
const_reverse_iterator rbegin() const;

reverse_iterator rend();
const_reverse_iterator rend() const;

size_type size() const;

void swap (map& x);

iterator upper_bound (const key_type& k);
const_iterator upper_bound (const key_type& k) const;

value_compare value_comp() const;





};

(1)	
template <class Key, class T, class Compare, class Alloc>
  bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs );
(2)	
template <class Key, class T, class Compare, class Alloc>
  bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs );
(3)	
template <class Key, class T, class Compare, class Alloc>
  bool operator<  ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs );
(4)	
template <class Key, class T, class Compare, class Alloc>
  bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs );
(5)	
template <class Key, class T, class Compare, class Alloc>
  bool operator>  ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs );
(6)	
template <class Key, class T, class Compare, class Alloc>
  bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
                    const map<Key,T,Compare,Alloc>& rhs );

template <class Key, class T, class Compare, class Alloc>
  void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y);

}

#endif