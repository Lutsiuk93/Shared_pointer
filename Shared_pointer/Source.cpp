#include "Shared_Ptr.h"
#include <iostream>

int main()
	{
	Shared_Ptr<int> a = make_shared<int>(10);
	std::cout << *a;
	return 1;
	}