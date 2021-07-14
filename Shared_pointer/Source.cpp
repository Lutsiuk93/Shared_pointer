#include "Shared_Ptr.h"
#include <iostream>

int main()
	{
	int* a = new int(10);

	Shared_Ptr<int> b = a;

	Shared_Ptr<int> c = std::move(b);

	std::cout << b << std::endl;

	b = c;

	std::cout << *b << " " << b.use_count();

	return 1;
	}