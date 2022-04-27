#include "vector/vector.hpp"

int	main()
{
	ft::vector<int> myVector;
	try
	{
		for (int i = 0; i < 10; i++)
		{	
			myVector.push_back(i);
			std::cout << i << " element is = " << myVector[i] << "\n";
		}
		for (int i = 0; i < 10; i++)
			std::cout << "index " << i << "= " << myVector[i] << "\n";
		std::cout << myVector;
		myVector.reserve(2);
		std::cout << "after reserve < capacity: " << myVector;
		myVector.reserve(12);
		std::cout << "after reserve > capacity: " << myVector;
		myVector.resize(3, 11);
		std::cout << "after resize in less: " << myVector;
		myVector.resize(300, 11);
		std::cout << "after resize in bigger: " << myVector;
		std::cout << "index[4] = " << myVector[4] << "\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}