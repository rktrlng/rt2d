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
	srand((unsigned)time(nullptr));

	text[0]->message("Scene12: PixelSprite");

	timer.start();

	const unsigned int pixelsize = 8;

	// Create backgroundcanvas. Fill with opaque gradient.
	// This will stay the background canvas. No need to update it.
	backgroundcanvas = new Canvas(pixelsize);
	layers[0]->addChild(backgroundcanvas);
	for (int y = 0; y < backgroundcanvas->height(); y++) {
		for (int x = 0; x < backgroundcanvas->width(); x++) {
			backgroundcanvas->setPixel(x, y, RGBAColor(0, y, 0, 255));
		}
	}

	// Create canvas. Default color is transparent black.
	// This is the one where we clear/draw pixels in update.
	canvas = new Canvas(pixelsize);
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

	// ###############################################################
	line.position = Point2i(canvas->width() / 2, canvas->height() / 2);

	// ###############################################################
	circle.createCircle(12, YELLOW);
	circle.position = Point2i(canvas->width() / 2, canvas->height() / 2);
}


Scene12::~Scene12()
{
	layers[0]->removeChild(canvas);
	delete canvas;
	layers[0]->removeChild(backgroundcanvas);
	delete backgroundcanvas;

	sprite.pixels.clear();
	bob.pixels.clear();
	line.pixels.clear();
	circle.pixels.clear();
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
		spr = sprite.rotated(d);
		spr.position = Pointi((canvas->width() / 4)*3, canvas->height() / 2);
		d += HALF_PI / 16;
		if (d > TWO_PI) { d -= TWO_PI; }
		canvas->drawSprite(spr);

		// draw line
		static float a = TWO_PI;
		static Vector2f vec = Vector2f(36,0);
		canvas->clearSprite(line);
		line.pixels.clear(); // empty pixels array before creating new line
		line.createLine(vec, GREEN); // vec, color
		a -= PI / 60; if (a < 0) { a += TWO_PI; }
		vec.rotation(a);
		canvas->drawSprite(line);

		// draw circle
		canvas->clearSprite(circle);
		canvas->drawSprite(circle);

		// draw bob
		Vector2i vel = Vector2i((int)(rand()%3)-1, (int)(rand()%3)-1);
		if (bob.position.x < 0 || bob.position.x > canvas->width()) {
			bob.position.x = canvas->width() / 2;
		}
		if (bob.position.y < 0 || bob.position.y > canvas->height()) {
			bob.position.y = canvas->height() / 2;
		}
		bob.position += vel;
		canvas->drawSprite(bob);

		// restart frametimer
		timer.start();
	}
}
