#include <iostream>
#include <vector>

#include "vector.h"
//profiler
#include "profile.h"
//simple unit-test framework
#include "test_runner.h"
#include "Tests.h"

int main()
{
	std::vector<int> t;
	std::vector<int> a(t.begin(), t.end());
	//std::vector<int> test(10, 2);
	//ptrdiff_t diff = test.begin()._Ptr - test.end()._Ptr;
	//
	//test.begin()._Ptr = nullptr;
	//
	//std::cout << diff << std::endl;
	//std::cout << sizeof(test) << " "
	//	<< sizeof(int) * 10;

	TestRunner tr;
	RUN_TEST(tr, ConstructorsTests);
	RUN_TEST(tr, ElementAccessTests);
	RUN_TEST(tr, IteratorsTests);
	RUN_TEST(tr, CapacityTests);
	RUN_TEST(tr, ModifiersTests);
}