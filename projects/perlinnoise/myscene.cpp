/**
 * This class describes MyScene behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	t.start();

	srand((unsigned)time(NULL));

	// Create a PerlinNoise object with a random permutation vector generated with seed
	unsigned int seed = rand()%1000;
	//unsigned int seed = 242;
	pn = new PerlinNoise(seed);

	// container for Sprite with custom Texture
	entity = new BasicEntity();
	entity->position = Point2(SWIDTH/2, SHEIGHT/2);
	entity->scale = Point2(8.0f, 8.0f);
	// width, height, bitdepth, filter, wrap
	PixelBuffer pixels = PixelBuffer(64, 64, 3, 0, 0);
	entity->addDynamicSprite(&pixels);

	// text
	text = new Text();
	text->message("Perlin Noise. Navigate with: W/S + up/down/left/right");
	text->scale = Point2(0.5f, 0.5f);
	text->position = Point2(50, 50);

	this->addChild(entity);
	this->addChild(text);
}


MyScene::~MyScene()
{
	this->removeChild(entity);
	delete entity;

	this->removeChild(text);
	delete text;

	delete pn;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	static Point3 move = Point3(0.0f,0.0f,0.0f);

	if (input()->getKey( GLFW_KEY_W )) { move.z += deltaTime; }
	if (input()->getKey( GLFW_KEY_S )) { move.z -= deltaTime; }
	if (input()->getKey( GLFW_KEY_UP )) { move.y += deltaTime; }
	if (input()->getKey( GLFW_KEY_DOWN )) { move.y -= deltaTime; }
	if (input()->getKey( GLFW_KEY_LEFT )) { move.x -= deltaTime; }
	if (input()->getKey( GLFW_KEY_RIGHT )) { move.x += deltaTime; }


	if (t.seconds() > 0.02f) {
		PixelBuffer* pixels = entity->sprite()->texture()->pixels();

		unsigned int width = pixels->width;
		unsigned int height = pixels->height;

		long counter = 0;
		// Visit every pixel of the image and assign a color generated with Perlin noise
		for(unsigned int i = 0; i < height; ++i) {     // y
			for(unsigned int j = 0; j < width; ++j) {  // x
				// map width and height between 0 and 1
				double x = (double)j/((double)width);
				double y = (double)i/((double)height);
				double z = 0.0f;

				x += move.x;
				y += move.y;
				z += move.z;

				// pn->noise(xsize, ysize, zsize) * multiplier;
				double a = pn->noise(1 * x, 1 * y, z) * 3;
				double b = pn->noise(5 * x, 5 * y, z) * 3;
				double c = pn->noise(9 * x, 9 * y, z) * 1;

				double n = (a+b+c) / 7; // average of noises (octaves)

				// Map the values to [0, 255]
				pixels->data[counter+0] = floor(255 * n);
				pixels->data[counter+1] = floor(255 * n);
				pixels->data[counter+2] = floor(255 * n);
				if (pixels->bitdepth == 4) {
					pixels->data[counter+3] = 255; // opaque
				}
				counter += pixels->bitdepth;
			}
		}

		t.start();
	}
}
