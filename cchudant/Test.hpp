/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 06:27:31 by cchudant          #+#    #+#             */
/*   Updated: 2020/11/29 22:16:38 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HPP
#define TEST_HPP

#include <assert.h>

#include <iostream>
#include <sstream>

// #include "../include/deque.hpp"
#include "../include/list.hpp"
#include "../include/map.hpp"
// #include "../include/multimap.hpp"
// #include "../include/multiset.hpp"
#include "../include/queue.hpp"
// #include "../include/set.hpp"
#include "../include/stack.hpp"
#include "../include/vector.hpp"

class ConstrCounter
{
public:
	static int g_constr;
	static int g_destr;

	int val;

	ConstrCounter();
	ConstrCounter(int val);
	ConstrCounter(const ConstrCounter &o);
	~ConstrCounter();

	static void reset_counters();
};

bool operator==(const ConstrCounter &lhs, const ConstrCounter &rhs);
bool operator!=(const ConstrCounter &lhs, const ConstrCounter &rhs);
bool operator<(const ConstrCounter &lhs, const ConstrCounter &rhs);
bool operator<=(const ConstrCounter &lhs, const ConstrCounter &rhs);
bool operator>(const ConstrCounter &lhs, const ConstrCounter &rhs);
bool operator>=(const ConstrCounter &lhs, const ConstrCounter &rhs);

void test_one(std::string name, void (&fn)());

void test_vector();
void test_stack();
void test_list();
void test_queue();
void test_map();
// void test_set();
// void test_multimap();
// void test_multiset();
// void test_deque();

#endif
