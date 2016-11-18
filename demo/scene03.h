/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE03_H
#define SCENE03_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "boidentity.h"
#include "basicentity.h"

class Scene03: public SuperScene
{
public:
	Scene03();
	virtual ~Scene03();

	virtual void update(float deltaTime);

private:
	Timer t;

	BasicEntity* rt2d_line;
	BasicEntity* default_line;
	BasicEntity* spaceship;

	BasicEntity* shape_container;
	std::vector<BasicEntity*> shapes;

	BasicEntity* dynamic_line;

	void updateSpaceShip(float deltaTime);
};

#endif /* SCENE03_H */
