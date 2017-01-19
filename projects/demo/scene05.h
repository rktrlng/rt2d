/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE05_H
#define SCENE05_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene05: public SuperScene
{
public:
	Scene05();
	virtual ~Scene05();

	virtual void update(float deltaTime);

private:
	Sprite* dynamic_sprite;
	BasicEntity* sprite_container;
	Timer t;

	void negativePixels(PixelBuffer* pixels);

	int filter;
	int wrap;
	int negative;
};

#endif /* SCENE05_H */
