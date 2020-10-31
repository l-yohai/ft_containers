/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:32:47 by yohlee            #+#    #+#             */
/*   Updated: 2020/10/31 18:02:47 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag {};
struct bidirectional_iterator_tag {};
struct random_access_iterator_tag {};

template <class iterator>
class iterator_traits
{
public:
	typedef typename iterator::difference_type		difference_type;
	typedef typename iterator::value_type			value_type;
	typedef typename iterator::pointer				pointer;
	typedef typename iterator::reference			reference;
	typedef typename iterator::iterator_category	iterator_category;
};

template <class T>
class iterator_traits<T*>
{
public:
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <class T>
class iterator_traits<const T*>
{
public:
	typedef ptrdiff_t					difference_type;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};

template <class iterator>
class reverse_iterator
{
private:
	iterator _it;

public:
	typedef iterator												iterator_type;
	typedef typename iterator_traits<iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<iterator>::value_type			value_type;
	typedef typename iterator_traits<iterator>::difference_type		difference_type;
	typedef typename iterator_traits<iterator>::pointer				pointer;
	typedef typename iterator_traits<iterator>::reference			reference;

public:

	reverse_iterator() : _it() {}
	explicit reverse_iterator(iterator_type it) : _it(it) {}

	reverse_iterator(const reverse_iterator<iterator>& rev_it) : _it(rev_it._it)
	{
		*this = rev_it;
	}

	reverse_iterator& operator=(const reverse_iterator<iterator>& rev_it)
	{
		this->_it = rev_it._it;
		return *this;
	}

	iterator_type base() const
	{
		return (this->_it);
	}

	reference operator*() const
	{
		iterator_type it(*this);
		return *(--it);
	}

	reverse_iterator operator+(difference_type n) const
	{
		return (this->_it - n);
	}

	reverse_iterator& operator++()
	{
		--(this->_it);
		return (*this);
	}
	reverse_iterator operator++(int)
	{
		reverse_iterator tmp = *this;
		--(*this);
		return (tmp);
	}

	reverse_iterator& operator+=(difference_type n)
	{
		reverse_iterator<iterator_type> it(*this);
		it -= n;
		return (*this);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return (this->_it + n);
	}

	reverse_iterator& operator--()
	{
		++(this->_it);
		return (*this);
	}

	reverse_iterator  operator--(int)
	{
		reverse_iterator tmp = *this;
		++(*this);
		return (tmp);
	}

	reverse_iterator& operator-=(difference_type n)
	{
		reverse_iterator<iterator_type> it(*this);
		it += n;
		return (*this);
	}

	pointer operator->() const
	{
		return (&(operator*()));
	}

	reference operator[](difference_type n) const
	{
		return (this->base()[-n - 1]);
	}
};

template <class Iterator>
bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
bool operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

// template <class Iterator>
// typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
// {
// 	return (lhs.base() - rhs.base());
// }


// template <class Iterator>
// reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
// {
// 	return (lhs.base() == rhs.base());
// }

}

#endif
