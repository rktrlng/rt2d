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
	
	text[0]->message("Scene02: Lists of n Things");
	//text[1]->message("");
	text[2]->message("<ESC> next scene");
	
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
}

void Scene02::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);
}
