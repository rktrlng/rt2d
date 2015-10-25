/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "scene04.h"

Scene04::Scene04() : SuperScene()
{
	t.start();
	rt.start();
	
	// container for Sprite with custom Texture
	pixel_container = new BasicEntity();
	pixel_container->position = Point2(SWIDTH/2, SHEIGHT/2);
	pixel_container->scale = Point2(10.0f, 10.0f);
	
	// width, height, bitdepth, filter
	PixelBuffer* pixels = new PixelBuffer(64, 64, 3, 0);
	pixel_container->addDynamicSprite(pixels);
	delete pixels;
	
	// fill with rainbow
	PixelBuffer* buff = pixel_container->sprite()->pixels();
	rainbowPixels(buff);

	layers[0]->addChild(pixel_container);
}


Scene04::~Scene04()
{
	layers[0]->removeChild(pixel_container);
	delete pixel_container;
}

void Scene04::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);
	
	// ###############################################################
	// pixel_container
	// ###############################################################
	pixel_container->rotation += PI / 8 * deltaTime;
	
	static int counter = 0;
	if (t.seconds() > 1.0f) {
		counter++;
		if (counter > 1) { counter=0; }
		t.start();
	}
	
	if (rt.seconds() > 0.05f) {
		// get the pixels
		PixelBuffer* buff = pixel_container->sprite()->pixels();
		if (counter%2) {
			rainbowPixels(buff);
		} else {
			randomPixels(buff);
		}
		rt.start();
	}
}

void Scene04::randomPixels(PixelBuffer* pixels)
{
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		for (long x=0; x<pixels->width; x++) {
			pixels->data[counter+0] = rand()%255;
			pixels->data[counter+1] = rand()%255;
			pixels->data[counter+2] = rand()%255;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = rand()%255;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = 0;
}

void Scene04::rainbowPixels(PixelBuffer* pixels)
{
	static Color c = Color(1.0, 0.0f, 0.0f, 1.0f);
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		c.rotate(0.25);
		for (long x=0; x<pixels->width; x++) {
			pixels->data[counter+0] = c.r * 255;
			pixels->data[counter+1] = c.g * 255;
			pixels->data[counter+2] = c.b * 255;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = c.a * 255;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = 3;
}
