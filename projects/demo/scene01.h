/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE01_H
#define SCENE01_H

#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene01: public SuperScene
{
public:
	Scene01();
	virtual ~Scene01();

	virtual void update(float deltaTime);

private:
	BasicEntity* default_entity;
	BasicEntity* child1_entity;
	BasicEntity* child2_entity;
	BasicEntity* animated_entity;
	BasicEntity* ui_element;

	Timer t;
};

#endif /* SCENE01_H */
