/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE06_H
#define SCENE06_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene06: public SuperScene
{
public:
	Scene06();
	virtual ~Scene06();

	virtual void update(float deltaTime);

private:
	// full, single circle (hexagon)
	BasicEntity* circle_container;
	Timer t;

	// a single hexagon with its elements
	BasicEntity* hexagon; // container
	BasicEntity* northeast;
	BasicEntity* north;
	BasicEntity* northwest;
	BasicEntity* southwest;
	BasicEntity* south;
	BasicEntity* southeast;

	// a container with n elements
	BasicEntity* segments_container;
	std::vector<BasicEntity*> elements;
	Timer ct;
};

#endif /* SCENE06_H */
