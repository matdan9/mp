#pragma once
#include <time.h>
#include <chrono>
class Time{
private:
	std::chrono::steady_clock::time_point startTime;
	std::chrono::steady_clock::time_point lastTime;

public:
	Time();
	~Time();
	double getRanTime();
	double getLapsTime();
	void resetTimer();
};

