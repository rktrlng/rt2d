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
	
	for (int i=0; i<16; i++) {
		BoidEntity* b = new BoidEntity();
		b->addSprite("assets/boid.tga");
		
		boids.push_back(b);
		this->addChild(b);
		
		Sprite* s = b->sprite();
		switch (i)
		{
			case 0:
				s->color = Color(0.4f, 0.4f, 0.4f, 1.0f);
				break;
			case 1:
				s->color = Color(0.0f, 0.0f, 1.0f, 1.0f);
				break;
			case 2:
				s->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
				break;
			case 3:
				s->color = Color(0.0f, 1.0f, 1.0f, 1.0f);
				break;
			case 4:
				s->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			case 5:
				s->color = Color(1.0f, 0.0f, 1.0f, 1.0f);
				break;
			case 6:
				s->color = Color(1.0f, 1.0f, 0.0f, 1.0f);
				break;
			case 7:
				s->color = Color(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			default:
				s->color = Color(); // default color (white)
				break;
		}
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
	
	// ###############################################################
	// Nervous red Boid
	// ###############################################################
	if (t.seconds() > 0.25f) {
		boids[4]->velocity = Vector2((rand()%500)-250, (rand()%500)-250);
		t.start();
	}
}
