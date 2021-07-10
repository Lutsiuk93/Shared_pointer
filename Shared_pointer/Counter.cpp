#include "Counter.h"

Counter::Counter() : count(1)
	{
	};

Counter& Counter::operator ++()
	{
	this->count += 1;
	return *this;
	};

Counter& Counter::operator --()
	{
	this->count -= 1;
	return *this;
	}
	
int Counter::getCount() const
	{
	return count;
	}


