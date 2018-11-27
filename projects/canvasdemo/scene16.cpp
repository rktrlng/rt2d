/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene16.h"

Scene16::Scene16() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene16: Metaballs");

	timer.start();

	// create Canvas
	int pixelsize = 8;
	canvas = new Canvas(pixelsize);
	canvas->sprite()->texture()->pixels()->filter = 3;
	layers[0]->addChild(canvas);

	// create blobs
	const int w = canvas->width();
	const int h = canvas->height();

	for (size_t i = 0; i < 6; i++) {
		blobs.push_back(Blob(w,h));
	}
}


Scene16::~Scene16()
{
	layers[0]->removeChild(canvas);
	delete canvas;
}

void Scene16::update(float deltaTime)
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
	if (tsec > 0.05f - deltaTime) {
		// update all blobs
		size_t s = blobs.size();
		for (size_t i = 0; i < s; i++) {
			blobs[i].update();
		}

		// draw
		for (int y = 0; y < canvas->height(); y++) {
			for (int x = 0; x < canvas->width(); x++) {
				// for each pixel...
				int sum = 0;
				for (size_t i = 0; i < s; i++) {
					// look at the distance of all blobs...
					Vector2 d = Vector2( Point2(blobs[i].pos.x, blobs[i].pos.y), Point2(x, y) );
					// add all radii over their distance (the farther away, the less important)
					sum += 15.0f * (float) blobs[i].radius / d.getLength();
				}
				// determine color for this pixel
				int value = (int) sum;
				value -= 192; // darken
				if (value > 255) { value = 255; } // just clamp
				if (value < 0) { value = 0; }

				//posterize
				//value = map(value, 0, 255, 0, 8);
				//value = map(value, 0, 8, 0, 255);

				//grayscale
				RGBAColor color = RGBAColor(value, value, value, 255);
				canvas->setPixel(x, y, color);
			}
		}

		// fix center pixel
		for (size_t i = 0; i < s; i++) {
			canvas->setPixel(blobs[i].pos.x, blobs[i].pos.y, WHITE);
		}

		timer.start();
	}
}
