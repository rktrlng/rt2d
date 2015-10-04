/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#ifndef SCENE02_H
#define SCENE02_H

#include <vector>
#include <rt2d/scene.h>
#include <rt2d/timer.h>
#include "boidentity.h"

class Scene02: public Scene
{
	public:
		Scene02();
		virtual ~Scene02();

		virtual void update(float deltaTime);
	
	private:
		std::vector<BoidEntity*> boids;
		Timer t;
};

#endif /* SCENE02_H */ 
