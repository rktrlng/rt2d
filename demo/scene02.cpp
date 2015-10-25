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

Scene02::Scene02() : SuperScene()
{
	srand((unsigned)time(NULL));
	
	// Create a UI entity
	ui_element = new BasicEntity();
	ui_element->position = Point2(SWIDTH/2, 10);
	ui_element->addSprite("assets/default.tga", 0.5f, 0.0f); // Default texture. Pivot point top middle. Pivot(0,0) is top left.
	ui_element->sprite()->size = Point2(1024, 64); // texture is 512x512. Make Mesh twice the width, 1 row of squares (512/8).
	ui_element->sprite()->uvdim = Point2(2.0f, 0.125f); // UV repeats horizontally twice, 1/8 of the height.
	ui_element->sprite()->uvoffset = Point2(0.0f, 0.125f * 7); // Show top row. UV(0,0) is bottom left.
	layers[0]->addChild(ui_element);
	
	// create Boids
	Color c = RED;
	for (int i=0; i<32; i++) {
		BoidEntity* b = new BoidEntity();
		b->addSprite("assets/boid.tga");
		b->sprite()->color = c.rotate(0.2f);
		
		boids.push_back(b);
		layers[0]->addChild(b);
	}
}


Scene02::~Scene02()
{
	int s = boids.size();
	for (int i=0; i<s; i++) {
		layers[0]->removeChild(boids[i]);
		delete boids[i];
		boids[i] = NULL;
	}
	boids.clear();
	
	layers[0]->removeChild(ui_element);
	delete ui_element;
}

void Scene02::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);
	
	// ###############################################################
	// ui_element uvoffset
	// ###############################################################
	static float xoffset = 0.0f;
	xoffset += deltaTime / 2;
	if (input()->getKey( GLFW_KEY_SPACE )) {
		xoffset = 0.0f;
	}
	ui_element->sprite()->uvoffset.x = xoffset;
}
