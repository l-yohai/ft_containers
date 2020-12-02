/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:32:47 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/30 00:06:03 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

# include <cstddef>

namespace ft
{

template <bool flag, class CONST, class NORMAL>
class is_const;

template <class CONST, class NORMAL>
class is_const<true, CONST, NORMAL>
{
public:
	typedef CONST type;
};

template <class CONST, class NORMAL>
class is_const<false, CONST, NORMAL>
{
public:
	typedef NORMAL type;
};

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag : public input_iterator_tag {};

struct bidirectional_iterator_tag : public forward_iterator_tag {};

struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::difference_type difference_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
	typedef typename Iterator::iterator_category iterator_category;
};

template <class T>
struct iterator_traits<T *>
{
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class T>
struct iterator_traits<const T *>
{
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef random_access_iterator_tag iterator_category;
};

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n, ft::input_iterator_tag)
{
	for (; n > 0; --n)
		++i;
}

template <class BidirectionalIterator, class Distance>
void advance(BidirectionalIterator& i, Distance n, ft::bidirectional_iterator_tag)
{
	if (n >= 0)
	{
		for (; n > 0; --n)
			++i;
	}
	else
	{
		for (; n < 0; ++n)
			--i;
	}
}

template <class RandomAccessIterator, class Distance>
void advance(RandomAccessIterator& i, Distance n, ft::random_access_iterator_tag)
{
	i += n;
}

template <class InputIterator, class Distance>
void advance(InputIterator& i, Distance n)
{
	advance(i, n, typename iterator_traits<InputIterator>::iterator_category());
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last, ft::input_iterator_tag)
{
	typename ft::iterator_traits<InputIterator>::difference_type n = 0;

	for (; first != last; first++)
		n++;

	return (n);
}

template <class RandomAccessIterator>
typename ft::iterator_traits<RandomAccessIterator>::difference_type distance(RandomAccessIterator first, RandomAccessIterator last, ft::random_access_iterator_tag)
{
	return (last - first);
}

template <class InputIterator>
typename ft::iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
{
	return (distance(first, last, typename iterator_traits<InputIterator>::iterator_category()));
}

template <class Iterator>
class reverse_iterator
{
private:
	Iterator _it;

	template <class Iterator2>
	friend class reverse_iterator;

public:
	typedef Iterator iterator_type;
	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
	typedef typename iterator_traits<Iterator>::value_type value_type;
	typedef typename iterator_traits<Iterator>::difference_type difference_type;
	typedef typename iterator_traits<Iterator>::pointer pointer;
	typedef typename iterator_traits<Iterator>::reference reference;

	reverse_iterator() {}

	explicit reverse_iterator(iterator_type it) : _it(--it) {}

	template <class Iter>
	reverse_iterator(const reverse_iterator<Iter>& rev_it) : _it(--rev_it.base()) {}

	template <class Iter>
	reverse_iterator& operator=(const reverse_iterator<Iter>& rev_it)
	{
		_it = rev_it._it;
		return (*this);
	}

	iterator_type base() const
	{
		Iterator ret(_it);

		return (ret);
	}

	reference operator*() const
	{
		return (*_it);
	}

	pointer operator->() const
	{
		return (&(operator*()));
	}
	
	reference operator[](difference_type n) const
	{
		return (_it[-1 - n]);
	}

	reverse_iterator operator+(difference_type n) const
	{
		reverse_iterator tmp(*this);

		tmp._it = tmp._it - n;
		return (tmp);
	}

	reverse_iterator& operator+=(difference_type n)
	{
		_it = _it - n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const
	{
		reverse_iterator tmp(*this);
		tmp._it = tmp._it + n;
		return (tmp);
	}

	reverse_iterator& operator-=(difference_type n)
	{
		_it = _it + n;
		return (*this);
	}

	reverse_iterator& operator++()
	{
		--_it;
		return (*this);
	}

	reverse_iterator operator++(int)
	{
		reverse_iterator tmp(*this);

		--_it;
		return (tmp);
	}

	reverse_iterator& operator--()
	{
		++_it;
		return (*this);
	}

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp(*this);

		++_it;
		return (tmp);
	}

	template <class it>
	friend bool operator==(const reverse_iterator& lhs, const reverse_iterator<it>& rhs)
	{
		return (lhs._it == rhs._it);
	}

	template <class it>
	friend bool operator!=(const reverse_iterator& lhs, const reverse_iterator<it>& rhs)
	{
		return (lhs._it != rhs._it);
	}

	template <class it>
	friend bool operator<(const reverse_iterator& lhs, const reverse_iterator<it>& rhs)
	{
		return (lhs._it > rhs._it);
	}

	template <class it>
	friend bool operator<=(const reverse_iterator& lhs, const reverse_iterator<it>& rhs)
	{
		return (lhs._it >= rhs._it);
	}

	template <class it>
	friend bool operator>(const reverse_iterator& lhs, const reverse_iterator<it>& rhs)
	{
		return (lhs._it < rhs._it);
	}

	template <class it>
	friend bool operator>=(const reverse_iterator& lhs, const reverse_iterator<it>& rhs)
	{
		return (lhs._it <= rhs._it);
	}

};

template <class Iterator>
ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it)
{
	return (ft::reverse_iterator<Iterator>(rev_it + n));
}

template <class Iterator>
ft::reverse_iterator<Iterator> operator-(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it)
{
	return (ft::reverse_iterator<Iterator>(rev_it - n));
}

}

#endif
