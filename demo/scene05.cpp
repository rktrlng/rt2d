/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "scene05.h"

Scene05::Scene05() : SuperScene()
{
	t.start();
	
	text[0]->message("Scene05: Dynamic PixelBuffer from file.tga");
	//text[1]->message("");
	text[2]->message("<ESC> quit demo");
	text[3]->message("<SPACE> pause animation");
	
	// container for Sprite with custom Texture
	sprite_container = new BasicEntity();
	sprite_container->position = Point2(SWIDTH/2, SHEIGHT/2);
	sprite_container->scale = Point2(5.0f, 5.0f);

	dynamic_sprite = new Sprite();
	dynamic_sprite->setupSpriteTGAPixelBuffer("assets/polar.tga");
	sprite_container->addSprite(dynamic_sprite);

	layers[0]->addChild(sprite_container);
}


Scene05::~Scene05()
{
	layers[0]->removeChild(sprite_container);
	
	delete sprite_container;
	delete dynamic_sprite;
}

void Scene05::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);
	
	// ###############################################################
	// sprite_container
	// ###############################################################
	sprite_container->rotation += PI / 16 * deltaTime;
	sprite_container->sprite()->uvoffset += Point2(deltaTime/8, deltaTime/8);
	
	// pause timer when SPACE is pressed
	if (input()->getKey( GLFW_KEY_SPACE )) {
		t.pause();
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		t.unpause();
	}
	
	if (t.seconds() > 0.05f) {
		PixelBuffer* buffer = dynamic_sprite->texture()->pixels();
		rotatePixels(buffer);
		t.start();
	}
}

void Scene05::rotatePixels(PixelBuffer* pixels)
{
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		for (long x=0; x<pixels->width; x++) {
			int r = pixels->data[counter+0];
			int g = pixels->data[counter+1];
			int b = pixels->data[counter+2];

			Color color = Color(r/255.0f, g/255.0f, b/255.0f);
			color.rotate(0.1);
			
			pixels->data[counter+0] = color.r * 255;
			pixels->data[counter+1] = color.g * 255;
			pixels->data[counter+2] = color.b * 255;
			if (pixels->bitdepth == 4) {
				pixels->data[counter+3] = 1.0f;
			}
			
			counter += pixels->bitdepth;
		}
	}
	pixels->filter = 1;
}
