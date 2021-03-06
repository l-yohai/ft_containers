/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 23:15:09 by cchudant          #+#    #+#             */
/*   Updated: 2020/11/29 16:24:38 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

static void test_push_pop()
{
	ft::queue<ConstrCounter> queue;
	assert(queue.size() == 0);
	assert(queue.empty());

	queue.push(ConstrCounter(0));
	assert(queue.size() == 1);
	assert(!queue.empty());
	assert(queue.back() == 0);
	assert(queue.front() == 0);

	queue.push(ConstrCounter(1));
	assert(queue.size() == 2);
	assert(!queue.empty());
	assert(queue.back() == 1);
	assert(queue.front() == 0);

	queue.push(ConstrCounter(2));
	assert(queue.size() == 3);
	assert(!queue.empty());
	assert(queue.back() == 2);
	assert(queue.front() == 0);

	queue.push(ConstrCounter(3));
	assert(queue.size() == 4);
	assert(!queue.empty());
	assert(queue.back() == 3);
	assert(queue.front() == 0);

	queue.push(ConstrCounter(4));
	assert(queue.size() == 5);
	assert(!queue.empty());
	assert(queue.back() == 4);
	assert(queue.front() == 0);

	queue.pop();
	assert(queue.size() == 4);
	assert(!queue.empty());
	assert(queue.back() == 4);
	assert(queue.front() == 1);

	queue.pop();
	assert(queue.size() == 3);
	assert(!queue.empty());
	assert(queue.back() == 4);
	assert(queue.front() == 2);

	queue.pop();
	assert(queue.size() == 2);
	assert(!queue.empty());
	assert(queue.back() == 4);
	assert(queue.front() == 3);

	queue.pop();
	assert(queue.size() == 1);
	assert(!queue.empty());
	assert(queue.back() == 4);
	assert(queue.front() == 4);

	queue.pop();
	assert(queue.size() == 0);
	assert(queue.empty());
}

static void test_assign_copy()
{
	ft::queue<ConstrCounter> queue;
	queue.push(ConstrCounter(0));
	queue.push(ConstrCounter(1));
	queue.push(ConstrCounter(2));

	ft::queue<ConstrCounter> queue2(queue);
	assert(queue2.size() == 3);
	assert(queue2.back() == 2);
	assert(queue2.front() == 0);
	queue2.pop();
	assert(queue2.size() == 2);
	assert(queue2.back() == 2);
	assert(queue2.front() == 1);
	queue2.pop();
	assert(queue2.size() == 1);
	assert(queue2.back() == 2);
	assert(queue2.front() == 2);
	queue2.pop();
	assert(queue2.size() == 0);

	queue2.push(ConstrCounter(0));
	assert(queue2.size() == 1);
	queue2.push(ConstrCounter(1));
	assert(queue2.size() == 2);
	queue2.push(ConstrCounter(2));
	assert(queue2.size() == 3);

	queue2.push(ConstrCounter(3));
	assert(queue.size() == 3);
	assert(queue2.size() == 4);

	ft::queue<ConstrCounter> queue3;
	assert(queue3.size() == 0);

	queue3 = queue2;
	assert(queue.size() == 3);
	assert(queue2.size() == 4);
	assert(queue3.size() == 4);

	queue = queue3;
	assert(queue.size() == 4);
	assert(queue2.size() == 4);
	assert(queue3.size() == 4);

	assert(queue.size() == 4);
	assert(queue.back() == 3);
	assert(queue.front() == 0);
	queue.pop();
	assert(queue.size() == 3);
	assert(queue.back() == 3);
	assert(queue.front() == 1);
	queue.pop();
	assert(queue.size() == 2);
	assert(queue.back() == 3);
	assert(queue.front() == 2);
	queue.pop();
	assert(queue.size() == 1);
	assert(queue.back() == 3);
	assert(queue.front() == 3);
	queue.pop();
	assert(queue.size() == 0);

	assert(queue2.size() == 4);
	assert(queue2.back() == 3);
	assert(queue2.front() == 0);
	queue2.pop();
	assert(queue2.size() == 3);
	assert(queue2.back() == 3);
	assert(queue2.front() == 1);
	queue2.pop();
	assert(queue2.size() == 2);
	assert(queue2.back() == 3);
	assert(queue2.front() == 2);
	queue2.pop();
	assert(queue2.size() == 1);
	assert(queue2.back() == 3);
	assert(queue2.front() == 3);
	queue2.pop();
	assert(queue2.size() == 0);

	assert(queue3.size() == 4);
	assert(queue3.back() == 3);
	assert(queue3.front() == 0);
	queue3.pop();
	assert(queue3.size() == 3);
	assert(queue3.back() == 3);
	assert(queue3.front() == 1);
	queue3.pop();
	assert(queue3.size() == 2);
	assert(queue3.back() == 3);
	assert(queue3.front() == 2);
	queue3.pop();
	assert(queue3.size() == 1);
	assert(queue3.back() == 3);
	assert(queue3.front() == 3);
	queue3.pop();
	assert(queue3.size() == 0);
}

static void test_swap()
{
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	ft::queue<ConstrCounter> queue(ft::list<ConstrCounter>(array, array + 5));

	ConstrCounter array2[3] = {2, 3, 1};
	ft::queue<ConstrCounter> queue2(ft::list<ConstrCounter>(array2, array2 + 3));

	swap(queue, queue2);
	assert(queue.size() == 3);
	assert(queue2.size() == 5);
	assert(queue.back() == 1);
	assert(queue.front() == 2);
	assert(queue2.back() == 4);
	assert(queue2.front() == 0);

	swap(queue2, queue);
	assert(queue.size() == 5);
	assert(queue2.size() == 3);
	assert(queue.back() == 4);
	assert(queue.front() == 0);
	assert(queue2.back() == 1);
	assert(queue2.front() == 2);
}

static void test_cmp_eq()
{
	ConstrCounter array[5] = {0, 1, 2, 3, 4};
	ft::queue<ConstrCounter> queue(ft::list<ConstrCounter>(array, array + 5));
	ft::queue<ConstrCounter> queue2(queue);

	assert(queue == queue2);
	assert(queue >= queue2);
	assert(queue <= queue2);

	queue2.push(50);
	assert(queue != queue2);
	assert(queue < queue2);
	assert(queue <= queue2);
	assert(queue2 > queue);
	assert(queue2 >= queue);

	queue.push(200);
	assert(queue != queue2);
	assert(queue > queue2);
	assert(queue >= queue2);
	assert(queue2 < queue);
	assert(queue2 <= queue);
}

void test_queue()
{
	test_one("push_pop", test_push_pop);
	test_one("assign_copy", test_assign_copy);
	test_one("swap", test_swap);
	test_one("cmp_eq", test_cmp_eq);
}
