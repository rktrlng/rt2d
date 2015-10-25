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
	
	// change state every n seconds, pause timer when SPACE is pressed
	static int state = 0;
	if (input()->getKey( GLFW_KEY_SPACE )) {
		t.pause();
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		t.unpause();
	}
	
	if (t.seconds() > 2.0f) {
		state++;
		if (state > 4) { state = 0; }
		t.start();
	}
	
	// change pixels according to state
	float statetime = 0.02f; // 0.0167 is 60 fps
	if (rt.seconds() > statetime) {
		// get the pixels
		PixelBuffer* buff = pixel_container->sprite()->pixels();
		switch (state) {
			case 0:
				checkerPixels(buff, 4, 0);
				break;
			case 1:
				randomPixels(buff, 0);
				break;
			case 2:
				rainbowPixels(buff, 0.25f, 3);
				break;
			case 3:
				randomPixels(buff, 1);
				break;
			case 4:
				rainbowPixels(buff, 0.1f, 3);
				break;
			default:
				break;
		}
		rt.start();
	}
}

void Scene04::randomPixels(PixelBuffer* pixels, int filter)
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
	pixels->filter = filter;
}

void Scene04::rainbowPixels(PixelBuffer* pixels, float step, int filter)
{
	static Color c = Color(1.0, 0.0f, 0.0f, 1.0f);
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		c.rotate(step);
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
	pixels->filter = filter;
}

void Scene04::checkerPixels(PixelBuffer* pixels, int cellwidth, int filter)
{
	static Color color = Color(1.0, 1.0f, 1.0f, 1.0f);
	int swapper = 1;
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		if (y%cellwidth == 0) { swapper *= -1; }
		for (long x=0; x<pixels->width; x++) {
			if (x%cellwidth == 0) { swapper *= -1; }
			
			if (swapper == 1) { color = RED; }
			if (swapper == -1) { color = YELLOW; }
			
			pixels->data[counter+0] = color.r * 255;
			pixels->data[counter+1] = color.g * 255;
			pixels->data[counter+2] = color.b * 255;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = color.a * 255;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = filter;
}
