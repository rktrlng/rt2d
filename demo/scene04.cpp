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
	
	text[0]->message("Scene04: Dynamic PixelBuffer as Texture");
	//text[1]->message("");
	text[2]->message("<ESC> quit demo");
	text[3]->message("<SPACE> pause state");
	
	// container for Sprite with custom Texture
	pixel_container = new BasicEntity();
	pixel_container->position = Point2(SWIDTH/2, SHEIGHT/2);
	pixel_container->scale = Point2(5.0f, 5.0f);
	
	// width, height, bitdepth, filter
	PixelBuffer* pixels = new PixelBuffer(128, 128, 3, 0);
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
	pixel_container->rotation += PI / 16 * deltaTime;
	//pixel_container->sprite()->uvoffset += Point2(deltaTime/8, deltaTime/8);
	
	// change state every n seconds, pause timer when SPACE is pressed
	static int state = 0;
	if (input()->getKey( GLFW_KEY_SPACE )) {
		t.pause();
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		t.unpause();
	}
	
	if (t.seconds() > 1.0f) {
		state++;
		if (state > 12) { state = 0; }
		t.start();
	}
	
	// change pixels according to state
	float statetime = 0.02f; // 0.0167 is 60 fps
	if (rt.seconds() > statetime) {
		// get the pixels
		PixelBuffer* buff = pixel_container->sprite()->texture()->pixels();
		switch (state) {
			case 0:
				randomPixels(buff, 0);
				text[3]->message("<SPACE> pause state (random unfiltered)");
				break;
			case 1:
				checkerPixels(buff, 32, WHITE, BLACK);
				text[3]->message("<SPACE> pause state (checker 32 px)");
				break;
			case 2:
				checkerPixels(buff, 16, RED, BLUE);
				text[3]->message("<SPACE> pause state (checker 16 px)");
				break;
			case 3:
				checkerPixels(buff, 8, ORANGE, CYAN);
				text[3]->message("<SPACE> pause state (checker 8 px)");
				break;
			case 4:
				checkerPixels(buff, 4, YELLOW, RED);
				text[3]->message("<SPACE> pause state (checker 4 px)");
				break;
			case 5:
				checkerPixels(buff, 2, YELLOW, BLUE);
				text[3]->message("<SPACE> pause state (checker 2 px)");
				break;
			case 6:
				checkerPixels(buff, 1, WHITE, BLACK);
				text[3]->message("<SPACE> pause state (checker 1 px)");
				break;
			case 7:
				randomPixels(buff, 0);
				text[3]->message("<SPACE> pause state (random unfiltered)");
				break;
			case 8:
				rainbowPixels(buff, 0.2f, 0);
				text[3]->message("<SPACE> pause state (rainbow 0.2 unfiltered)");
				break;
			case 9:
				rainbowPixels(buff, 0.2f, 3);
				text[3]->message("<SPACE> pause state (rainbow 0.2 filtered)");
				break;
			case 10:
				randomPixels(buff, 1);
				text[3]->message("<SPACE> pause state (random filtered)");
				break;
			case 11:
				rainbowPixels(buff, 0.05f, 0);
				text[3]->message("<SPACE> pause state (rainbow 0.05 unfiltered)");
				break;
			case 12:
				rainbowPixels(buff, 0.05f, 3);
				text[3]->message("<SPACE> pause state (rainbow 0.05 filtered)");
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
	Color c = RED;
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

void Scene04::checkerPixels(PixelBuffer* pixels, int cellwidth, Color a, Color b)
{
	Color color;
	int swapper = 1;
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		if (y%cellwidth == 0) { swapper *= -1; }
		for (long x=0; x<pixels->width; x++) {
			if (x%cellwidth == 0) { swapper *= -1; }
			
			if (swapper == 1) { color = a; }
			if (swapper == -1) { color = b; }
			
			pixels->data[counter+0] = color.r * 255;
			pixels->data[counter+1] = color.g * 255;
			pixels->data[counter+2] = color.b * 255;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = color.a * 255;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = 0;
}
