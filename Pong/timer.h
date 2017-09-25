//This class implements a timer. It will be used to measure FPS and to cap it

#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

//Created from Lazyfoo's SDL2 timer tutorial

class Timer {
private:
	//The clock time when the timer started
	Uint32 startTicks;

	//The ticks stored when the timer was paused
	Uint32 pausedTicks;

	//For calculating Frames Per Second
	int countedFrames;
	float avgFPS;


	//The timer status
	bool paused;
	bool started;
public:
	Timer();

	//FPS Calculations
	float calculateAvgFPS();
	void incrementCountedFrames();

	//Controls
	void start();
	void stop();
	void pause();
	void unpause();

	//Get timer's time in milliseconds(how long it's been running for)
	Uint32 getTicks();

	//For checking status
	bool isStarted();
	bool isPaused();
};

#endif // TIMER_H
