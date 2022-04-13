#pragma once

#include <chrono>
#include <string>

class Timer
{
public:
	explicit Timer(const std::string&);
	~Timer();
private:
	std::string _message;
	std::chrono::steady_clock::time_point _start;
	std::chrono::steady_clock::time_point _finish;
};

#define UNIQ_ID_HELPER(atLine) newTimer_##atLine
#define UNIQ_ID(line) UNIQ_ID_HELPER(line)
#define TIMER(message)				 \
	Timer UNIQ_ID(__LINE__){message};