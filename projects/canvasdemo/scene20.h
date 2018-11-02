/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE20_H
#define SCENE20_H

#include <deque>
#include <rt2d/timer.h>
#include <rt2d/util.h>
#include <rt2d/canvas.h>
#include "superscene.h"

class Scene20: public SuperScene
{
public:
	Scene20();
	virtual ~Scene20();

	virtual void update(float deltaTime);

private:
	Canvas* canvas;
	Timer timer;

	size_t w;
	size_t h;

	void drawMandelBrot(float focusx, float focusy, float zoom);

	float aspectratio;
	double zoom;
};

#endif /* SCENE20_H */
