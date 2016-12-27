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
	int pixelsize = 8;
	int border = 0; // multiples of (at least) 4
	canvas = new BasicEntity();
	canvas->position = Point2(SWIDTH/2, SHEIGHT/2);
	canvas->scale = Point2(pixelsize, pixelsize);
	layers[0]->addChild(canvas);

	// our PixelBuffer(width, height, bitdepth, filter, wrap)
	PixelBuffer* tmp = new PixelBuffer((SWIDTH/pixelsize)-border, (SHEIGHT/pixelsize)-border, 3, 0, 0);
	canvas->addDynamicSprite(tmp);
	delete tmp;

	// get the pixels from the texture and call it the global framebuffer
	framebuffer = canvas->sprite()->texture()->pixels();

	// fill framebuffer with background color
	backgroundcolor = RGBAColor(32, 32, 32, 255);

	// clear to background color
	for (long y=0; y<framebuffer->height; y++) {
		for (long x=0; x<framebuffer->width; x++) {
			framebuffer->setPixel(x, y, backgroundcolor);
		}
	}

	// ###############################################################
	int menneke[7][9] = {
		0,1,1,1,1,1,1,1,0,
		1,1,0,0,0,0,0,1,1,
		1,1,0,1,0,1,0,1,1,
		0,1,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,1,0,
		0,1,1,1,1,1,1,1,0,
		0,0,1,1,0,1,1,0,0
	};

	for (int y = 0; y < 7; y++) {
		for (int x = 0; x < 9; x++) {
			if (menneke[y][x] == 1) {
				bob.pixels.push_back(Pixel(Point_t<int>(x, y*-1), WHITE));
			}
		}
	}

	bob.position = Point_t<int>(framebuffer->width / 4, framebuffer->height / 2);

	// ###############################################################
	RGBAColor color = WHITE;
	int pixelarray[16][16] = {
		2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,2,0,0,0,0,0,0,0,0,3,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,5,0,0,0,0,0,0,0,0,4,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4
	};

	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			int value = pixelarray[y][x];
			if (value == 1) {
				color = BLUE;
			} else if (value == 2) {
				color = MAGENTA;
			} else if (value == 3) {
				color = RED;
			} else if (value == 4) {
				color = GREEN;
			} else if (value == 5) {
				color = YELLOW;
			}

			if (pixelarray[y][x] != 0) {
				sprite.pixels.push_back(Pixel(Point_t<int>(x-8, (y*-1)+8), color));
			}
		}
	}
	sprite.position = Point_t<int>(framebuffer->width / 2, framebuffer->height / 2);
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
		// draw rotating square
		static float d = 0.0f;
		PixelSprite spr = sprite.rotation(d);
		// expensive to do another rotation to clear, but cheaper than clearing full frame.
		clearSprite(sprite.rotation(d-HALF_PI/8));
		d += HALF_PI / 8;
		if (d > TWO_PI) { d -= TWO_PI; }
		drawSprite(spr);

		// draw bob
		clearSprite(bob);
		Vector2 vel = Vector2((rand()%3)-1, (rand()%3)-1);
		if (bob.position.x < 0) {
			bob.position.x = framebuffer->width / 2;
		}
		if (bob.position.x > framebuffer->width) {
			bob.position.x = framebuffer->width / 2;
		}
		if (bob.position.y < 0) {
			bob.position.y = framebuffer->height / 2;
		}
		if (bob.position.y > framebuffer->height) {
			bob.position.y = framebuffer->height / 2;
		}
		bob.position += VectorX_t<int>(round(vel.x), round(vel.y));
		drawSprite(bob);

		// restart frametimer
		timer.start();
	}
}

void Scene12::drawSprite(const PixelSprite& spr)
{
	size_t s = spr.pixels.size();
	for (size_t i = 0; i < s; i++) {
		framebuffer->setPixel(spr.pixels[i].position.x + spr.position.x, spr.pixels[i].position.y + spr.position.y, spr.pixels[i].color);
	}
}

void Scene12::clearSprite(const PixelSprite& spr)
{
	size_t s = spr.pixels.size();
	for (size_t i = 0; i < s; i++) {
		framebuffer->setPixel(spr.pixels[i].position.x + spr.position.x, spr.pixels[i].position.y + spr.position.y, backgroundcolor);
	}
}
