/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 15:32:47 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/08 12:24:52 by yohlee           ###   ########.fr       */
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

template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
class iterator
{
public:
	typedef Category iterator_category;
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer pointer;
	typedef Reference reference;
};

template <class Iterator>
Iterator next(Iterator it, unsigned long n = 1)
{
	while (n--)
		++it;
	return (it);
}

template <class Iterator>
class iterator_traits
{
public:
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
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

template<class Iterator>
typename iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last, typename ft::iterator_traits<Iterator>::iterator_category() = ft::random_access_iterator_tag())
{
	return (last - first);
}

template <class Iterator>
class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, Iterator>
{
private:
	Iterator _it;

public:
	typedef Iterator													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;

public:
	random_access_iterator() : _it() {}
	explicit random_access_iterator(const Iterator& it) : _it(it) {}

	random_access_iterator(const random_access_iterator<Iterator>& it) : _it(it._it)
	{
		*this = it;
	}

	random_access_iterator& operator=(const random_access_iterator<Iterator>& it)
	{
		this->_it = it._it;
		return (*this);
	}

	~random_access_iterator() {}

	iterator_type base() const
	{
		return (this->_it);
	}

	reference operator*() const
	{
		iterator_type it = this->_it;
		return (*(--it));
	}

	random_access_iterator operator+(difference_type n) const
	{
		return (this->_it + n);
	}

	random_access_iterator& operator++()
	{
		++(this->_it);
		return (*this);
	}

	random_access_iterator operator++(int)
	{
		random_access_iterator tmp = *this;
		++(*this);
		return (tmp);
	}

	random_access_iterator& operator+=(difference_type n)
	{
		random_access_iterator<iterator_type> it(*this);
		it += n;
		return (*this);
	}

	random_access_iterator operator-(difference_type n) const
	{
		return (this->_it - n);
	}

	random_access_iterator& operator--()
	{
		--(this->_it);
		return (*this);
	}

	random_access_iterator operator--(int)
	{
		random_access_iterator tmp = *this;
		--(this->_it);
		return (tmp);
	}

	random_access_iterator& operator-=(difference_type n)
	{
		this->_it -= n;
		return (*this);
	}

	pointer operator->() const
	{
		return (this->_it);
	}

	reference operator[](difference_type n) const
	{
		return (*(this->_it + n));
	}
};

template <class Iterator>
bool operator==(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <class Iterator>
bool operator!=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <class Iterator>
bool operator<(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <class Iterator>
bool operator<=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
	return (lhs.base() <= rhs.base());
}

template <class Iterator>
bool operator>(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <class Iterator>
bool operator>=(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <class Iterator>
typename random_access_iterator<Iterator>::difference_type operator-(const random_access_iterator<Iterator>& lhs, const random_access_iterator<Iterator>& rhs)
{
	return (lhs.base() + rhs.base());
}

template <class Iterator>
random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator>& rev_it)
{
	return (random_access_iterator<Iterator> (rev_it.base() - n));
}


/*
** reverse_ iterator
*/

template <class Iterator>
class reverse_iterator
:public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category, typename ft::iterator_traits<Iterator>::value_type, typename ft::iterator_traits<Iterator>::difference_type, typename ft::iterator_traits<Iterator>::pointer, typename ft::iterator_traits<Iterator>::reference>
{
private:
	Iterator _it;

public:
	typedef Iterator													iterator_type;
	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	typedef typename ft::iterator_traits<Iterator>::reference			reference;

public:

	reverse_iterator() : _it() {}
	explicit reverse_iterator(iterator_type it) : _it(it) {}

	reverse_iterator(const reverse_iterator<Iterator>& rev_it) : _it(rev_it._it)
	{
		*this = rev_it;
	}

	reverse_iterator& operator=(const reverse_iterator<Iterator>& rev_it)
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
		iterator_type it = this->_it;
		return (*(--it));
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

	reverse_iterator operator--(int)
	{
		reverse_iterator tmp = *this;
		++(this->_it);
		return (tmp);
	}

	reverse_iterator& operator-=(difference_type n)
	{
		this->_it += n;
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

template <class Iterator>
typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
	//TODO: -인지 +인지 확인할 것.
	return (lhs.base() - rhs.base());
}

template <class Iterator>
reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
{
	return (reverse_iterator<Iterator> (rev_it.base() - n));
}

}

#endif
