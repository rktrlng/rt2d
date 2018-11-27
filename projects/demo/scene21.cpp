/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 *
 * https://en.wikipedia.org/wiki/Phyllotaxis
 * http://algorithmicbotany.org/papers/abop/abop-ch4.pdf
 *
 */

#include "scene21.h"

Scene21::Scene21() : SuperScene()
{
	srand((unsigned)time(nullptr));

	t.start();

	text[0]->message("Scene21: Phyllotaxis");

	container = new BasicEntity();
	container->position = Point2(SWIDTH/2, SHEIGHT/2);
	layers[0]->addChild(container);

	m = 800; // maxdots
	n = 0; // numdot (init)
	a = 0.0f; // angle (init)
	r = 0.0f; // radius (init)
	c = 12.0f; // scale
	magic = 137.5f * DEG_TO_RAD; // 137.5f

	color = RED;
}


Scene21::~Scene21()
{
	layers[0]->removeChild(container);
	delete container;
}

void Scene21::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do
	// - Escape key stops Scene
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	//text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[5]->message("");
	text[6]->message("");
	text[10]->message(""); // clear player click count message

	if (t.seconds() > 0.01f) {
		if (n < m) {
			a = n * magic; // 137.5 deg
			r = c * sqrt(n);
			float x = r * sin(a);
			float y = r * cos(a);

			Sprite* spr = new Sprite();
			spr->setupSprite("assets/dot.tga", 0.5f, 0.5f, 1.0f, 1.0f);
			spr->color = color;
			color = Color::rotate(color, 0.004f);
			spr->spritescale = Point2(0.5f, 0.5f);
			spr->spriteposition = Point2(x, y);
			container->spritebatch().push_back(spr);

			n++;
		}
		t.start();
	}
	container->rotation.z += HALF_PI/8 * deltaTime;
}
