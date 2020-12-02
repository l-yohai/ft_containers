#include "vector.hpp"
#include <vector>
#include <iostream>

#include <iostream>
#include <vector>

void construct_test()
{
	// constructors used in the same order as described above:
	std::vector<int> first;                                // empty vector of ints
	std::vector<int> second (4,100);                       // four ints with value 100
	std::vector<int> third (second.begin(),second.end());  // iterating through second
	std::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	std::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::string my;
	my += "The contents of fifth are:";
	for (std::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		my += (' ' + *it);
	my += '\n';

	std::string origin = "The contents of fifth are: 16 2 77 29";

	std::cout << my << std::endl;
	std::cout << origin << std::endl;
	if (my.compare(origin) == 0)
		std::cout << "PASS" << std::endl;
	else
		std::cout << "FAIL" << std::endl;
}

void vector_test()
{
	void (*f)();

	std::vector<void (*)(void)> tests = {
		construct_test,
	};
}