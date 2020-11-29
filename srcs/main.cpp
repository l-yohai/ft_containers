/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohlee <yohlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 06:32:36 by yohlee            #+#    #+#             */
/*   Updated: 2020/11/29 22:56:10 by yohlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iterator.hpp"
#include <iostream>
#include <vector>

#define END			"[0m"
#define BOLD		"[1m"
#define UNDER		"[4m"
#define REV			"[7m"
#define GREY		"[30m"
#define RED			"[31m"
#define GREEN		"[32m"
#define YELLOW		"[33m"
#define BLUE		"[34m"
#define PURPLE		"[35m"
#define CYAN		"[36m"
#define WHITE		"[37m"

void print_title()
{
	std::cout << "\033" << REV << "\033[01m";
	std::cout << "\033" << UNDER << "\033[01m";
	std::cout << "\033" << GREEN << "\033[01m";
	std::cout << "ft_containers Tester by yohlee" << std::endl << std::endl;
	std::cout << "\033" << END << "\033[01m";
}

void print_testcase()
{
	std::cout << "\033" << BLUE << "\033[01m";
	std::cout << "Test case:";
}

void print_result()
{
	std::cout << "\033" << RED << "\033[01m";
	std::cout << "Result   :";
}

void print_answer()
{
	std::cout << "\033" << YELLOW << "\033[01m";
	std::cout << "Answer   :";
}

void print_next()
{

}

void reverse_iterator_base_test()
{
	std::vector<int> myvector;

	std::cout << "\033" << PURPLE << "\033[01m";
	std::cout << "REVERSE ITERATOR BASE" << std::endl << std::endl;

	print_testcase();
	for (int i = 0; i < 10; i++)
	{
		myvector.push_back(i);
		std::cout << " " << i;
	}
	std::cout << std::endl;

	typedef std::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_end(myvector.begin());
	ft::reverse_iterator<iter_type> rev_begin(myvector.end());

	print_result();
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	print_answer();
	std::cout << " 0 1 2 3 4 5 6 7 8 9" << std::endl;
}

// void reverse_iterator_operator_test()
// {
// 	std::vector<int> myvector;

// 	for (int i = 0; i < 10; i++)
// 		myvector.push_back(i);

// 	typedef std::vector<int>::iterator iter_type;

// 	iter_type from(myvector.begin());
// 	iter_type until(myvector.end());

// 	ft::reverse_iterator<iter_type> rev_until(from);
// 	ft::reverse_iterator<iter_type> rev_from(until);

// 	std::cout << "myvector:";
// 	while (rev_from != rev_until)
// 		std::cout << ' ' << *rev_from++;
// 	std::cout << '\n';
// }

int main()
{
	while (1)
	{
		system("clear");
		print_title();
		std::cout << "\033" << PURPLE << "\033[01m";
		std::cout << "This is the test for ft_containers." << std::endl << std::endl;

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
			break ;
	}

	void (*f)();

	std::vector<void (*)(void)> tests = {
		reverse_iterator_base_test,
		// reverse_iterator_operator_test,
	};

	std::vector<void (*)(void)>::iterator it = tests.begin();

	while (it != tests.end())
	{
		system("clear");
		print_title();

		f = *it;
		f();


		std::cout << "\033" << PURPLE << "\033[01m";
		std::cout << std::endl << "Input n(next) or p(prev) or q(quit)" << std::endl;
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