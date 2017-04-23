#pragma once

#include <chrono>

typedef std::chrono::steady_clock Clock;

typedef std::chrono::duration<double, std::nano> dur_double_nano;
typedef std::chrono::duration<double, std::milli> dur_double_millis;
typedef std::chrono::duration<double> dur_double_second;
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

	bool isPaused();
	void Pause();
	void UnPause();

	void PrintCurrentTime(); //prints current times in s, m, and n in the console. 

private:	
	bool paused = false;

	std::chrono::time_point< std::chrono::steady_clock, dur_double_nano> creationTime, currentTime, previousTime, pauseTime;
	dur_double_nano deltaTime;
};

