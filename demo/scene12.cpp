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

	RGBAColor color = BLUE;
	// left
	sprite.pixels.push_back(Pixel(Point_t<int>(-3, -3), RED));
	sprite.pixels.push_back(Pixel(Point_t<int>(-3, -2), color));
	sprite.pixels.push_back(Pixel(Point_t<int>(-3, -1), color));
	sprite.pixels.push_back(Pixel(Point_t<int>(-3,  0), color));
	sprite.pixels.push_back(Pixel(Point_t<int>(-3,  1), color));
	sprite.pixels.push_back(Pixel(Point_t<int>(-3,  2), color));
	sprite.pixels.push_back(Pixel(Point_t<int>(-3,  3), GREEN));

	// top
	sprite.pixels.push_back(Pixel(Point_t<int>(-2,  3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>(-1,  3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 0,  3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 1,  3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 2,  3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 3,  3), MAGENTA));

	// right
	sprite.pixels.push_back(Pixel(Point_t<int>( 3, -3), YELLOW));
	sprite.pixels.push_back(Pixel(Point_t<int>( 3, -2), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 3, -1), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 3,  0), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 3,  1), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 3,  2), color));

	// bottom
	sprite.pixels.push_back(Pixel(Point_t<int>(-2, -3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>(-1, -3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 0, -3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 1, -3), color));
	sprite.pixels.push_back(Pixel(Point_t<int>( 2, -3), color));

	// outside
	/*
	sprite.pixels.push_back(Pixel(Point_t<int>(-4, -4), RED));
	sprite.pixels.push_back(Pixel(Point_t<int>( 4, -4), YELLOW));
	sprite.pixels.push_back(Pixel(Point_t<int>(-4,  4), GREEN));
	sprite.pixels.push_back(Pixel(Point_t<int>( 4,  4), MAGENTA));

	sprite.pixels.push_back(Pixel(Point_t<int>(-5, -5), RED));
	sprite.pixels.push_back(Pixel(Point_t<int>( 5, -5), YELLOW));
	sprite.pixels.push_back(Pixel(Point_t<int>(-5,  5), GREEN));
	sprite.pixels.push_back(Pixel(Point_t<int>( 5,  5), MAGENTA));
	*/
	sprite.pixels.push_back(Pixel(Point_t<int>(-6, -6), RED));
	sprite.pixels.push_back(Pixel(Point_t<int>( 6, -6), YELLOW));
	sprite.pixels.push_back(Pixel(Point_t<int>(-6,  6), GREEN));
	sprite.pixels.push_back(Pixel(Point_t<int>( 6,  6), MAGENTA));

	sprite.position = Point_t<int>(framebuffer->width / 2, framebuffer->height / 2);

	// ###############################################################
	RGBAColor bobcolor = WHITE;

	// eyes
	bob.pixels.push_back(Pixel(Point_t<int>(-1,  1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 1,  1), bobcolor));
	// scalp
	bob.pixels.push_back(Pixel(Point_t<int>(-3,  3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-2,  3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-1,  3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 0,  3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 1,  3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 2,  3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 3,  3), bobcolor));
	// ears left
	bob.pixels.push_back(Pixel(Point_t<int>(-4,  2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-3,  2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 3,  2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 4,  2), bobcolor));
	// ears right
	bob.pixels.push_back(Pixel(Point_t<int>(-4,  1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-3,  1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 3,  1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 4,  1), bobcolor));
	// space under eyes
	bob.pixels.push_back(Pixel(Point_t<int>(-3,  0), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 3,  0), bobcolor));
	// neck
	bob.pixels.push_back(Pixel(Point_t<int>(-3, -1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-2, -1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-1, -1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 0, -1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 1, -1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 2, -1), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 3, -1), bobcolor));
	// second neck / belly
	bob.pixels.push_back(Pixel(Point_t<int>(-3, -2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-2, -2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-1, -2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 0, -2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 1, -2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 2, -2), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 3, -2), bobcolor));
	// feet
	bob.pixels.push_back(Pixel(Point_t<int>(-2, -3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>(-1, -3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 1, -3), bobcolor));
	bob.pixels.push_back(Pixel(Point_t<int>( 2, -3), bobcolor));



	bob.position = Point_t<int>(framebuffer->width / 2, framebuffer->height / 2);
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
	if (tsec > 0.1 - deltaTime) { // 0.1 is 100 fps
		// clear to background color
		for (long y=0; y<framebuffer->height; y++) {
			for (long x=0; x<framebuffer->width; x++) {
				framebuffer->setPixel(x, y, backgroundcolor);
			}
		}

		static float d = 0.0f;
		PixelSprite spr = sprite.rotation(d);
		d += HALF_PI / 8;
		if (d > TWO_PI) { d -= TWO_PI; }

		drawSprite(spr);

		int range = 3;
		Vector2 vel = Vector2((rand()%3)-range/2, (rand()%range)-range/2);
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
