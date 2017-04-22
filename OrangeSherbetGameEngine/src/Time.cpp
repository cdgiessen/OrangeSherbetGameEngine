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
	if (!paused) {
		previousTime = currentTime;
		currentTime = Clock::now();
		deltaTime = std::chrono::duration_cast<dur_double_nano>(currentTime - previousTime);
		//std::cout << "Delta t2-t1: " << std::chrono::duration_cast<std::chrono::nanoseconds>(deltaTime).count() << " nanoseconds" << std::endl;
	}
}

//TODO: Make time not dumb?
double Time::GetCurrentTime() {
	return std::chrono::time_point_cast<dur_double_second>(currentTime).time_since_epoch().count() - std::chrono::time_point_cast<dur_double_second>(creationTime).time_since_epoch().count();
	
}
double Time::GetCurrentTimeInMillis() {
	return std::chrono::time_point_cast<dur_double_millis>(currentTime).time_since_epoch().count() - std::chrono::time_point_cast<dur_double_millis>(creationTime).time_since_epoch().count();

}
double Time::GetCurrentTimeInNano() {
	return currentTime.time_since_epoch().count() - creationTime.time_since_epoch().count();
	
}
	   
double Time::GetDeltaTime() {
	return std::chrono::duration_cast<dur_double_second>(deltaTime).count();
}
double Time::GetDeltaTimeInMillis() {
	return std::chrono::duration_cast<dur_double_millis>(deltaTime).count();
}
double Time::GetDeltaTimeInNano() {
	return deltaTime.count();
}

bool Time::isPaused() {
	return paused;
}

void Time::Pause() {
	paused = true;
	pauseTime = Clock::now();
}

void Time::UnPause() {
	paused = false;
	previousTime += (Clock::now() - pauseTime);
}