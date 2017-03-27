/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE21_H
#define SCENE21_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene21: public SuperScene
{
public:
	Scene21();
	virtual ~Scene21();

	virtual void update(float deltaTime);

private:
	BasicEntity* container;
	RGBAColor color;

	int m; // maxdots
	int n; // numdot
	float a; // angle
	float r; // radius
	float c; // scale
	float magic; // 137.5f

	Timer t;
};

#endif /* SCENE21_H */
