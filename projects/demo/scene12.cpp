/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene12.h"

Scene12::Scene12() : SuperScene()
{
	srand((unsigned)time(NULL));

	text[0]->message("Scene12: PixelSprite");

	timer.start();

	// create Canvas
	canvas = new Canvas(8); // pixelsize
	layers[0]->addChild(canvas);

	// ###############################################################
	char menneke[63] = { // 9*7
		0,1,1,1,1,1,1,1,0,
		1,1,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,1,
		0,1,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,0,
		0,0,1,1,0,1,1,0,0
	};

	bob.init(menneke, 9, 7);
	bob.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	// ###############################################################
	char pixelarray[256] = { // 16*16
		3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,3,0,0,0,0,0,0,0,0,4,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,6,0,0,0,0,0,0,0,0,5,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,
		6,2,2,2,2,2,2,2,2,2,2,2,2,2,2,5
	};

	sprite.init(pixelarray, 16, 16);
	sprite.position = Pointi(canvas->width() / 4, canvas->height() / 2);
}


Scene12::~Scene12()
{
	layers[0]->removeChild(canvas);
	delete canvas;

	sprite.pixels.clear();
	bob.pixels.clear();
}

void Scene12::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[10]->message(""); // clear player click count message

	// ###############################################################
	// Update and draw only when it's time
	// ###############################################################
	float tsec = timer.seconds();
	if (tsec > 0.1 - deltaTime) { // 0.1 is 10 fps
		// clear bob first, we always want him 'transparent'
		canvas->clearSprite(bob);

		// draw original square
		canvas->clearSprite(sprite);
		canvas->drawSprite(sprite);

		// rotate copied square and draw that
		static float d = 0.0f;
		static PixelSprite spr = sprite;
		canvas->clearSprite(spr);
		spr = sprite.rotation(d);
		spr.position = Pointi((canvas->width() / 4)*3, canvas->height() / 2);
		d += HALF_PI / 16;
		if (d > TWO_PI) { d -= TWO_PI; }
		canvas->drawSprite(spr);

		// draw bob
		Vector2 vel = Vector2((rand()%3)-1, (rand()%3)-1);
		if (bob.position.x < 0) {
			bob.position.x = canvas->width() / 2;
		}
		if (bob.position.x > canvas->width()) {
			bob.position.x = canvas->width() / 2;
		}
		if (bob.position.y < 0) {
			bob.position.y = canvas->height() / 2;
		}
		if (bob.position.y > canvas->height()) {
			bob.position.y = canvas->height() / 2;
		}
		bob.position += Vector2i(round(vel.x), round(vel.y));
		canvas->drawSprite(bob);

		// restart frametimer
		timer.start();
	}
}
