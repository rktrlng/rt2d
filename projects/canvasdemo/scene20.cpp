/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene20.h"

Scene20::Scene20() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene20: Mandelbrot");

	//text[4]->message("<SPACE> reset particles");
	//text[7]->message("FPS: ---");

	timer.start();

	// create Canvas
	canvas = new Canvas(2); // pixelsize
	canvas->sprite()->texture()->pixels()->wrap = 1;
	canvas->sprite()->texture()->pixels()->filter = 0;
	layers[0]->addChild(canvas);

	w = canvas->width();
	h = canvas->height();

	aspectratio = (float)SWIDTH/(float)SHEIGHT;
	zoom = 1.3f;

	this->drawMandelBrot(0.8f, 0.0f, zoom);
}

Scene20::~Scene20()
{
	layers[0]->removeChild(canvas);
	delete canvas;
}

void Scene20::update(float deltaTime)
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

	// some arbitrary x, y and zoom factors
	static float counter = 0.0f;
	float tsec = timer.seconds();
	if (tsec > 0.01f - deltaTime) { // 0.01f = 100fps
		counter += 0.0075f;
		float speed = cos(counter);
		zoom = cos(speed) * 0.5f;
		float x = sin(counter);
		float y = cos(counter);
		this->drawMandelBrot(-x, y, zoom);
		timer.start();
	}
}

void Scene20::drawMandelBrot(float focusx, float focusy, float zoom)
{
	int maxiterations = 80;
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			float a = map(x, 0, w, -(zoom*aspectratio)-focusx, (zoom*aspectratio)-focusx);
			float b = map(y, 0, h, -(zoom)-focusy, (zoom)-focusy);

			float ca = a;
			float cb = b;

			int n = 0;

			while (n < maxiterations) {
			  float aa = a * a - b * b;
			  float bb = 2 * a * b;
			  a = aa + ca;
			  b = bb + cb;
			  if (a * a + b * b > 16) {
				break;
			  }
			  n++;
			}

			int bright = map(n, 0, maxiterations, 0, 255);
			if (n == maxiterations) { bright = 0; }

			float v = map(bright, 0, 255, 0, 1);
			HSVColor hsv = HSVColor(v, 1.0f, 1.0f);
			RGBAColor rgb = Color::HSV2RGBA(hsv);
			if (n == maxiterations) { rgb = BLACK; }

			canvas->setPixel(x,y,rgb);
		}
	}
}
