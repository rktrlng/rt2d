/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE22_H
#define SCENE22_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

struct Light {
	Point2 position;
	Vector2 velocity;
};

class Scene22: public SuperScene
{
public:
	Scene22();
	virtual ~Scene22();

	virtual void update(float deltaTime);

private:
	BasicEntity* field;
	Light light;

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;

	Timer t;
};

#endif /* SCENE10_H */
