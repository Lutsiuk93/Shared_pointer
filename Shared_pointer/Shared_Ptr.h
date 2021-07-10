#pragma once
#include "Counter.h"

template <typename T>
class Shared_Ptr
	{
	private:
		T* ptr;
		Counter* counter;

	public:
		Shared_Ptr() : ptr(nullptr), counter(new Counter)
			{
			}
		Shared_Ptr(T* Ptr) : ptr(Ptr), counter(new Counter)
			{
			}

		Shared_Ptr(const Shared_Ptr& Sptr) : ptr(Sptr.ptr), counter(Sptr.counter)
			{
			++* counter;
			}

		Shared_Ptr(Shared_Ptr&& Sptr) : ptr(Sptr.ptr), counter(Sptr.counter)
			{
				Sptr.ptr = nullptr;
			}

		Shared_Ptr& operator= (const Shared_Ptr& Sptr)
			{
			if (&Sptr == this)
				{
				return *this;
				}

			delete ptr;
			ptr = Sptr.ptr;
			counter = Sptr.counter;
			++*counter;

			return *this;
			}

		Shared_Ptr& operator= (T* Ptr)
			{
			if (Ptr == ptr)
				{
				return *this;
				}

			delete ptr;
			ptr = Ptr;

			if (use_count() > 1)
				{
				--*counter;
				counter = new Counter;
				}

			return *this;

			}

		Shared_Ptr& operator= (Shared_Ptr&& Sptr)
			{
			if (*Sptr == this)
				{
				return *this;
				}

			delete ptr;

			ptr = Sptr.ptr;
			Sptr.ptr = nullptr;
			counter = Sptr.counter;

			}
		~Shared_Ptr()
			{
			if (counter->getCount() == 1 && !unique())
				{
				delete ptr;
				delete counter;
				}
			else
				{
				--* counter;
				}
			}

		int use_count() const
			{
			return counter->getCount();
			}

		void reset(T* Ptr)
			{

			ptr = Ptr;

			if (counter->getCount() > 1)
				{
				counter = new Counter;
				}

			}

		void swap(Shared_Ptr& Sptr)
			{
			T* temp_ptr = ptr;
			Counter* tmp_counter = counter;

			ptr = Sptr.ptr;
			counter = Sptr.counter;

			Sptr.ptr = temp_ptr;
			Sptr.counter = tmp_counter;

			}

		bool unique() const
			{
			return ptr == nullptr;
			}

		T* get() const
			{
			return ptr;
			}

		T& operator* () const
			{
			return *ptr;
			}

		T* operator-> () const
			{
			return ptr;
			}

		constexpr operator bool() const
			{
			return ptr == nullptr;
			}


	};