/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene05.h"

Scene05::Scene05() : SuperScene()
{
	t.start();

	filter = 0;
	wrap = 0;
	negative = 0;

	text[0]->message("Scene05: Dynamic PixelBuffer from file.tga");

	text[4]->message("<SPACE> pause animation");

	// container for Sprite with custom Texture
	sprite_container = new BasicEntity();
	sprite_container->position = Point2(SWIDTH/2, SHEIGHT/2);
	sprite_container->scale = Point2(5.0f, 5.0f);

	dynamic_sprite = new Sprite();
	dynamic_sprite->setupSpriteTGAPixelBuffer("assets/pencils.tga", filter, wrap);
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
	// wrap and filter
	// ###############################################################
	if (input()->getKeyDown( KeyCode::W )) {
		wrap++; if (wrap > 2) { wrap = 0;}
		dynamic_sprite->texture()->pixels()->filter = filter;
		dynamic_sprite->texture()->pixels()->wrap = wrap;
	}
	if (input()->getKeyDown( KeyCode::F )) {
		filter++; if (filter > 3) { filter = 0;}
		dynamic_sprite->texture()->pixels()->filter = filter;
		dynamic_sprite->texture()->pixels()->wrap = wrap;
	}
	if (input()->getKeyDown( KeyCode::N )) {
		negative++; if (negative > 1) { negative = 0;}
		PixelBuffer* buffer = dynamic_sprite->texture()->pixels();
		buffer->filter = filter;
		buffer->wrap = wrap;
		negativePixels(buffer);
	}
	if (wrap == 0) { text[5]->message("<W> Toggle wrapping (repeat)"); }
	if (wrap == 1) { text[5]->message("<W> Toggle wrapping (mirror repeat)"); }
	if (wrap == 2) { text[5]->message("<W> Toggle wrapping (clamp)"); }
	if (filter == 0) { text[6]->message("<F> Toggle filtering (none)"); }
	if (filter == 1) { text[6]->message("<F> Toggle filtering (linear)"); }
	if (filter == 2) { text[6]->message("<F> Toggle filtering (bilinear)"); }
	if (filter == 3) { text[6]->message("<F> Toggle filtering (trilinear)"); }
	if (negative == 0) { text[7]->message("<N> Toggle to negative"); }
	if (negative == 1) { text[7]->message("<N> Toggle to positive"); }

	// ###############################################################
	// sprite_container
	// ###############################################################
	// pause timer when SPACE is pressed
	if (input()->getKey( KeyCode::Space )) {
		t.pause();
	}
	if (input()->getKeyUp( KeyCode::Space )) {
		t.unpause();
	}
	static float adder = 0.0f;
	if (!t.paused()) {
		float x = cos(adder) * 0.15f * deltaTime;
		float y = sin(adder) * 0.15f * deltaTime;
		sprite_container->sprite()->uvoffset += Point2(x, y);
		sprite_container->rotation.z += PI / 16 * deltaTime;
		adder += deltaTime;
	}
}

void Scene05::negativePixels(PixelBuffer* pixels)
{
	long counter = 0;
	for (long y=0; y<pixels->height; y++) {
		for (long x=0; x<pixels->width; x++) {
			int r = pixels->data[counter+0];
			int g = pixels->data[counter+1];
			int b = pixels->data[counter+2];

			pixels->data[counter+0] = 255 - r;
			pixels->data[counter+1] = 255 - g;
			pixels->data[counter+2] = 255 - b;

			counter += pixels->bitdepth;
		}
	}
}
