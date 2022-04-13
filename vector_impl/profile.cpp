#include "profile.h"

#include <iostream>

using namespace std::chrono;

Timer::Timer(const std::string& msg)
	: _message(msg)
	, _start(steady_clock::now())
	, _finish()
{}

Timer::~Timer()
{
	_finish = std::chrono::steady_clock::now();
	std::chrono::duration duration =
		duration_cast<nanoseconds>(_finish - _start);

	std::cerr << _message << ": "
		<< duration.count() << " ns\n";
}