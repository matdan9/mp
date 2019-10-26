#include "Time.h"

Time::Time(){
	startTime = std::chrono::high_resolution_clock::now();
	lastTime = startTime;
}

Time::~Time(){

}

double Time::getLapsTime() {
	auto currentTime = std::chrono::high_resolution_clock::now();
	double retVal = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
	lastTime = currentTime;
	return retVal;
}

double Time::getRanTime() {
	auto diff = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::nanoseconds>(diff - startTime).count();
}

void Time::resetTimer() {
	startTime = std::chrono::high_resolution_clock::now();
}