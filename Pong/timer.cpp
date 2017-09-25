#include "timer.h"

Timer::Timer() {
	//Initialize variables
	startTicks = 0;
	pausedTicks = 0;

	countedFrames = 0;
	avgFPS = 0.f;

	paused = false;
	started = false;
}

float Timer::calculateAvgFPS() {
	//Calculate and correct fps
	avgFPS = countedFrames / (getTicks() / 1000.f);
	if (avgFPS > 2000000)
	{
		avgFPS = 0;
	}

	return avgFPS;
}

void Timer::incrementCountedFrames() {
	countedFrames++;
}

//Start the timer
void Timer::start() {
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

//Reinitializes all variables, i.e., timer is cleared
void Timer::stop() {
	started = false;
	paused = false;

	//Clear variables
	startTicks = 0;
	pausedTicks = 0;
}

//Pauses the timer, and stores the time the timer was on for in pausedTicks
void Timer::pause() {
   //If the timer is running and isn't already paused
	if (started && !paused) {
		//Pause timer
		paused = true;

		//Calculate how long the timer was paused for (ticks)
		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
   }
}

//Unpauses timer
void Timer::unpause() {
	//If the timer is running and paused
	if (started && paused) {
		//unpause
		paused = false;

		//reset starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;

		//Reset paused ticks
		pausedTicks = 0;
	}
}

//Get timer's time in milliseconds(how long it's been running for)
//If timer is stopped, we return 0
Uint32 Timer::getTicks() {
	//The actual timer time
	Uint32 time = 0;

	//If timer is running
	if (started) {
		//If timer is paused
		if (paused) {
			//return number of ticks when the timer was paused
			time = pausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - startTicks;
		}
	}

	return time;
}

//For checking status
bool Timer::isStarted() {
	//timer is running and can be paused or unpaused
	return started;
}
bool Timer::isPaused() {
	//timer is running and paused
	return paused;
}