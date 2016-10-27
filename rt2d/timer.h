/**
 * @file timer.h
 *
 * @brief The Timer header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef TIMER_H_
#define TIMER_H_

// Include GLFW
#include <glfw3.h>

/// @brief The Timer class keeps track of time.
class Timer
{
public:
	Timer(); ///< @brief Constructor of the Timer
	virtual ~Timer(); ///< @brief Destructor of the Timer

	void start(); ///< @brief start the Timer
	void stop(); ///< @brief stop the Timer
	void pause(); ///< @brief pause the Timer
	void unpause(); ///< @brief unpause the Timer
	void paused(bool b); ///< @brief set paused or not
	/// @brief paused or not
	bool paused() { return _paused; };

	/// @brief the number of seconds passed since Timer::start()
	/// @return double time in seconds
	double seconds();

private:
	double _startTicks; ///< @brief when we started
	double _pausedTicks; ///< @brief when we paused
	bool _started; ///< @brief started or not
	bool _paused; ///< @brief paused or not
	double _tsec(); ///< @brief We know nothing. Ask glfw.
};

#endif /* TIMER_H_ */
