#pragma once
class Counter
	{
	private:
		int count;

	public:
		Counter();
		~Counter() = default;

		Counter& operator ++();
		Counter& operator --();

		int getCount() const;

	};

