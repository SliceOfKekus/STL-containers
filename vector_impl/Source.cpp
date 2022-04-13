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
	TestRunner tr;
	RUN_TEST(tr, ConstructorsTests);
	RUN_TEST(tr, ElementAccessTests);
	RUN_TEST(tr, IteratorsTests);
	RUN_TEST(tr, CapacityTests);
	RUN_TEST(tr, ModifiersTests);
}