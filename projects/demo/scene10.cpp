/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene10.h"

Scene10::Scene10() : SuperScene()
{
	text[0]->message("Scene10: Heightmap (256x256=65536 sprites)");
	text[5]->message("<Arrow keys> move camera");

	camera()->position.x = 4500;
	camera()->position.y = 6000;

	gridwidth = 256;
	gridheight = 256;
	cellwidth = 32;
	cellheight = 32;

	RGBAColor deepwater =		RGBAColor(5, 0, 130);
	RGBAColor midwater =		RGBAColor(65, 60, 175);
	RGBAColor shallowwater =	RGBAColor(127, 127, 215);
	RGBAColor sand =			RGBAColor(215, 200, 115);
	RGBAColor grass =			RGBAColor(100, 185, 90);
	RGBAColor woods =			RGBAColor(64, 127, 64);
	RGBAColor highland =		RGBAColor(85, 85, 50);
	RGBAColor rock =			RGBAColor(100, 100, 100);
	RGBAColor snow =			RGBAColor(224, 224, 224);

	// fill field of tiles
	field = new BasicEntity();
	//field->addGrid(AUTOGENWHITE, 1, 1, gridwidth, gridheight, cellwidth, cellheight);
	field->addGrid("assets/defaultgray.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);

	heightmapsprite = new Sprite();
	heightmapsprite->setupSpriteTGAPixelBuffer("assets/heightmap256.tga", 0, 2);
	PixelBuffer* heightmap = heightmapsprite->texture()->pixels();
	int w = heightmap->width;
	int h = heightmap->height;
	int counter = 0;
	int tcounter = 0;

	Point2 offset = Point2(-100,-100);
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			Sprite* tile = field->spritebatch()[tcounter];
			unsigned char tint = heightmap->data[counter+3]; // alpha pixel

			if (tint == 255) { tile->color = deepwater; }
			if (tint == 224) { tile->color = midwater; }
			if (tint == 192) { tile->color = shallowwater; }
			if (tint == 160) { tile->color = sand; }
			if (tint == 128) { tile->color = grass; }
			if (tint == 96) { tile->color = woods; }
			if (tint == 64) { tile->color = highland; }
			if (tint == 32) { tile->color = rock; }
			if (tint == 0) { tile->color = snow; }

			if (tint == 255) { tile->frame(0); }
			if (tint == 224) { tile->frame(1); }
			if (tint == 192) { tile->frame(2); }
			if (tint == 160) { tile->frame(3); }
			if (tint == 128) { tile->frame(4); }
			if (tint == 96) { tile->frame(5); }
			if (tint == 64) { tile->frame(6); }
			if (tint == 32) { tile->frame(7); }
			if (tint == 0) { tile->frame(8); }

			counter += heightmap->bitdepth;
			tcounter++;
		}
	}
	// add field_container to Scene
	layers[0]->addChild(field);
}


Scene10::~Scene10()
{
	layers[0]->removeChild(field);
	delete field;
	delete heightmapsprite;
}

void Scene10::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do
	// - Escape key stops Scene
	// - Move Camera
	// ###############################################################
	SuperScene::update(deltaTime);
	SuperScene::moveCamera(deltaTime);

	// ###############################################################
	// - link mouse to camera
	// - account for camera offset (center of the screen)
	// - update mouse cursor text
	// ###############################################################
	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH/2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT/2;
	std::stringstream cursortxt;
	cursortxt << "cursor (" << mousex << "," << mousey << ")";
	text[9]->message(cursortxt.str());

	// loop over grid
	std::vector<Sprite*> spritebatch = field->spritebatch();
	int counter = 0;
	for (int x=0; x<gridwidth; x++) {
		for (int y=0; y<gridheight ; y++) {
			Point2 pos = spritebatch[counter]->spriteposition;

			int halfwidth = cellwidth/2;
			int halfheight = cellheight/2;
			int left = pos.x - halfwidth;
			int right = pos.x + halfwidth;
			int top = pos.y - halfheight;
			int bottom = pos.y + halfheight;

			if ( mousex >= left && mousex < right && mousey >= top && mousey < bottom ) {
				spritebatch[counter]->color.a = 192;

				std::stringstream postxt;
				postxt << "pos (" << x << "," << y << ")";
				RGBAColor color = spritebatch[counter]->color;
				postxt << " RGB: ("<< (int) color.r << "," << (int) color.g << "," << (int) color.b << ")";
				text[8]->message(postxt.str());
			} else {
				spritebatch[counter]->color.a = 255;
			}
			counter++;
		}
	}
}
