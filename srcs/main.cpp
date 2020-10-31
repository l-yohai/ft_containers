#include "Iterator.hpp"
#include <iostream>
#include <vector>

void reverse_iterator_base_test()
{
	std::vector<int> myvector;

	for (int i = 0; i < 10; i++)
		myvector.push_back(i);

	typedef std::vector<int>::iterator iter_type;

	ft::reverse_iterator<iter_type> rev_end(myvector.begin());
	ft::reverse_iterator<iter_type> rev_begin(myvector.end());

	std::cout << "myvector:";
	for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
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

	reverse_iterator_base_test();
	// reverse_iterator_operator_test();

	return 0;
}