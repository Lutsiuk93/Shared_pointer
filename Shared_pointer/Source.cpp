#include "Shared_Ptr.h"
#include <iostream>

int main()
	{
	Shared_Ptr<int> a = make_shared<int>(10);
	auto b = std::move(a);

	std::cout << "after move operator : " << " | a : " << a << " | b : " << b << " | count b : " << b.use_count() << std::endl;

	auto c = b;

	std::cout << "\nafter copy operator : " << " | b : " << b << " | c : " << c << " | count b : " << b.use_count() << " | count c : " << c.use_count() << std::endl;

	auto d(std::move(c));

	std::cout << "\nafter move constructor : " << " | c : " << c << " | count c : " << c.use_count() << " | d : " << d << " | count d : " << d.use_count() << std::endl;

	auto e(d);

	std::cout << "\nafter copy constructor : " << " | d : " << d << " | count d : " << d.use_count() << " | e : " << e << " | count e : " << e.use_count() << std::endl;

	std::cout << "\nb = " << *b << " d = " << *d << " e = " << *e;
	}