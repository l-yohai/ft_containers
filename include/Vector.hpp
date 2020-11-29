/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 08:58:20 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/29 23:49:37 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "utils.hpp"

namespace ft
{

template <class T, bool flag = false>
class vector_iterator;

template <class T, class Alloc = std::allocator<T> >
class vector
{
private:
	T* _array;
	size_t _size;
	size_t _capacity;

	vector(const vector& x, size_t capacity) : _array(capacity ? new T[capacity] : nullptr), _capacity(capacity)
	{
		size_type i = 0;
		while (i < this->_capacity && i < x._size)
		{
			this->_array[i] = x._array[i];
			i++;
		}
		this->_size = i;
	}

public:
	typedef T value_type;
	typedef Alloc allocator_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef vector_iterator<T> iterator;
	typedef vector_iterator<T, true> const_iterator;
	typedef ft::reverse_iterator<iterator> reverse_iterator;
	typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef size_t size_type;
	typedef typename iterator_traits<iterator>::difference_type difference_type;

public:
	explicit vector(const allocator_type & = allocator_type()) : _array(0),
																 _size(0),
																 _capacity(0)
	{
	}
	explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type & = allocator_type()) : _array(new T[n]),
																 _size(n),
																 _capacity(n)
	{
		for (size_type i = 0; i < n; i++)
			_array[i] = val;
	}
	template <class InputIterator>
	vector(InputIterator first, InputIterator last,
		   const allocator_type & = allocator_type(),
		   typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0) : _array(0),
																						   _size(0),
																						   _capacity(0)
	{
		while (first != last)
			push_back(*first++);
	}
	vector(const vector &x) : _array(new T[x._capacity]),
							  _size(x._size),
							  _capacity(x._capacity)
	{
		for (size_type i = 0; i < _size; i++)
			_array[i] = x._array[i];
	}
	~vector()
	{
		delete[] _array;
	}
	vector &operator=(const vector &x)
	{
		vector ret(x);
		swap(ret);
		return *this;
	}
	iterator begin() { return _array; }
	const_iterator begin() const { return _array; }
	iterator end() { return &_array[_size]; }
	const_iterator end() const { return &_array[_size]; }
	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
	size_type size() const { return _size; }
	size_type max_size() const
	{
		return std::numeric_limits<difference_type>::max() / ((sizeof(T) / 2) < 1 ? 1 : (sizeof(T) / 2));
	}
	void resize(size_type n, value_type val = value_type())
	{
		if (n > max_size())
			throw std::length_error("max_size(size_t n) 'n' exceeds maximum supported size");
		vector tmp(*this, n);
		swap(tmp);
		for (size_type i = _size; i < _capacity; ++i)
			_array[i] = val;
		_size = n;
	}
	size_type capacity() const { return _capacity; }
	bool empty() const { return !_size; }
	void reserve(size_type n)
	{
		if (n > _capacity)
		{
			if (n > max_size())
				throw std::length_error("reserve(size_t n) 'n' exceeds maximum supported size");
			vector tmp(*this, n);
			swap(tmp);
		}
	}
	reference operator[](size_type n) { return _array[n]; }
	const_reference operator[](size_type n) const { return _array[n]; }
	reference at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector");
		return _array[n];
	}
	const_reference at(size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("vector");
		return _array[n];
	}
	reference front() { return _array[0]; }
	const_reference front() const { return _array[0]; }
	reference back() { return _array[_size - 1]; }
	const_reference back() const { return _array[_size - 1]; }
	template <class InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		vector tmp(first, last);
		swap(tmp);
	}
	void assign(size_type n, const value_type &val)
	{
		vector tmp(n, val);
		swap(tmp);
	}
	void push_back(const value_type &val)
	{
		if (_size >= _capacity)
		{
			vector tmp(*this, !_capacity ? 1 : _capacity * 2);
			swap(tmp);
		}
		_array[_size++] = val;
	}
	void pop_back()
	{
		if (_size > 0)
			_size--;
	}
	iterator insert(iterator position, const value_type &val)
	{
		size_type n = position - _array;
		insert(position, 1, val);
		return _array + n;
	}
	void insert(iterator position, size_type n, const value_type &val)
	{
		if (_size + n >= _capacity)
		{
			vector tmp(*this, _capacity + n);
			position = tmp._array + (position - _array);
			swap(tmp);
		}
		for (iterator back = &_array[_size - 1]; back >= position; --back)
			back[n] = *back;
		for (size_type i = 0; i < n; i++)
			*position++ = val;
		_size += n;
	}
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,
				typename std::enable_if<!std::is_integral<InputIterator>::value>::type * = 0)
	{
		while (first != last)
			position = insert(position, *first++) + 1;
	}
	iterator erase(iterator position)
	{
		for (iterator it = position; it + 1 < end(); ++it)
			*it = *(it + 1);
		if (_size)
			_size--;
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		size_type dif = last - first;
		for (iterator it = first; last < end(); ++last)
			*it++ = *last;
		_size -= dif;
		return first;
	}
	void swap(vector &x)
	{
		char buffer[sizeof(vector)];
		memcpy(buffer, reinterpret_cast<char *>(&x), sizeof(vector));
		memcpy(reinterpret_cast<char *>(&x), this, sizeof(vector));
		memcpy(reinterpret_cast<char *>(this), buffer, sizeof(vector));
	}
	void clear()
	{
		vector tmp;
		swap(tmp);
	}
};

template <class T, bool flag>
class vector_iterator
{
private:
	friend class vector_iterator<T, false>;
	friend class vector_iterator<T, true>;

public:
	typedef ft::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef typename ft::is_const<flag, const T &, T &>::type reference;
	typedef typename ft::is_const<flag, const T *, T *>::type pointer;
	typedef std::ptrdiff_t difference_type;

protected:
	pointer _ptr;

public:
	vector_iterator() : _ptr(nullptr) {}
	vector_iterator(pointer ptr) : _ptr(ptr) {}
	vector_iterator(vector_iterator<T, false> const &x) : _ptr(x._ptr) {}
	virtual ~vector_iterator() {}

	vector_iterator &operator=(vector_iterator<T, false> const &x)
	{
		_ptr = x._ptr;
		return *this;
	}
	reference operator*() const
	{
		return *_ptr;
	}
	pointer operator->() const
	{
		return _ptr;
	}
	reference operator[](int val) const
	{
		return _ptr[val];
		// return *(p + val);
	}
	vector_iterator operator++(int)
	{
		vector_iterator tmp(*this);
		++_ptr;
		return tmp;
	}
	vector_iterator &operator++()
	{
		++_ptr;
		return *this;
	}
	vector_iterator operator--(int)
	{
		vector_iterator tmp(*this);
		--_ptr;
		return tmp;
	}
	vector_iterator &operator--()
	{
		--_ptr;
		return *this;
	}
	vector_iterator &operator+=(int value)
	{
		_ptr += value;
		return *this;
	}
	vector_iterator operator+(int value) const
	{
		vector_iterator tmp(*this);
		return tmp += value;
	}
	vector_iterator &operator-=(int value)
	{
		_ptr -= value;
		return *this;
	}
	vector_iterator operator-(int value) const
	{
		vector_iterator tmp(*this);
		return tmp -= value;
	}
	difference_type operator-(vector_iterator const &x) const
	{
		return _ptr - x._ptr;
	}
	friend vector_iterator operator+(difference_type value, const vector_iterator &x)
	{
		vector_iterator tmp(x);
		return tmp += value;
	}
	friend bool operator==(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs._ptr == rhs._ptr;
	}
	friend bool operator!=(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs._ptr != rhs._ptr;
	}
	friend bool operator<(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs._ptr < rhs._ptr;
	}
	friend bool operator<=(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs._ptr <= rhs._ptr;
	}
	friend bool operator>(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs._ptr > rhs._ptr;
	}
	friend bool operator>=(const vector_iterator &lhs, const vector_iterator &rhs)
	{
		return lhs._ptr >= rhs._ptr;
	}

};

template <class T>
bool operator==(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	return equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <class T>
bool operator!=(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return !(lhs == rhs);
}
template <class T>
bool operator<(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	std::less<T> less;
	return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), less);
}
template <class T>
bool operator<=(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return !(rhs < lhs);
}
template <class T>
bool operator>(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return rhs < lhs;
}
template <class T>
bool operator>=(const ft::vector<T> &lhs, const ft::vector<T> &rhs)
{
	return !(lhs < rhs);
}

template <class T>
void swap(ft::vector<T> &a, ft::vector<T> &b)
{
	a.swap(b);
}

}

#endif

