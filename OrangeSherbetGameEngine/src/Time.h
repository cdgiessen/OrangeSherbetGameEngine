#pragma once

#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

class Time
{
public:
	Time();
	~Time();

	void TickClock();
		
	double GetCurrentTime();
	double GetCurrentTimeInMillis();
	double GetCurrentTimeInNano();

	double GetDeltaTime();
	double GetDeltaTimeInMillis();
	double GetDeltaTimeInNano();

private:	
	std::chrono::time_point< std::chrono::high_resolution_clock> creationTime, currentTime, previousTime;
	std::chrono::nanoseconds deltaTime;
};

