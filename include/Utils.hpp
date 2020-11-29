/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 07:17:41 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/29 13:35:04 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <limits>
#include <memory>

namespace ft
{
template <class T1, class T2>
struct pair
{
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair() : first(T1()), second(T2()) {}

	template <class U1, class U2>
	pair(const pair<U1, U2>& p) : first(p.first),
								  second(p.second)
	{
	}
	pair(const first_type& x, const second_type& y = T2()) : first(x),
															 second(y) {}

	pair& operator=(const pair& x)
	{
		first = x.first;
		second = x.second;
		return *this;
	}
};

template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}
template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return !(lhs == rhs);
}
template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	if (lhs.first < rhs.first)
		return true;
	return lhs.first == rhs.first && lhs.second < rhs.second;
}
template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return !(rhs < lhs);
}
template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return rhs < lhs;
}
template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
	return !(lhs < rhs);
}

template <class T1, class T2>
pair<T1, T2> make_pair(T1 a, T2 b)
{
	return pair<T1, T2>(a, b);
}

template <typename T>
struct less
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs < rhs;
	}
};

template <typename InputIterator, typename Compare>
bool lexicographical_compare(InputIterator lhsBegin, InputIterator lhsEnd,
							 InputIterator rhsBegin, InputIterator rhsEnd,
							 const Compare& comp)
{
	for (; lhsBegin != lhsEnd && rhsBegin != rhsEnd; ++lhsBegin, ++rhsBegin)
	{
		if (comp(*lhsBegin, *rhsBegin))
			return true;
		if (comp(*rhsBegin, *lhsBegin))
			return false;
	}
	return lhsBegin == lhsEnd && rhsBegin != rhsEnd;
}
template <typename InputIterator>
bool equal(InputIterator lhsBegin, InputIterator lhsEnd,
		   InputIterator rhsBegin)
{
	for (; lhsBegin != lhsEnd; ++lhsBegin, ++rhsBegin)
	{
		if (*lhsBegin != *rhsBegin)
			return false;
	}
	return true;
}

}  //namespace ft

#endif
