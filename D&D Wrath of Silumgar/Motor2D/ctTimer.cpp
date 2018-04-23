// ----------------------------------------------------
// ctTimer.cpp
// Fast timer with milisecons precision
// ----------------------------------------------------

#include "ctTimer.h"
#include "SDL\include\SDL_timer.h"

// ---------------------------------------------
ctTimer::ctTimer()
{
}

// ---------------------------------------------
void ctTimer::Start()
{
	started_at = SDL_GetTicks();
}

// ---------------------------------------------

void ctTimer::SetStartTime(uint32 time) {
	started_at = SDL_GetTicks() + time;
}


void ctTimer::Stop()
{
	running = false;
	stopped_at = SDL_GetTicks();
}

void ctTimer::Continue()
{
	running = true;
	if (started_at != NULL) {
		started_at += SDL_GetTicks() - stopped_at;
	}
	else {
		Start();
	}
}

// ---------------------------------------------
uint32 ctTimer::Read() const
{
	return SDL_GetTicks() - started_at;
}

// ---------------------------------------------
float ctTimer::ReadSec() const
{
	return float(SDL_GetTicks() - started_at) / 1000.0f;
}