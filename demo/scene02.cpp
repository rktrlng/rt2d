/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene02.h"

Scene02::Scene02() : SuperScene()
{
	srand((unsigned)time(NULL));

	text[0]->message("Scene02: Lists of n Things (Entities)");

	// create Boids
	int amount = 2500;
	for (int i=0; i<amount; i++) {
		BoidEntity* b = new BoidEntity();
		b->addSprite("assets/boid.tga");
		/*
		static HSVColor hsv = HSVColor(0.0f, 1.0f, 1.0f); // initially red
		RGBAColor rgb = Color::HSV2RGBA(hsv);
		b->sprite()->color = rgb;
		hsv.h += 1.0f/amount;
		if (hsv.h > 1.0f) { hsv.h -= 1.0f; }
		*/
		static RGBAColor rgb = RED;
		b->sprite()->color = rgb;
		//rgb = Color::rotate(rgb, 1.0f/amount);
		rgb = Color::rotate(rgb, 0.004f);

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
