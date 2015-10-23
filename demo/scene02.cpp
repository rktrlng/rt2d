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
	
	ui_element = new BasicEntity();
	ui_element->position = Point2(10,10);
	ui_element->addSprite("assets/default.tga", 0.0f, 0.0f);
	Sprite* s = ui_element->sprite();
	s->size = Point2(1024, 64);
	s->uvdim = Point2(2.0f, 0.125f);
	this->addChild(ui_element);
	
	
	Color c = RED;
	for (int i=0; i<32; i++) {
		BoidEntity* b = new BoidEntity();
		b->addSprite("assets/boid.tga");
		b->sprite()->color = c.rotate(0.2f);
		
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
	
	this->removeChild(ui_element);
	delete ui_element;
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
	// ui_element uvoffset
	// ###############################################################
	Sprite* s = ui_element->sprite();
	static float offset = 0.0f;
	offset += deltaTime / 8;
	s->uvoffset = Point2(offset, 0.0f);
}
