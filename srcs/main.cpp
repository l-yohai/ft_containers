/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 06:32:36 by yohlee            #+#    #+#             */
/*   Updated: 2020/12/02 20:03:40 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "list.hpp"
#include "utils.hpp"
#include "queue.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <unistd.h>
#include <iterator>
#include <sys/types.h>
#include <sys/wait.h>

#define END "[0m"
#define BOLD "[1m"
#define UNDER "[4m"
#define REV "[7m"
#define GREY "[30m"
#define RED "[31m"
#define GREEN "[32m"
#define YELLOW "[33m"
#define BLUE "[34m"
#define PURPLE "[35m"
#define CYAN "[36m"
#define WHITE "[37m"

void print_title()
{
	std::cout << "\033" << REV << "\033[01m";
	std::cout << "\033" << UNDER << "\033[01m";
	std::cout << "\033" << GREEN << "\033[01m";
	std::cout << "ft_containers Tester by yohlee" << std::endl
			  << std::endl;
	std::cout << "\033" << END << "\033[01m";
}

void print_result()
{
	std::cout << "\033" << RED << "\033[01m";
	std::cout << "Result : ";
}

void print_answer()
{
	std::cout << "\033[36m\033[01m";
	std::cout << "===============================================" << std::endl;
	std::cout << "\033[0m";

	std::cout << "\033" << YELLOW << "\033[01m";
	std::cout << "Answer : ";
}

void vector_construct_test()
{
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR CONTRUCTOR TEST" << std::endl
			  << std::endl;

	// constructors used in the same order as described above:
	ft::vector<int> first;								 // empty vector of ints
	ft::vector<int> second(4, 100);						 // four ints with value 100
	ft::vector<int> third(second.begin(), second.end()); // iterating through second
	ft::vector<int> fourth(third);						 // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16, 2, 77, 29};
	ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	print_result();
	std::cout << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::string origin = "The contents of fifth are: 16 2 77 29";
	std::cout << origin << std::endl;
}

void vector_assign_test()
{
	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR ASSIGN TEST" << std::endl
			  << std::endl;

	first.assign(7, 100); // 7 ints with a value of 100

	ft::vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1); // the 5 central values of first

	int myints[] = {1776, 7, 4};
	third.assign(myints, myints + 3); // assigning from array.

	print_result();
	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';
	std::cout << "Size of third: " << int(third.size()) << '\n';

	print_answer();
	std::cout << "Size of first: 7" << '\n';
	std::cout << "Size of second: 5" << '\n';
	std::cout << "Size of third: 3" << '\n';
}

void vector_at_test()
{
	ft::vector<int> myvector(10); // 10 zero-initialized ints

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR AT TEST" << std::endl
			  << std::endl;

	// assign some values:
	for (unsigned i = 0; i < myvector.size(); i++)
		myvector.at(i) = i;

	print_result();
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';

	print_answer();
	std::cout << " 0 1 2 3 4 5 6 7 8 9" << std::endl;
}

void vector_back_test()
{
	ft::vector<int> myvector;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR BACK TEST" << std::endl
			  << std::endl;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back(myvector.back() - 1);
	}

	print_result();
	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 10 9 8 7 6 5 4 3 2 1 0" << std::endl;
}

void vector_begin_test()
{
	ft::vector<int> myvector;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR BEGIN TEST" << std::endl
			  << std::endl;

	print_result();
	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 1 2 3 4 5" << std::endl;
}

void vector_capacity_test()
{
	ft::vector<int> myvector;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR CAPACITY TEST" << std::endl
			  << std::endl;

	// set some content in the vector:
	for (int i = 0; i < 100; i++)
		myvector.push_back(i);

	print_result();
	std::cout << "size: " << (int)myvector.size() << '\n';
	std::cout << "capacity: " << (int)myvector.capacity() << '\n';

	print_answer();
	std::cout << "size: 100" << std::endl;
	std::cout << "capacity: 128" << std::endl;

}

void vector_clear_test()
{
	ft::vector<int> myvector;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR CLEAR TEST" << std::endl
			  << std::endl;

	print_result();
	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	myvector.clear();
	myvector.push_back(1101);
	myvector.push_back(2202);

	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 100 200 300" << std::endl;
	std::cout << "myvector contains: 1101 2202" << std::endl;
}

void vector_empty_test()
{
	ft::vector<int> myvector;
	int sum(0);

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR empty TEST" << std::endl
			  << std::endl;

	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	print_result();
	std::cout << "total: " << sum << '\n';

	print_answer();
	std::cout << "total: 55" << std::endl;
}

void vector_end_test()
{
	ft::vector<int> myvector;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR END TEST" << std::endl
			  << std::endl;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);

	print_result();
	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 1 2 3 4 5" << std::endl;
}

void vector_erase_test()
{
	ft::vector<int> myvector;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR ERASE TEST" << std::endl
			  << std::endl;

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++)
		myvector.push_back(i);

	// erase the 6th element
	myvector.erase(myvector.begin() + 5);

	// erase the first 3 elements:
	myvector.erase(myvector.begin(), myvector.begin() + 3);
	print_result();
	std::cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 4 5 7 8 9 10" << std::endl;
}

void vector_front_test()
{
	ft::vector<int> myvector;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR FRONT TEST" << std::endl
			  << std::endl;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();
	print_result();
	std::cout << "myvector.front() is now " << myvector.front() << '\n';
	print_answer();
	std::cout << "myvector.front() is now 62" << std::endl;
}

void vector_insert_test()
{
	ft::vector<int> myvector(3, 100);
	ft::vector<int>::iterator it;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR INSERT TEST" << std::endl
			  << std::endl;

	it = myvector.begin();
	it = myvector.insert(it, 200);

	myvector.insert(it, 2, 300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	int myarray[] = {501, 502, 503};
	myvector.insert(myvector.begin(), myarray, myarray + 3);
	print_result();
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 501 502 503 300 300 400 400 200 100 100 100" << std::endl;
}

void vector_pop_back_test()
{
	ft::vector<int> myvector;
	int sum(0);

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR POP_BACK TEST" << std::endl
			  << std::endl;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}
	print_result();
	std::cout << "The elements of myvector add up to " << sum << '\n';
	print_answer();
	std::cout << "The elements of myvector add up to 600" << std::endl;
}

void vector_rbegin_test()
{
	ft::vector<int> myvector(5); // 5 default-constructed ints
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR RBEGIN TEST" << std::endl
			  << std::endl;
	int i = 0;

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	for (; rit != myvector.rend(); ++rit)
		*rit = ++i;
	print_result();
	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 5 4 3 2 1" << std::endl;
}

void vector_rend_test()
{
	ft::vector<int> myvector(5); // 5 default-constructed ints

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR REND TEST" << std::endl
			  << std::endl;
	int i = 0;
	for (rit = myvector.rbegin(); rit != myvector.rend(); ++rit)
		*rit = ++i;
	print_result();
	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "myvector contains: 5 4 3 2 1 " << std::endl;
}

void vector_reserve_test()
{
	ft::vector<int>::size_type sz;

	ft::vector<int> foo;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR REVERSE TEST" << std::endl
			  << std::endl;
	sz = foo.capacity();
	print_result();
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100); // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		bar.push_back(i);
		if (sz != bar.capacity())
		{
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	print_answer();
	std::cout << "making foo grow:" << std::endl;
	std::cout << "capacity changed: 1" << std::endl;
	std::cout << "capacity changed: 2" << std::endl;
	std::cout << "capacity changed: 4" << std::endl;
	std::cout << "capacity changed: 8" << std::endl;
	std::cout << "capacity changed: 16" << std::endl;
	std::cout << "capacity changed: 32" << std::endl;
	std::cout << "capacity changed: 64" << std::endl;
	std::cout << "capacity changed: 128" << std::endl;
	std::cout << "making bar grow:" << std::endl;
	std::cout << "capacity changed: 100" << std::endl;
}

void vector_resize_test()
{
	ft::vector<int> myvector;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR RESIZE TEST" << std::endl
			  << std::endl;
	// set some initial content:
	for (int i = 1; i < 10; i++)
		myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8, 100);
	myvector.resize(12);
	print_result();
	std::cout << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';

	print_answer();
	std::cout << "myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0" << std::endl;
}

void vector_size_test()
{
	ft::vector<int> myints;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR SIZE TEST" << std::endl;
	std::cout << "0. size: " << myints.size() << '\n';
	print_result();
	for (int i = 0; i < 10; i++)
		myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert(myints.end(), 10, 100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';

	print_answer();
	std::cout << "0. size: 0" << std::endl;
	std::cout << "1. size: 10" << std::endl;
	std::cout << "2. size: 20" << std::endl;
	std::cout << "3. size: 19" << std::endl;
}

void vector_swap_test()
{
	ft::vector<int> foo(3, 100); // three ints with a value of 100
	ft::vector<int> bar(5, 200); // five ints with a value of 200
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "VECTOR SWAP TEST" << std::endl
			  << std::endl;
	foo.swap(bar);
	print_result();
	std::cout << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';

	print_answer();
	std::cout << "foo contains: 200 200 200 200 200 " << std::endl;
	std::cout << "bar contains: 100 100 100 " << std::endl;
}

void stack_empty_test()
{
	ft::stack<int> mystack;
	int sum(0);

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "STACK EMPTY TEST" << std::endl
			  << std::endl;

	for (int i = 1; i <= 10; i++)
		mystack.push(i);

	while (!mystack.empty())
	{
		sum += mystack.top();
		mystack.pop();
	}
	print_result();
	std::cout << "total: " << sum << '\n';
	print_answer();
	std::cout << "total: 55" << std::endl;
}

void stack_pop_test()
{
	ft::stack<int> mystack;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "STACK POP TEST" << std::endl
			  << std::endl;
	for (int i = 0; i < 5; ++i)
		mystack.push(i);
	print_result();
	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';

	print_answer();
	std::cout << "Popping out elements... 4 3 2 1 0" << std::endl;
}

void stack_push_test()
{
	ft::stack<int> mystack;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "STACK PUSH TEST" << std::endl
			  << std::endl;
	for (int i = 0; i < 5; ++i)
		mystack.push(i);
	print_result();
	std::cout << "Popping out elements...";
	while (!mystack.empty())
	{
		std::cout << ' ' << mystack.top();
		mystack.pop();
	}
	std::cout << '\n';

	print_answer();
	std::cout << "Popping out elements... 4 3 2 1 0" << std::endl;
}

void stack_size_test()
{
	ft::stack<int> myints;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "STACK SIZE TEST" << std::endl
			  << std::endl;
	print_result();
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 5; i++)
		myints.push(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';

	print_answer();
	std::cout << "0. size: 0" << std::endl;
	std::cout << "1. size: 5" << std::endl;
	std::cout << "2. size: 4" << std::endl;
}

void stack_top_test()
{
	ft::stack<int> mystack;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "STACK TOP TEST" << std::endl
			  << std::endl;
	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;
	print_result();
	std::cout << "mystack.top() is now " << mystack.top() << '\n';
	print_answer();
	std::cout << "mystack.top() is now 15" << std::endl;
}

void list_assign_test()
{
	ft::list<int> first;
	ft::list<int> second;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST ASSIGN TEST" << std::endl
			  << std::endl;
	first.assign(7, 100); // 7 ints with value 100

	second.assign(first.begin(), first.end()); // a copy of first

	int myints[] = {1776, 7, 4};
	first.assign(myints, myints + 3); // assigning from array
	print_result();
	std::cout << "Size of first: " << int(first.size()) << '\n';
	std::cout << "Size of second: " << int(second.size()) << '\n';

	print_answer();
	std::cout << "Size of first: 3" << std::endl;
	std::cout << "Size of second: 7" << std::endl;
}

void list_back_test()
{
	ft::list<int> mylist;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST BACK TEST" << std::endl
			  << std::endl;
	mylist.push_back(10);

	while (mylist.back() != 0)
	{
		mylist.push_back(mylist.back() - 1);
	}
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 10 9 8 7 6 5 4 3 2 1 0" << std::endl;
}

void list_begin_test()
{
	int myints[] = {75, 23, 65, 42, 13};
	ft::list<int> mylist(myints, myints + 5);
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST BEGIN TEST" << std::endl
			  << std::endl;
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 75 23 65 42 13" << std::endl;
}

void list_clear_test()
{
	ft::list<int> mylist;
	ft::list<int>::iterator it;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST CLEAR TEST" << std::endl
			  << std::endl;
	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);
	print_result();
	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.clear();
	mylist.push_back(1101);
	mylist.push_back(2202);

	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::cout << "mylist contains: 100 200 300" << std::endl;
	std::cout << "mylist contains: 1101 2202" << std::endl;
}

void list_empty_test()
{
	ft::list<int> mylist;
	int sum(0);
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST EMPTY TEST" << std::endl
			  << std::endl;
	for (int i = 1; i <= 10; ++i)
		mylist.push_back(i);

	while (!mylist.empty())
	{
		sum += mylist.front();
		mylist.pop_front();
	}
	print_result();
	std::cout << "total: " << sum << '\n';

	print_answer();
	std::cout << "total: 55" << std::endl;
}

void list_end_test()
{
	int myints[] = {75, 23, 65, 42, 13};
	ft::list<int> mylist(myints, myints + 5);
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST END TEST" << std::endl
			  << std::endl;
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 75 23 65 42 13" << std::endl;
}

void list_erase_test()
{
	ft::list<int> mylist;
	ft::list<int>::iterator it1, it2;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST ERASE TEST" << std::endl
			  << std::endl;
	// set some values:
	for (int i = 1; i < 10; ++i)
		mylist.push_back(i * 10);

	// 10 20 30 40 50 60 70 80 90
	it1 = it2 = mylist.begin(); // ^^
	advance(it2, 6);			// ^                 ^
	++it1;						//    ^              ^

	it1 = mylist.erase(it1); // 10 30 40 50 60 70 80 90
							 //    ^           ^

	it2 = mylist.erase(it2); // 10 30 40 50 60 80 90
							 //    ^           ^

	++it1; //       ^        ^
	--it2; //       ^     ^

	mylist.erase(it1, it2); // 10 30 60 80 90
							//        ^
	print_result();
	std::cout << "mylist contains:";
	for (it1 = mylist.begin(); it1 != mylist.end(); ++it1)
		std::cout << ' ' << *it1;
	std::cout << '\n';

	print_answer();
	std::cout << "mylist contains: 10 30 60 80 90" << std::endl;
}

void list_insert_test()
{
	ft::list<int> mylist;
	ft::list<int>::iterator it;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST INSERT TEST" << std::endl
			  << std::endl;
	// set some initial values:
	for (int i = 1; i <= 5; ++i)
		mylist.push_back(i); // 1 2 3 4 5

	it = mylist.begin();
	++it; // it points now to number 2           ^

	mylist.insert(it, 10); // 1 10 2 3 4 5

	// "it" still points to number 2                      ^
	mylist.insert(it, 2, 20); // 1 10 20 20 2 3 4 5

	--it; // it points now to the second 20            ^

	std::vector<int> myvector(2, 30);
	mylist.insert(it, myvector.begin(), myvector.end());
	// 1 10 20 30 30 20 2 3 4 5
	//               ^
	print_result();
	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 1 10 20 30 30 20 2 3 4 5" << std::endl;
}

void list_front_test()
{
	ft::list<int> mylist;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST FRONT TEST" << std::endl
			  << std::endl;

	mylist.push_back(77);
	mylist.push_back(22);

	// now front equals 77, and back 22

	mylist.front() -= mylist.back();
	print_result();
	std::cout << "mylist.front() is now " << mylist.front() << '\n';
	print_answer();
	std::cout << "mylist.front() is now 55" << std::endl;
}

bool mycomparison(double first, double second)
{
	return (int(first) < int(second));
}

void list_merge_test()
{
	ft::list<double> first, second;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST MERGE TEST" << std::endl
			  << std::endl;

	first.push_back(3.1);
	first.push_back(2.2);
	first.push_back(2.9);

	second.push_back(3.7);
	second.push_back(7.1);
	second.push_back(1.4);

	first.sort();
	second.sort();

	first.merge(second);

	// (second is now empty)

	second.push_back(2.1);

	first.merge(second, mycomparison);
	print_result();
	std::cout << "first contains:";
	for (ft::list<double>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "first contains: 1.4 2.2 2.9 2.1 3.1 3.7 7.1" << std::endl;
}

void list_pop_back_test()
{
	ft::list<int> mylist;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST POP_BACK TEST" << std::endl
			  << std::endl;
	int sum(0);
	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);

	while (!mylist.empty())
	{
		sum += mylist.back();
		mylist.pop_back();
	}
	print_result();
	std::cout << "The elements of mylist summed " << sum << '\n';
	print_answer();
	std::cout << "The elements of mylist summed 600" << std::endl;
}

void list_pop_front_test()
{
	ft::list<int> mylist;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST POP_FRONT TEST" << std::endl
			  << std::endl;
	mylist.push_back(100);
	mylist.push_back(200);
	mylist.push_back(300);
	print_result();
	std::cout << "Popping out the elements in mylist:";
	while (!mylist.empty())
	{
		std::cout << ' ' << mylist.front();
		mylist.pop_front();
	}

	std::cout << "\nFinal size of mylist is " << mylist.size() << '\n';

	print_answer();
	std::cout << "Popping out the elements in mylist: 100 200 300" << std::endl;
	std::cout << "Final size of mylist is 0" << std::endl;
}

void list_push_front_test()
{
	ft::list<int> mylist(2, 100); // two ints with a value of 100
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST PUSH_FRONT TEST" << std::endl
			  << std::endl;
	mylist.push_front(200);
	mylist.push_front(300);
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 300 200 100 100 " << std::endl;
}

void list_rbegin_test()
{
	ft::list<int> mylist;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST RBEGIN TEST" << std::endl
			  << std::endl;
	for (int i = 1; i <= 5; ++i)
		mylist.push_back(i);
	print_result();
	std::cout << "mylist backwards:";
	for (ft::list<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist backwards: 5 4 3 2 1" << std::endl;
}

void list_remove_test()
{
	int myints[] = {17, 89, 7, 14};
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST REMOVE TEST" << std::endl
			  << std::endl;
	ft::list<int> mylist(myints, myints + 4);

	mylist.remove(89);
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 17 7 14" << std::endl;
}

// a predicate implemented as a function:
bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd
{
	bool operator()(const int &value) { return (value % 2) == 1; }
};

void list_remove_if_test()
{
	int myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST REMOVE_IF TEST" << std::endl
			  << std::endl;
	ft::list<int> mylist(myints, myints + 8); // 15 36 7 17 20 39 4 1

	mylist.remove_if(single_digit); // 15 36 17 20 39

	mylist.remove_if(is_odd()); // 36 20
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 36 20" << std::endl;
}

void list_rend_test()
{
	ft::list<int> mylist;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST REND TEST" << std::endl
			  << std::endl;
	for (int i = 1; i <= 5; ++i)
		mylist.push_back(i);
	print_result();
	std::cout << "mylist backwards:";
	for (ft::list<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist backwards: 5 4 3 2 1" << std::endl;
}

void list_resize_test()
{
	ft::list<int> mylist;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST RESIZE TEST" << std::endl
			  << std::endl;
	// set some initial content:
	for (int i = 1; i < 10; ++i)
		mylist.push_back(i);

	mylist.resize(5);
	mylist.resize(8, 100);
	mylist.resize(12);
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 1 2 3 4 5 100 100 100 0 0 0 0" << std::endl;
}

void list_reverse_test()
{
	ft::list<int> mylist;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST REVERSE TEST" << std::endl
			  << std::endl;
	for (int i = 1; i < 10; ++i)
		mylist.push_back(i);

	mylist.reverse();
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 9 8 7 6 5 4 3 2 1" << std::endl;
}

void list_size_test()
{
	ft::list<int> myints;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST SIZE TEST" << std::endl
			  << std::endl;
	print_result();
	std::cout << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 10; i++)
		myints.push_back(i);
	std::cout << "1. size: " << myints.size() << '\n';

	myints.insert(myints.begin(), 10, 100);
	std::cout << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	std::cout << "3. size: " << myints.size() << '\n';
	print_answer();
	std::cout << "0. size: 0" << std::endl;
	std::cout << "1. size: 10" << std::endl;
	std::cout << "2. size: 20" << std::endl;
	std::cout << "3. size: 19" << std::endl;
}

// comparison, not case sensitive.
bool compare_nocase(const std::string &first, const std::string &second)
{
	unsigned int i = 0;
	while ((i < first.length()) && (i < second.length()))
	{
		if (tolower(first[i]) < tolower(second[i]))
			return true;
		else if (tolower(first[i]) > tolower(second[i]))
			return false;
		++i;
	}
	return (first.length() < second.length());
}

void list_sort_test()
{
	ft::list<std::string> mylist;
	ft::list<std::string>::iterator it;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST SORT TEST" << std::endl
			  << std::endl;
	mylist.push_back("one");
	mylist.push_back("two");
	mylist.push_back("Three");

	mylist.sort();
	print_result();
	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	mylist.sort(compare_nocase);

	std::cout << "mylist contains:";
	for (it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: Three one two" << std::endl;
	std::cout << "mylist contains: one Three two" << std::endl;
}

void list_splice_test()
{
	ft::list<int> mylist1, mylist2;
	ft::list<int>::iterator it;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST SPLICE TEST" << std::endl
			  << std::endl;

	// set some initial values:
	for (int i = 1; i <= 4; ++i)
		mylist1.push_back(i); // mylist1: 1 2 3 4

	for (int i = 1; i <= 3; ++i)
		mylist2.push_back(i * 10); // mylist2: 10 20 30

	it = mylist1.begin();
	++it; // points to 2

	mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
								 // mylist2 (empty)
								 // "it" still points to 2 (the 5th element)

	mylist2.splice(mylist2.begin(), mylist1, it);
	// mylist1: 1 10 20 30 3 4
	// mylist2: 2
	// "it" is now invalid.
	it = mylist1.begin();
	advance(it, 3); // "it" points now to 30

	mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
	// mylist1: 30 3 4 1 10 20
	print_result();
	std::cout << "mylist1 contains:";
	for (it = mylist1.begin(); it != mylist1.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "mylist2 contains:";
	for (it = mylist2.begin(); it != mylist2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "mylist1 contains: 30 3 4 1 10 20" << std::endl;
	std::cout << "mylist2 contains: 2" << std::endl;
}

void list_swap_test()
{
	ft::list<int> first(3, 100);  // three ints with a value of 100
	ft::list<int> second(5, 200); // five ints with a value of 200
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST SWAP TEST" << std::endl
			  << std::endl;
	first.swap(second);
	print_result();
	std::cout << "first contains:";
	for (ft::list<int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (ft::list<int>::iterator it = second.begin(); it != second.end(); it++)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::cout << "first contains: 200 200 200 200 200 " << std::endl;
	std::cout << "second contains: 100 100 100 " << std::endl;
}

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second)
{
	return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near
{
	bool operator()(double first, double second)
	{
		return (fabs(first - second) < 5.0);
	}
};

void list_unique_test()
{
	double mydoubles[] = {12.15, 2.72, 73.0, 12.77, 3.14,
						  12.77, 73.35, 72.25, 15.3, 72.25};
	ft::list<double> mylist(mydoubles, mydoubles + 10);
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "LIST UNIQUE TEST" << std::endl
			  << std::endl;
	mylist.sort(); //  2.72,  3.14, 12.15, 12.77, 12.77,
				   // 15.3,  72.25, 72.25, 73.0,  73.35

	mylist.unique(); //  2.72,  3.14, 12.15, 12.77
					 // 15.3,  72.25, 73.0,  73.35

	mylist.unique(same_integral_part); //  2.72,  3.14, 12.15
									   // 15.3,  72.25, 73.0

	mylist.unique(is_near()); //  2.72, 12.15, 72.25
	print_result();
	std::cout << "mylist contains:";
	for (ft::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	print_answer();
	std::cout << "mylist contains: 2.72 12.15 72.25" << std::endl;
}

void queue_back_test()
{
	ft::queue<int> myqueue;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "QUEUE BACK TEST" << std::endl
			  << std::endl;
	myqueue.push(12);
	myqueue.push(75); // this is now the back

	myqueue.back() -= myqueue.front();
	print_result();
	std::cout << "myqueue.back() is now " << myqueue.back() << '\n';
	print_answer();
	std::cout << "myqueue.back() is now 63" << std::endl;
}

void queue_empty_test()
{
	ft::queue<int> myqueue;
	int sum(0);
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "QUEUE EMPTY TEST" << std::endl
			  << std::endl;
	for (int i = 1; i <= 10; i++)
		myqueue.push(i);

	while (!myqueue.empty())
	{
		sum += myqueue.front();
		myqueue.pop();
	}
	print_result();
	std::cout << "total: " << sum << '\n';

	print_answer();
	std::cout << "total: 55" << std::endl;
}

void queue_front_test()
{
	ft::queue<int> myqueue;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "QUEUE FRONT TEST" << std::endl
			  << std::endl;
	myqueue.push(77);
	myqueue.push(16);

	myqueue.front() -= myqueue.back(); // 77-16=61
	print_result();
	std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
	print_answer();
	std::cout << "myqueue.front() is now 61" << std::endl;
}

void queue_size_test()
{
	ft::queue<int> myints;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "QUEUE SIZE TEST" << std::endl;
	std::cout << "0. size: " << myints.size() << '\n';
	for (int i = 0; i < 5; i++)
		myints.push(i);
	print_result();
	std::cout << "1. size: " << myints.size() << '\n';

	myints.pop();
	std::cout << "2. size: " << myints.size() << '\n';

	print_answer();
	std::cout << "0. size: 0" << std::endl;
	std::cout << "1. size: 5" << std::endl;
	std::cout << "2. size: 4" << std::endl;
}

void map_begin_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP BEGIN TEST" << std::endl
			  << std::endl;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	print_result();
	// show content:
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	print_answer();
	std::cout << "a => 200" << std::endl;
	std::cout << "b => 100" << std::endl;
	std::cout << "c => 300" << std::endl;
}

void map_clear_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP CLEAR TEST" << std::endl
			  << std::endl;
	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;
	print_result();
	std::cout << "mymap contains:\n";
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a'] = 1101;
	mymap['b'] = 2202;

	std::cout << "mymap contains:\n";
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	print_answer();
	std::cout << "mymap contains:" << std::endl;
	std::cout << "x => 100" << std::endl;
	std::cout << "y => 200" << std::endl;
	std::cout << "z => 300" << std::endl;
	std::cout << "mymap contains:" << std::endl;
	std::cout << "a => 1101" << std::endl;
	std::cout << "b => 2202" << std::endl;
}

void map_count_test()
{
	ft::map<char, int> mymap;
	char c;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP COUNT TEST" << std::endl
			  << std::endl;
	mymap['a'] = 101;
	mymap['c'] = 202;
	mymap['f'] = 303;
	print_result();
	for (c = 'a'; c < 'h'; c++)
	{
		std::cout << c;
		if (mymap.count(c) > 0)
			std::cout << " is an element of mymap.\n";
		else
			std::cout << " is not an element of mymap.\n";
	}

	print_answer();
	std::cout << "a is an element of mymap." << std::endl;
	std::cout << "b is not an element of mymap." << std::endl;
	std::cout << "c is an element of mymap." << std::endl;
	std::cout << "d is not an element of mymap." << std::endl;
	std::cout << "e is not an element of mymap." << std::endl;
	std::cout << "f is an element of mymap." << std::endl;
	std::cout << "g is not an element of mymap." << std::endl;
}

void map_empty_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP EMPTY TEST" << std::endl
			  << std::endl;
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	print_result();
	while (!mymap.empty())
	{
		std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}

	print_answer();
	std::cout << "a => 10" << std::endl;
	std::cout << "b => 20" << std::endl;
	std::cout << "c => 30" << std::endl;
}

void map_end_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP END TEST" << std::endl
			  << std::endl;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	print_result();
	// show content:
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	print_answer();
	std::cout << "a => 200" << std::endl;
	std::cout << "b => 100" << std::endl;
	std::cout << "c => 300" << std::endl;
}

void map_equal_range_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP EQUAL_RANGE TEST" << std::endl
			  << std::endl;
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;

	ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> ret;
	ret = mymap.equal_range('b');
	print_result();
	std::cout << "lower bound points to: ";
	std::cout << ret.first->first << " => " << ret.first->second << '\n';

	std::cout << "upper bound points to: ";
	std::cout << ret.second->first << " => " << ret.second->second << '\n';

	print_answer();
	std::cout << "lower bound points to: b => 20" << std::endl;
	std::cout << "upper bound points to: c => 30" << std::endl;
}

void map_erase_test()
{
	ft::map<char, int> mymap;
	ft::map<char, int>::iterator it;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP ERASE TEST" << std::endl
			  << std::endl;
	// insert some values:
	mymap['a'] = 10;
	mymap['b'] = 20;
	mymap['c'] = 30;
	mymap['d'] = 40;
	mymap['e'] = 50;
	mymap['f'] = 60;

	it = mymap.find('b');
	mymap.erase(it); // erasing by iterator

	mymap.erase('c'); // erasing by key

	it = mymap.find('e');
	mymap.erase(it, mymap.end()); // erasing by range
	print_result();
	// show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	print_answer();
	std::cout << "a => 10" << std::endl;
	std::cout << "d => 40" << std::endl;
}

void map_find_test()
{
	ft::map<char, int> mymap;
	ft::map<char, int>::iterator it;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP FIND TEST" << std::endl
			  << std::endl;
	mymap['a'] = 50;
	mymap['b'] = 100;
	mymap['c'] = 150;
	mymap['d'] = 200;

	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase(it);
	print_result();
	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';

	print_answer();
	std::cout << "elements in mymap:" << std::endl;
	std::cout << "a => 50" << std::endl;
	std::cout << "c => 150" << std::endl;
	std::cout << "d => 200" << std::endl;
}

void map_insert_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP INSERT TEST" << std::endl
			  << std::endl;
	// first insert function version (single parameter):
	mymap.insert(ft::pair<char, int>('a', 100));
	mymap.insert(ft::pair<char, int>('z', 200));

	ft::pair<ft::map<char, int>::iterator, bool> ret;
	ret = mymap.insert(ft::pair<char, int>('z', 500));
	if (ret.second == false)
	{
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	ft::map<char, int>::iterator it = mymap.begin();
	mymap.insert(it, ft::pair<char, int>('b', 300)); // max efficiency inserting
	mymap.insert(it, ft::pair<char, int>('c', 400)); // no max efficiency inserting

	// third insert function version (range insertion):
	ft::map<char, int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));
	print_result();
	// showing contents:
	std::cout << "mymap contains:\n";
	for (it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it = anothermap.begin(); it != anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	print_answer();
	std::cout << "element 'z' already existed with a value of 200" << std::endl;
	std::cout << "mymap contains:" << std::endl;
	std::cout << "a => 100" << std::endl;
	std::cout << "b => 300" << std::endl;
	std::cout << "c => 400" << std::endl;
	std::cout << "z => 200" << std::endl;
	std::cout << "anothermap contains:" << std::endl;
	std::cout << "a => 100" << std::endl;
	std::cout << "b => 300" << std::endl;
}

void map_key_comp_test()
{
	ft::map<char, int> mymap;

	ft::map<char, int>::key_compare mycomp = mymap.key_comp();
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP KEY_COMP TEST" << std::endl
			  << std::endl;
	mymap['a'] = 100;
	mymap['b'] = 200;
	mymap['c'] = 300;
	print_result();
	std::cout << "mymap contains:\n";

	char highest = mymap.rbegin()->first; // key value of last element

	ft::map<char, int>::iterator it = mymap.begin();
	do
	{
		std::cout << it->first << " => " << it->second << '\n';
	} while (mycomp((*it++).first, highest));

	std::cout << '\n';

	print_answer();
	std::cout << "mymap contains:" << std::endl;
	std::cout << "a => 100" << std::endl;
	std::cout << "b => 200" << std::endl;
	std::cout << "c => 300" << std::endl;
}

void map_lower_bound_test()
{
	ft::map<char, int> mymap;
	ft::map<char, int>::iterator itlow, itup;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP LOWER_BOUND TEST" << std::endl
			  << std::endl;
	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;

	itlow = mymap.lower_bound('b'); // itlow points to b
	itup = mymap.upper_bound('d');	// itup points to e (not d!)

	mymap.erase(itlow, itup); // erases [itlow,itup)
	print_result();
	// print content:
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	print_answer();
	std::cout << "a => 20" << std::endl;
	std::cout << "e => 100" << std::endl;
}

void map_rbegin_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP RBEGIN TEST" << std::endl
			  << std::endl;
	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;
	print_result();
	// show content:
	ft::map<char, int>::reverse_iterator rit;
	for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

	print_answer();
	std::cout << "z => 300" << std::endl;
	std::cout << "y => 200" << std::endl;
	std::cout << "x => 100" << std::endl;
}

void map_rend_test()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP REND TEST" << std::endl
			  << std::endl;
	mymap['x'] = 100;
	mymap['y'] = 200;
	mymap['z'] = 300;
	print_result();
	// show content:
	ft::map<char, int>::reverse_iterator rit;
	for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';

	print_answer();
	std::cout << "z => 300" << std::endl;
	std::cout << "y => 200" << std::endl;
	std::cout << "x => 100" << std::endl;
}

void map_size_test()
{
	ft::map<char, int> mymap;
	mymap['a'] = 101;
	mymap['b'] = 202;
	mymap['c'] = 302;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP SIZE TEST" << std::endl
			  << std::endl;
	print_result();
	std::cout << "mymap.size() is " << mymap.size() << '\n';

	print_answer();
	std::cout << "mymap.size() is 3" << std::endl;
}

void map_swap_test()
{
	ft::map<char, int> foo, bar;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP SWAP TEST" << std::endl
			  << std::endl;
	foo['x'] = 100;
	foo['y'] = 200;

	bar['a'] = 11;
	bar['b'] = 22;
	bar['c'] = 33;

	foo.swap(bar);
	print_result();
	std::cout << "foo contains:\n";
	for (ft::map<char, int>::iterator it = foo.begin(); it != foo.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "bar contains:\n";
	for (ft::map<char, int>::iterator it = bar.begin(); it != bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	print_answer();
	std::cout << "foo contains:" << std::endl;
	std::cout << "a => 11" << std::endl;
	std::cout << "b => 22" << std::endl;
	std::cout << "c => 33" << std::endl;
	std::cout << "bar contains:" << std::endl;
	std::cout << "x => 100" << std::endl;
	std::cout << "y => 200" << std::endl;
}

void map_upper_bound_test()
{
	ft::map<char, int> mymap;
	ft::map<char, int>::iterator itlow, itup;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP UPPER_BOUND TEST" << std::endl
			  << std::endl;
	mymap['a'] = 20;
	mymap['b'] = 40;
	mymap['c'] = 60;
	mymap['d'] = 80;
	mymap['e'] = 100;

	itlow = mymap.lower_bound('b'); // itlow points to b
	itup = mymap.upper_bound('d');	// itup points to e (not d!)

	mymap.erase(itlow, itup); // erases [itlow,itup)
	print_result();
	// print content:
	for (ft::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	print_answer();
	std::cout << "a => 20" << std::endl;
	std::cout << "e => 100" << std::endl;
}

void map_value_comp()
{
	ft::map<char, int> mymap;
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "MAP VALUE_COMP TEST" << std::endl
			  << std::endl;
	mymap['x'] = 1001;
	mymap['y'] = 2002;
	mymap['z'] = 3003;
	print_result();
	std::cout << "mymap contains:\n";

	ft::pair<char, int> highest = *mymap.rbegin(); // last element

	ft::map<char, int>::iterator it = mymap.begin();
	do
	{
		std::cout << it->first << " => " << it->second << '\n';
	} while (mymap.value_comp()(*it++, highest));

	print_answer();
	std::cout << "mymap contains:" << std::endl;
	std::cout << "x => 1001" << std::endl;
	std::cout << "y => 2002" << std::endl;
	std::cout << "z => 3003" << std::endl;
}

int main()
{
	while (1)
	{
		system("clear");
		print_title();
		std::cout << "\033" << PURPLE << "\033[01m";
		std::cout << "This is the test for ft_containers." << std::endl
				  << std::endl;

		std::cout << "\033[34m\033[01m";
		std::cout << "Are you ready?" << std::endl;
		std::cout << "\033[0m";

		std::cout << "\033[35m\033[01m";
		std::cout << "Input y(yes) or n(no)" << std::endl;
		std::cout << "\033[0m";

		char c;
		std::cin >> c;
		if (c == 'n')
		{
			std::cout << "\033[31m\033[01m";
			std::cout << "===============================================" << std::endl;
			std::cout << "test ended!" << std::endl;
			std::cout << "===============================================" << std::endl;
			std::cout << "\033[0m";
			exit(0);
		}
		else if (c == 'y')
			break;
	}

	void (*f)();

	std::vector<void (*)(void)> tests = {
		vector_construct_test,
		vector_assign_test,
		vector_at_test,
		vector_back_test,
		vector_begin_test,
		vector_capacity_test,
		vector_clear_test,
		vector_empty_test,
		vector_end_test,
		vector_erase_test,
		vector_front_test,
		vector_insert_test,
		vector_pop_back_test,
		vector_rbegin_test,
		vector_rend_test,
		vector_reserve_test,
		vector_resize_test,
		vector_size_test,
		vector_swap_test,
		
		stack_empty_test,
		stack_pop_test,
		stack_size_test,
		stack_top_test,
		
		list_assign_test,
		list_back_test,
		list_begin_test,
		list_clear_test,
		list_empty_test,
		list_end_test,
		list_erase_test,
		list_insert_test,
		list_front_test,
		list_merge_test,
		list_pop_back_test,
		list_pop_front_test,
		list_push_front_test,
		list_rbegin_test,
		list_remove_test,
		list_remove_if_test,
		list_rend_test,
		list_resize_test,
		list_reverse_test,
		list_size_test,
		list_sort_test,
		list_splice_test,
		list_swap_test,
		list_unique_test,

		queue_back_test,
		queue_empty_test,
		queue_front_test,
		queue_size_test,

		map_begin_test,
		map_clear_test,
		map_count_test,
		map_empty_test,
		map_end_test,
		map_equal_range_test,
		map_erase_test,
		map_find_test,
		map_key_comp_test,
		map_lower_bound_test,
		map_rbegin_test,
		map_rend_test,
		map_size_test,
		map_swap_test,
		map_upper_bound_test,
		map_value_comp,
	};

	std::vector<void (*)(void)>::iterator it = tests.begin();

	while (it != tests.end())
	{
		system("clear");
		print_title();

		f = *it;
		f();

		std::cout << "\033" << BLUE << "\033[01m";
		std::cout << std::endl
				  << "Input n(next) or p(prev) or q(quit)" << std::endl;
		char c;
		std::cin >> c;
		if (c == 'n')
			++it;
		else if (c == 'p')
			--it;
		else if (c == 'q')
			exit(0);
	}

	system("clear");
	print_title();
	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "TEST ENDED!" << std::endl;

	// reverse_iterator_base_test();
	// reverse_iterator_operator_test();

	return 0;
}