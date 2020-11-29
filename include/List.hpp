/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 13:33:41 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/30 00:30:17 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include "iterator.hpp"
#include "utils.hpp"

namespace ft
{

template <class T, bool flag = false>
class list_iterator;

template <class T>
class ListNode
{
public:
	ListNode* next;
	ListNode* prev;
	T _value;

	ListNode(T value = T()) : next(0), prev(0), _value(value) {}
	ListNode(ListNode* next, ListNode* prev, T value) : next(next), prev(prev), _value(value) {}
	ListNode(ListNode const& cpy) : next(cpy.next), prev(cpy.prev), _value(cpy.value) {}
};

template <class T, class Alloc = std::allocator<T> >
class list
{
private:
	template <class U, bool flag>
	friend class list_iterator;

	typedef ft::ListNode<T> Node;
	Node* _start;
	Node* _last;
	size_t _size;

public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef list_iterator<T> iterator;
	typedef list_iterator<T, true> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef size_t size_type;
	typedef typename iterator_traits<iterator>::difference_type difference_type;

public:
	explicit list(const allocator_type&  = allocator_type()) : _start(0), _last(0), _size(0) {}

	explicit list(size_t n, const T& val = T(), const allocator_type& = allocator_type())
	: _start(0), _last(0), _size(n)
	{
		if (n)
		{
			_start = new Node(0, 0, val);
			Node* tmp;
			Node* prev = _start;
			while (--n)
			{
				tmp = new Node(0, prev, val);
				prev->next = tmp;
				prev = tmp;
			}
			_last = prev;
		}
	}

	template <class InputIterator>
	list(InputIterator start, InputIterator last, const allocator_type& = allocator_type(), typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
	: _start(0), _last(0), _size(0)
	{
		if (start != last)
		{
			_size = 1;
			_start = new Node(0, 0, *start);
			Node* tmp;
			Node* prev = _start;
			for (start = ++start; start != last; start++)
			{
				tmp = new Node(0, prev, *start);
				prev->next = tmp;
				prev = tmp;
				_size++;
			}
			_last = prev;
		}
	}

	list(const list& x) : _start(0), _last(0), _size(x._size)
	{
		if (_size)
		{
			_start = new Node(0, 0, x._start->_value);
			Node* tmp;
			Node* prev = _start;
			Node* ctrav = x._start->next;
			while (ctrav)
			{
				tmp = new Node(0, prev, ctrav->_value);
				prev->next = tmp;
				prev = tmp;
				ctrav = ctrav->next;
			}
			_last = prev;
		}
	}

	list& operator=(const list& x)
	{
		list tmp(x);
		swap(tmp);
		return (*this);
	}

	~list()
	{
		Node* prev;
		while (_start && _size)
		{
			prev = _start;
			_start = _start->next;
			delete prev;
		}
		_start = _last = 0;
		_size = 0;
	}

	size_type size() const
	{
		return (_size);
	}

	size_type max_size() const 
	{
		return (std::numeric_limits<difference_type>::max() / (sizeof(Node) / 2));
	}

	bool empty() const
	{
		return (!_size);
	}

	void resize(size_type n, value_type val = value_type())
	{
		Node* trav;

		if (!n)
			clear();
		else if (empty())
		{
			list tmp(n, val);
			swap(tmp);
		}
		else if (n < _size)
		{
			trav = _start;
			while (n-- > 0)
				trav = trav->next;
			erase(iterator(trav), iterator(0));
		}
		else if (n > _size)
		{
			insert(iterator(0), n - _size, val);
		}
	}

	void swap(list& x)
	{
		char buf[sizeof(list)];

		memcpy(buf, &x, sizeof(list));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(list));
		memcpy(reinterpret_cast<char *>(this), buf, sizeof(list));
	}

	reference front()
	{
		return (_start->_value);
	}

	const_reference front() const
	{
		return (_start->_value);
	}

	reference back()
	{
		return (_last->_value);
	}

	const_reference back() const
	{
		return (_last->_value);
	}

	iterator begin()
	{
		return (iterator(_start, this));
	}

	const_iterator begin() const
	{
		return (const_iterator(_start, this));
	}

	iterator end()
	{
		return (iterator(0, this));
	}

	const_iterator end() const
	{
		return (const_iterator(0, this));
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

	template <class InputIterator>
	void assign(InputIterator start, InputIterator last)
	{
		list tmp(start, last);
		swap(tmp);
	}

	void assign(size_t n, const value_type& val)
	{
		list tmp(n, val);
		swap(tmp);
	}

	iterator insert(iterator position, const value_type& val)
	{
		Node* tmp;
		if (empty())
		{
			tmp = new Node(0, 0, val);
			_start = _last = tmp;
		}
		else if (position._node == _start)
		{
			tmp = new Node(_start, 0, val);
			_start->prev = tmp;
			_start = tmp;
		}
		else if (!position._node)
		{
			tmp = new Node(0, _last, val);
			_last->next = tmp;
			_last = tmp;
		}
		else
		{
			tmp = new Node(position._node, position._node->prev, val);
			position._node->prev->next = tmp;
			position._node->prev = tmp;
		}
		_size++;
		position._node = tmp;
		return (position);
	}

	void insert(iterator position, size_type n, const value_type& val)
	{
		for (size_type i = 0; i < n; ++i)
		{
			position = insert(position, val);
			++position;
		}
	}

	template <class InputIterator>
	void insert(iterator position, InputIterator start, InputIterator last,
				typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
	{
		while (start != last)
		{
			position = insert(position, *start++);
			++position;
		}
	}

	iterator erase(iterator position)
	{
		if (position._node == 0)
			return (position);
		iterator ret(position);
		ret++;
		disconnect(position._node);
		delete position._node;
		return (ret);
	}

	iterator erase(iterator start, iterator last)
	{
		if (start == last)
			return (start);
		Node* toDel;
		disconnect(start._node, last._node);
		while (start._node != 0 && start != last)
		{
			toDel = start._node;
			start++;
			delete toDel;
		}
		return (last);
	}

	void push_back(const value_type& val)
	{
		_last = new Node(0, _last, val);
		_size++;
		if (_last->prev)
			_last->prev->next = _last;
		else
			_start = _last;
	}

	void pop_back()
	{
		Node* toDel = _last;
		disconnect(_last);
		delete toDel;
	}

	void push_front(const value_type& val)
	{
		_start = new Node(_start, 0, val);
		_size++;
		if (_start->next)
			_start->next->prev = _start;
		else
			_last = _start;
	}

	void pop_front()
	{
		Node* toDel = _start;
		disconnect(_start);
		delete toDel;
	}

	void clear()
	{
		Node* prev;
		while (_start)
		{
			prev = _start;
			_start = _start->next;
			delete prev;
		}
		_start = _last = 0;
		_size = 0;
	}

	void splice(iterator position, list& x)
	{
		if (x.empty() || &x == this)
			return ;
		if (empty())
		{
			swap(x);
			return ;
		}
		if (position._node == _start)
		{
			_start->prev = x._last;
			x._last->next = _start;
			_start = x._start;
		}
		else if (position._node == 0)
		{
			_last->next = x._start;
			x._start->prev = _last;
			_last = x._last;
		}
		else
		{
			position._node->prev->next = x._start;
			x._start->prev = position._node->prev;
			position._node->prev = x._last;
			x._last->next = position._node;
		}
		_size += x._size;
		x._start = x._last = 0;
		x._size = 0;
	}

	void splice(iterator position, list& x, iterator i)
	{
		x.disconnect(i._node);

		if (empty())
		{
			_start = _last = i._node;
		}
		else if (position._node == _start)
		{
			_start->prev = i._node;
			i._node->next = _start;
			_start = i._node;
		}
		else if (position._node == 0)
		{
			_last->next = i._node;
			i._node->prev = _last;
			_last = i._node;
		}
		else
		{
			i._node->next = position._node;
			i._node->prev = position._node->prev;
			i._node->prev->next = i._node;
			i._node->next->prev = i._node;
		}
		_size++;
	}

	void splice(iterator position, list& x, iterator start, iterator last)
	{
		if (!x._start || start == last)
			return;
		Node* nlast = (last._node) ? last._node->prev : x._last;
		_size += x.disconnect(start._node, last._node);
		if (empty())
		{
			_start = start._node;
			_last = nlast;
		}
		else if (position._node == _start)
		{
			_start->prev = nlast;
			nlast->next = _start;
			_start = start._node;
		}
		else if (position._node == 0)
		{
			_last->next = start._node;
			start._node->prev = _last;
			_last = nlast;
		}
		else
		{
			position._node->prev->next = start._node;
			start._node->prev = position._node->prev;
			position._node->prev = nlast;
			nlast->next = position._node;
		}
	}

	void remove(const value_type& val)
	{
		iterator it(_start);
		while (it._node != 0)
		{
			if (*it == val)
				it = erase(it);
			else
				it++;
		}
	}

	template <class Predicate>
	void remove_if(Predicate pred)
	{
		iterator it(_start);
		while (it._node != 0)
		{
			if (pred(*it))
				it = erase(it);
			else
				it++;
		}
	}

	void unique()
	{
		iterator it = begin();
		value_type prev = *it++;
		while (it != end())
		{
			if (*it == prev)
				it = erase(it);
			else
				prev = *it++;
		}
	}

	template <class BinaryPredicate>
	void unique(BinaryPredicate binary_pred)
	{
		iterator it = begin();
		value_type prev = *it++;
		while (it != end())
		{
			if (binary_pred(prev, *it))
				it = erase(it);
			else
				prev = *it++;
		}
	}

	void merge(list& x)
	{
		iterator a(_start, this);
		iterator b(x._start, &x);
		if (this == &x || x.empty())
			return;
		if (empty())
		{
			swap(x);
			return;
		}
		while (a._node != 0 && b._node != 0)
		{
			if (*b < *a)
				splice(a, x, b++);
			else
				a++;
		}
		if (!x.empty())
			splice(a, x, b, x.end());
	}

	template <class Compare>
	void merge(list& x, Compare comp)
	{
		iterator a(_start, this);
		iterator b(x._start, &x);
		if (this == &x || x.empty())
			return;
		if (empty())
		{
			swap(x);
			return;
		}
		while (a._node != 0 && b._node != 0)
		{
			if (comp(*b, *a) > 0)
				splice(a, x, b++);
			else
				a++;
		}
		if (!x.empty())
			splice(a, x, b, x.end());
	}

	void sort()
	{
		if (_size < 2)
			return;
		mergesort(&_start, ft::less<value_type>());
		Node* trav;
		for (trav = _last; trav && trav->next; trav = trav->next)
			;
		_last = trav;
	}

	template <class Compare>
	void sort(Compare comp)
	{
		if (_size < 2)
			return;
		mergesort(&_start, comp);
		Node* trav;
		for (trav = _last; trav && trav->next; trav = trav->next)
			;
		_last = trav;
	}

	void reverse()
	{
		iterator front(_start);
		iterator back(_last);
		while (front != back)
		{
			std::swap(*front, *back);
			front++;
			if (front == back)
				break;
			back--;
		}
	}

private:
	void disconnect(Node* position)
	{
		if (!position)
			return;
		_size--;
		if (_size < 1)
		{
			_start = _last = 0;
		}
		else if (position == _start)
		{
			_start = _start->next;
			_start->prev = 0;
		}
		else if (position == _last)
		{
			_last = _last->prev;
			_last->next = 0;
		}
		else
		{
			position->prev->next = position->next;
			position->next->prev = position->prev;
		}
		position->prev = position->next = 0;
	}

	size_t disconnect(Node* start, Node* last)
	{
		size_t range_size = 0;
		for (Node* trav = start; trav != last; trav = trav->next)
			range_size++;
		if (range_size == _size || (start == _start && last == 0))
		{
			_start = _last = 0;
		}
		else if (start == _start)
		{
			_start = last;
			last->prev->next = 0;
			_start->prev = 0;
		}
		else if (last == 0)
		{
			_last = start->prev;
			_last->next = 0;
		}
		else
		{
			start->prev->next = last;
			last->prev->next = 0;
			last->prev = start->prev;
		}
		start->prev = 0;
		_size -= range_size;
		return (range_size);
	}

	Node* split_list(Node* start)
	{
		if (start->next != 0)
		{
			for (Node* fast = start; fast != 0; fast = fast->next)
			{
				if (fast && fast->next)
				{
					fast = fast->next;
					start = start->next;
				}
			}
		}
		if (start->prev)
			start->prev->next = 0;
		return (start);
	}

	template <typename Comp>
	Node* sort_merge(Node* a, Node* c, Comp comp)
	{
		if (!a)
		{
			_last = c;
			return (c);
		}
		if (!c)
		{
			_last = a;
			return (a);
		}
		if (comp(a->_value, c->_value))
		{
			a->next = sort_merge(a->next, c, comp);
			a->next->prev = a;
			a->prev = 0;
			return (a);
		}
		else
		{
			c->next = sort_merge(a, c->next, comp);
			c->next->prev = c;
			c->prev = 0;
			return (c);
		}
	}

	template <typename Comp>
	void mergesort(Node* *start, Comp comp)
	{
		if (!*start || !(*start)->next)
			return ;
		Node* middle = split_list(*start);
		mergesort(start, comp);
		mergesort(&middle, comp);
		*start = sort_merge(*start, middle, comp);
	}
};

template <class T, bool flag>
class list_iterator
{
	friend class list<T>;
	friend class list_iterator<T, true>;
	friend class list_iterator<T, false>;

	typedef typename is_const<flag, const ListNode<T>, ListNode<T> >::type Node;
	typedef typename is_const<flag, const list<T> * , list<T> *>::type Ctnr;

	Node* _node;
	Ctnr _ctnr;

public:
	typedef ft::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef typename is_const<flag, const T&, T&>::type reference;
	typedef typename is_const<flag, const T*, T*>::type pointer;

	list_iterator(Node* node = 0) : _node(node), _ctnr(0) {}

	list_iterator(Node* node, Ctnr container) : _node(node), _ctnr(container) {}

	list_iterator(list_iterator<T, flag> const &cpy) : _node(cpy._node), _ctnr(cpy._ctnr) {}

	list_iterator &operator=(list_iterator const &cpy)
	{
		list_iterator tmp(cpy);
		swap(tmp);
		return (*this);
	}

	~list_iterator() {}

	list_iterator &operator++(void)
	{
		if (_node)
			_node = _node->next;
		else if (_ctnr)
			_node = _ctnr->_start;
		return (*this);
	}

	list_iterator operator++(int)
	{
		list_iterator old(*this);
		if (_node)
			_node = _node->next;
		else if (_ctnr)
			_node = _ctnr->_start;
		return (old);
	}

	list_iterator &operator--(void)
	{
		if (_node)
			_node = _node->prev;
		else if (_ctnr)
			_node = _ctnr->_last;
		return (*this);
	}

	list_iterator operator--(int)
	{
		list_iterator old(*this);
		if (_node)
			_node = _node->prev;
		else if (_ctnr)
			_node = _ctnr->_last;
		return (old);
	}

	reference operator*(void) const
	{
		return (_node->_value);
	}

	pointer operator->(void) const
	{
		return (&(_node->_value));
	}

	friend bool operator==(const list_iterator& lhs, const list_iterator& rhs)
	{
		return (lhs._node == rhs._node);
	}

	friend bool operator!=(const list_iterator& lhs, const list_iterator& rhs)
	{
		return (lhs._node != rhs._node);
	}

	void swap(list_iterator& x)
	{
		char buf[sizeof(list_iterator)];
		memcpy(buf, &x, sizeof(list_iterator));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(list_iterator));
		memcpy(reinterpret_cast<char *>(this), buf, sizeof(list_iterator));
	}

};

template <class T, class Alloc>
bool operator==(const ft::list<T, Alloc>& lhs, const ft::list<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	return (equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!=(const ft::list<T, Alloc>& lhs, const ft::list<T, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<(const ft::list<T, Alloc>& lhs, const ft::list<T, Alloc>& rhs)
{
	ft::less<T> less;
	return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), less));
}

template <class T, class Alloc>
bool operator<=(const ft::list<T, Alloc>& lhs, const ft::list<T, Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>(const ft::list<T, Alloc>& lhs, const ft::list<T, Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>=(const ft::list<T, Alloc>& lhs, const ft::list<T, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

template <class T, class Alloc>
void swap(ft::list<T, Alloc> &a, ft::list<T, Alloc> &b)
{
	a.swap(b);
}

}

#endif
