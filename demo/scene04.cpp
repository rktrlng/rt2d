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
	
	// get the pixels
	if (t.seconds() > 0.1f) {
		PixelBuffer* buff = pixel_container->sprite()->pixels();
	
		long counter = 0;
		for (long y=0; y<buff->width; y++) {
			for (long x=0; x<buff->height; x++) {
				buff->data[counter+0] = rand()%255;
				buff->data[counter+1] = rand()%255;
				buff->data[counter+2] = rand()%255;
				if (buff->bitdepth == 4) {
					buff->data[counter+3] = rand()%255;
				}
				
				counter += buff->bitdepth;
			}
		}
		
		t.start();
	}
}
