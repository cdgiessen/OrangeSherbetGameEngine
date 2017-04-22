#include "Time.h"

#include <iostream>

Time::Time()
{
	creationTime = Clock::now();
	currentTime = creationTime;
	previousTime = currentTime;
}


Time::~Time()
{
}

void Time::TickClock() {
	previousTime = currentTime;
	currentTime = Clock::now();
	auto diff = (currentTime - previousTime);
	deltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - previousTime);
	std::cout << "Delta t2-t1: " << deltaTime.count() << " nanoseconds" << std::endl;
}

//TODO: Make time not dumb?
double Time::GetCurrentTime() {
	return std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();
}
double Time::GetCurrentTimeInMillis() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();
}
double Time::GetCurrentTimeInNano() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime.time_since_epoch()).count();
}
	   
double Time::GetDeltaTime() {
	return std::chrono::duration_cast<std::chrono::seconds>(deltaTime).count();
}
double Time::GetDeltaTimeInMillis() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();
}
double Time::GetDeltaTimeInNano() {
	return deltaTime.count();
}