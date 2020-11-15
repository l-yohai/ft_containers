/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:16:14 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/15 18:56:02 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

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

template <class T1, class T2>
pair<T1, T2> make_pair(T1 a, T2 b)
{
	return (pair<T1, T2>(a, b));
}

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
	class value_compare : public std::binary_function<value_type, value_type, bool>
	{
	protected:
		Compare cmp;
		value_compare(Compare c) : cmp(c) {}
	public:
		friend class map;
		
		typedef bool result_type;
		typedef value_type first_type;
		typedef value_type second_type;
		bool operator()(const value_type& x, const value_type& y) const
		{
			return (cmp(x.first, y.first));
		}
	};
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef RedBlackTree<pair<Key, T>, value_compare>::iterator iterator;
	typedef const RedBlackTree<pair<Key, T>, value_compare>::iterator const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef const ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef ft::iterator_traits<iterator>::difference_type difference_type;
	typedef size_t size_type;

private:
	Compare _comp;
	ft::RedBlackTree<ft::pair<Key, T>, value_compare> _tree;

public:
	explicit Map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _tree(value_compare(comp)), _comp(comp) {}

	template <class InputIterator>
	Map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
	: _tree(value_compare(comp)), _comp(comp)
	{
		for (; first != last; fisrt++)
			this->_tree.add(*first);
	}

	Map(const Map& x) : _tree(x._tree), _comp(x._comp)
	{
		*this = x;
	}

	Map& operator=(const Map &x)
	{
		this->_tree = x._tree;
		this->_comp = x._comp;
		return (*this);
	}

	mapped_type& operator[](const key_type& k)
	{
		return ((this->_tree.add(k))->_value.second);
	}

	~Map() {}

	iterator begin()
	{
		return (iterator(this->_tree.min(), &(this->_tree)));
	}

	const_iterator begin() const
	{
		return (const_iterator(this->_tree.min(), &(this->_tree)));
	}

	iterator end()
	{
		return (iterator(0, &(this->_tree)));
	}

	const_iterator end() const
	{
		return (const_iterator(0, &(this->_tree)));
	}

	reverse_iterator rbegin()
	{
		return (reverse_iterator(end()));
	}

	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(end()));
	}

	reverse_iterator rend()
	{
		return (reverse_iterator(begin()));
	}

	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(begin()));
	}

	void clear()
	{
		this->_tree.clear();
	}

	size_type count(const key_type& k) const
	{
		return ((this->_tree.find(k)) ? 1 : 0);
	}

	bool empty() const
	{
		return (!this->_tree.getSize());
	}

	pair<const_iterator,const_iterator> equal_range(const key_type& k) const
	{
		return (ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)));
	}

	pair<iterator,iterator> equal_range(const key_type& k)
	{
		return (ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k)));
	}

	void erase(iterator position)
	{
		this->_tree.deleteKey(position->first);
	}

	size_type erase(const key_type& k)
	{
		return (this->_tree.deleteKey(k));
	}

	void erase(iterator first, iterator last)
	{
		whiel (first != end() && first != last && (last == end() || !comp(last->first, first->first)))
			first = this->_tree.deleteKey(first);
	}

	iterator find(const key_type& k)
	{
		return (iterator(this->_tree.found(k), &(this->_tree)));
	}

	const_iterator find(const key_type& k) const
	{
		return (const_iterator(this->_tree.found(k), &(this->_tree)));
	}

	allocator_type get_allocator() const;

	pair<iterator, bool> insert(const value_type& val)
	{
		iterator tmp(this->_tree.add(val), &(this->_tree));
		return (pair<iterator, bool>(tmp, (tmp->second == val.second)));
	}

	iterator insert(iterator position, const value_type& val)
	{
		return (iterator(this->_tree.add(position, val), &(this->_tree)));
	}

	template <class InputIterator>
	void insert(InputIterator first, InputIterator last)
	{
		while (first != last)
			this->_tree.add(*first++);
	}

	key_compare key_comp() const
	{
		return (this->_comp);
	}

	iterator lower_bound(const key_type& k)
	{
		return (iterator(this->_tree.lower_bound(k), &(this->_tree)));
	}

	const_iterator lower_bound(const key_type& k) const
	{
		return (const_iterator(this->_tree.lower_bound(k), &(this->_tree)));
	}

	size_type max_size() const
	{
		return (this->_tree.getMaxSize());
	}

	size_type size() const
	{
		return (this->_tree.getSize());
	}

	void swap(map& x);

	iterator upper_bound(const key_type& k)
	{
		return (iterator(this->_tree.upper_bound(k), &(this->_tree)));
	}

	const_iterator upper_bound(const key_type& k) const
	{
		return (const_iterator(this->_tree.upper_bound(k), &(this->_tree)));
	}

	value_compare value_comp() const
	{
		return (value_compare(this->_comp));
	}

};


template <class Key, class T, class Compare, class Alloc>
bool operator==(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	if (lhs.size() != rhs.size())
		return (false);
	return (equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Compare, class Alloc>
bool operator!=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	ft::less<ft::pair<Key, T>> less;
	return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), less));
}

template <class Key, class T, class Compare, class Alloc>
bool operator<=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return (!(lhs < rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool operator>(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool operator>=(const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
{
	return (!(rhs > lhs));
}

template <class Key, class T, class Compare, class Alloc>
void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
{
	x.swap(y);
}

}

#endif