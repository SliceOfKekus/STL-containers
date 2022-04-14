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
		size_t size = 4;
		vector<int> a(size);
		const vector<int> b{0, 1, 2, 3};

		for (size_t i = 0; i < size; ++i)
		{
			a[i] = static_cast<int>(i);
		}

		Assert(a.at(0) == 0 && a.at(1) == 1
			&& a.at(2) == 2 && a.at(3) == 3,
			"at() vector method.");
		Assert(b.at(0) == 0 && b.at(1) == 1
			&& b.at(2) == 2 && b.at(3) == 3,
			"at() vector method.");
		try
		{
			a.at(size);
			Assert(false, "at() method throw exception");
		}
		catch (std::out_of_range& ex)
		{
			std::cerr << ex.what() << '\n';
		}
		catch (...)
		{
			Assert(false, "at() throw exception but not std::out_of_range.");
		}

		Assert(a[0] == 0 && a[1] == 1
			&& a[2] == 2 && a[3] == 3,
			"operator[] vector.");
	}
	{
		vector<int> a = { 1, 2, 3, 4, 5 };
		const vector<int> b = { 1, 2 };
		Assert(a.front() == 1 && a.back() == 5
			&& b.front() == 1 && b.back() == 2,
			"front() and back() methods");
	}
	{
		vector<int> a = { 1, 2, 3 };
		const vector<int> b = { 1, 2, 3 };
		auto ptr = a.data();
		auto _ptr = b.data();
		std::stringstream os, _os;

		for (size_t i = 0; i < a.size(); ++i)
		{
			os << ptr[i];
			_os << _ptr[i];
		}

		Assert(os.str() == "123" && _os.str() == "123",
			"data() method.");
	}
}

#define TYPE(x) #x

void IteratorsTests()
{
	{
		vector<int> a = { 1, 2, 3 };
		const vector<int> b;

		Assert(a.data() == a.begin().Ptr() && a.data() + 1 == (a.begin() + 1).Ptr()
			&& a.data() + 2 == (a.begin() + 2).Ptr() && a.data() + 3 == a.end().Ptr(),
			"begin/end methods");
		Assert(b.cbegin().Ptr() == b.data() && b.data() == b.cend().Ptr(),
			"cbegin/cend methods.");

		std::stringstream os;
		for (auto it = a.begin(); it != a.end(); ++it)
		{
			os << *it;
		}
		Assert(os.str() == "123",
			"iterator operator*/operator++(int junk) + comparing iters.");
	}
}

void CapacityTests()
{
	{
		vector<int> a = { 1 }, b;

		Assert(!a.empty() && b.empty(),
			"empty method.");
		Assert(a.size() == 1 && b.size() == 0,
			"size method.");
	}
	{
		vector<int> a = { 1, 2, 3, 4, 5, 6 };
		std::stringstream os;
		a.shrink_to_fit();

		for (size_t i = 0; i < a.capacity(); ++i)
		{
			os << a[i];
		}

		Assert(os.str() == "123456" 
			&& a.size() == a.capacity(),
			"shrink_to_fit.");
	}
	{
		vector<int> a;
		a.reserve(100);

		Assert(a.size() == 0 && a.capacity() == 100,
			"reserve method.");
	}
}

void ModifiersTests()
{
	{
		vector<int> a = { 1, 1 };

		a.clear();
		Assert(a.size() == 0 && a.capacity() == 3
			&& a.begin() == a.end(),
			"clear method.");
	}
	{
		std::stringstream os;
		vector<int> a = {1, 2};
		a.insert(a.begin(), 0);

		for (size_t i = 0; i < a.size(); ++i)
		{
			os << a[i];
		}
		Assert(os.str() == "012",
			"insert(begin(), val).");
		
		os.str("");
		a.insert(a.end(), 3);

		for (size_t i = 0; i < a.size(); ++i)
		{
			os << a[i];
		}
		Assert(os.str() == "0123",
			"insert(end(), val).");

		os.str("");
		a.insert(++a.begin(), 3);

		for (size_t i = 0; i < a.size(); ++i)
		{
			os << a[i];
		}
		Assert(os.str() == "03123",
			"insert(somewhere inside array, val).");


	}
}