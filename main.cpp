#include "vector/vector.hpp"
#include <iostream>
#include <iomanip>
#include <vector>

void	print(std::vector<int> t, ft::vector<int> m)
{
	std::vector<int>::iterator it = t.begin();
	for (size_t i = 0; it != t.end(); i++, it++)
		std::cout << "STD vector " << i << ", it = " << *it << "\n";
	ft::vector<int>::iterator ite = m.begin();
	for (size_t i = 0; ite != m.end(); i++, ite++)
		std::cout << "FT vector " << i << ", it = " << *it << "\n";
}

int main()
{
	std::vector<int> test;
	ft::vector<int> mytest;

	for (size_t i = 0; i < 10; i++)
		test.push_back(i);
	for (size_t i = 0; i < 10; i++)
		test.push_back(i);
	print(test, mytest);
}