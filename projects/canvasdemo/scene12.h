/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE12_H
#define SCENE12_H

#include <vector>
#include <rt2d/timer.h>
#include <rt2d/canvas.h>
#include <rt2d/vectorx.h>
#include "superscene.h"


class Scene12: public SuperScene
{
public:
	Scene12();
	virtual ~Scene12();

	virtual void update(float deltaTime);

private:
	PixelSprite sprite;
	PixelSprite bob;
	PixelSprite line;
	PixelSprite circle;

	Canvas* backgroundcanvas;
	Canvas* canvas;
	Timer timer;
};

#endif /* SCENE12_H */
