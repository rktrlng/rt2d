/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <rt2d/timer.h>

Timer::Timer()
{
	_startTicks = 0;
	_pausedTicks = 0;
	_paused = false;
	_started = false;
}

Timer::~Timer()
{

}

void Timer::start()
{
	_started = true;
	_paused = false;

	_startTicks = _tsec();
}

void Timer::stop()
{
	_started = false;
	_paused = false;
}

void Timer::pause()
{
	if( _started && !_paused ) {
		_paused = true;
		_pausedTicks = _tsec() - _startTicks;
	}
}

void Timer::unpause()
{
	if(_paused) {
		_paused = false;
		_startTicks = _tsec() - _pausedTicks;
		_pausedTicks = 0;
	}
}

void Timer::paused(bool b)
{
	if (b) {
		pause();
	} else {
		unpause();
	}
}

double Timer::seconds()
{
	if(_started) {
		if(_paused) {
			return _pausedTicks;
		} else {
			return _tsec() - _startTicks;
		}
	}

	return 0;
}

double Timer::_tsec()
{
	return glfwGetTime();
}
