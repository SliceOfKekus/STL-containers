#include <iostream>
#include "Tests.h"

void ConstructorsTests()
{
	{
		vector<int> vec;

		Assert(!vec.size() && !vec.capacity()
			&& !vec.data(), "empty vector constructor");
	}
	{
		size_t size = 10;
		vector<int> vec(size);
		ptrdiff_t diff = vec.end().Ptr() - vec.begin().Ptr();

		Assert(vec.size() == size && vec.capacity() == (size + size / 2)
			&& (diff * sizeof(int)) == (sizeof(int) * size),
			"vector constructor with specified size.");
	}
	{
		size_t size = 10;
		int default_val = 3;
		vector<int> vec(size, default_val);

		auto sum = std::accumulate(vec.begin(), vec.end(), 0);

		Assert(vec.size() == size && vec.capacity() == (size + size / 2)
			&& sum == 30,
			"vector constructor with specified size and default value.");
	}
	{
		size_t size = 10;
		int default_val = 5;
		vector<int> vec(size, default_val);
		vector<int> temp(vec);
		
		Assert(vec == temp && vec.data() != temp.data(),
			"copy-constructor.");
		
		temp.clear();
		auto ptr = vec.data();
		temp = std::move(vec);

		Assert(temp.data() == ptr && temp.size() == size
			&& temp.capacity() == (size + size / 2)
			&& vec.data() == nullptr && vec.size() == 0
			&& vec.capacity() == 0,
			"move operator=");
	}
	{
		size_t size = 10;
		int default_val = 5;
		vector<int> vec(size, default_val);
		vector<int> temp(std::move(vec));
		ptrdiff_t diff = temp.end().Ptr() - temp.begin().Ptr();

		Assert(temp.size() == size && temp.capacity() == (size + size / 2)
			&& (diff * sizeof(int)) == (sizeof(int) * size) && vec.data() == nullptr 
			&& vec.size() == 0 && vec.capacity() == 0,
			"move constructor.");
	}
	{
		std::initializer_list<int> l = { 1, 2, 3, 4 };
		vector<int> a(l);

		int sum = std::accumulate(a.begin(), a.end(), 0);
		Assert(sum == 10 && a.size() == 4 && a.capacity() == 6,
				"initializer list<int> constructor.");
	}
	{
		size_t size = 10;
		int default_val = 5;
		vector<int> a(10, 5);
		vector<int> b(a);
		vector<int> c(a);
		std::initializer_list<vector<int>> l = { a, b ,c };

		vector<vector<int>> vec = l;
		
		Assert(vec.size() == 3 && vec.capacity() == 4,
			"initializer list constructor vec<vec<T>>.");

		for (const auto& elem : vec)
		{
			Assert(elem == a,
				"Verifying matrix correctness.");
		}
	}
	{
		size_t size = 10;
		int default_val = 1;
		vector<int> a(size, default_val);

		vector<int> b(a.begin(), a.end());

		Assert(a == b && a.data() != b.data(),
			"constructor with iterators as params.");
	}
	{
		vector<std::string> strs{ "First", "Second", "Third" };
		std::stringstream os;

		for (const auto& str : strs)
		{
			os << str << "\n";
		}

		Assert(os.str() == "First\nSecond\nThird\n",
			"Some vector containing std::string.");
	}
}

void ElementAccessTests()
{
	{
		vector<int> a;
	}
}

void IteratorsTests()
{}

void CapacityTests()
{}

void ModifiersTests()
{}