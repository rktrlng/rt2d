/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include <time.h>
#include "scene02.h"

Scene02::Scene02() : Scene()
{
	srand((unsigned)time(NULL));
	
	Color c = RED;
	for (int i=0; i<32; i++) {
		BoidEntity* b = new BoidEntity();
		b->addSprite("assets/boid.tga");
		c.rotate(0.2f);
		b->sprite()->color = c;
		
		boids.push_back(b);
		this->addChild(b);
	}
	
	t.start();
}


Scene02::~Scene02()
{
	int s = boids.size();
	for (int i=0; i<s; i++) {
		this->removeChild(boids[i]);
		delete boids[i];
	}
	boids.clear();
}

void Scene02::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}
}
