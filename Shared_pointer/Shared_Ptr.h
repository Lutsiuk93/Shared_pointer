#pragma once
#include "Counter.h"
#include <utility>

template <typename T>
class Shared_Ptr
	{
	private:
		T* ptr;
		Counter* counter;

	public:
		Shared_Ptr() : ptr(nullptr), counter(nullptr)
			{
			}
		Shared_Ptr(T* Ptr) : ptr(Ptr), counter(new Counter)
			{
			}

		Shared_Ptr(const Shared_Ptr& Sptr) : ptr(Sptr.ptr), counter(Sptr.counter)
			{
			if (Sptr)
				{
				++* counter;
				}
			}

		Shared_Ptr(Shared_Ptr&& Sptr) noexcept : ptr(Sptr.ptr), counter(Sptr.counter)
			{
				Sptr.ptr = nullptr;
				Sptr.counter = nullptr;
			}

		Shared_Ptr& operator= (const Shared_Ptr& Sptr)
			{
			if (&Sptr == this)
				{
				return *this;
				}

			ptr = Sptr.ptr;
			counter = Sptr.counter;

			if (Sptr)
				{
				++* counter;
				}

			return *this;
			}

		Shared_Ptr& operator= (T* Ptr)
			{
			if (use_count == 1)
				{
				delete ptr;
				}
			else
				{
				--* counter;
				counter = new Counter;
				}

			ptr = Ptr;

			return *this;

			}

		Shared_Ptr& operator= (Shared_Ptr&& Sptr) noexcept
			{
			if (*Sptr == this)
				{
				return *this;
				}

			if (use_count == 1)
				{
				delete ptr;
				}

			ptr = Sptr.ptr;
			counter = Sptr.counter;
			Sptr.ptr = nullptr;
			Sptr.counter = nullptr;

			}

		~Shared_Ptr()
			{
			if (!unique() && use_count() == 1)
				{
				delete ptr;
				delete counter;
				}
			else if (!unique())
				{
				--* counter;
				}
			}

		int use_count() const
			{
			if (!unique())
				{
				return counter->getCount();
				}
			else
				{
				return 0;
				}
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
			return !(ptr == nullptr);
			}


	};

template <typename T, typename... Args>
std::enable_if_t<!std::is_array<T>::value, Shared_Ptr<T>>
make_shared(Args&&... args)
	{
	return Shared_Ptr<T>(new T(std::forward<Args>(args)...));
	}

template <typename T>
Shared_Ptr<T> make_shared(std::size_t size)
	{
	return Shared_Ptr<T>(new T[size]());
	}