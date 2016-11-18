/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE02_H
#define SCENE02_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"
#include "boidentity.h"

class Scene02: public SuperScene
{
public:
	Scene02();
	virtual ~Scene02();

	virtual void update(float deltaTime);

private:
	std::vector<BoidEntity*> boids;
};

#endif /* SCENE02_H */
