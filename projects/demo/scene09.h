/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE09_H
#define SCENE09_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene09: public SuperScene
{
public:
	Scene09();
	virtual ~Scene09();

	virtual void update(float deltaTime);

private:
	BasicEntity* grid;
	Timer t;

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;
};

#endif /* SCENE09_H */
