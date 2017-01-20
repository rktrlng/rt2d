/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene09.h"

Scene09::Scene09() : SuperScene()
{
	t.start();

	text[0]->message("Scene09: Spritebatch (128x128=16384 sprites)");
	text[5]->message("<Arrow keys> move camera");
	text[6]->message("<leftclick> random sprite");

	gridwidth = 128;
	gridheight = 128;
	cellwidth = 64;
	cellheight = 64;

	// create grid
	grid = new BasicEntity();
	grid->addGrid("assets/default.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);

	layers[0]->addChild(grid);

	// fill Sprites with random number
	int counter = 0;
	for (int x=0; x<gridwidth; x++) {
		for (int y=0; y<gridheight ; y++) {
			grid->spritebatch()[counter]->frame(rand()%16);
			counter++;
		}
	}

}


Scene09::~Scene09()
{
	layers[0]->removeChild(grid);
	delete grid;
}

void Scene09::update(float deltaTime)
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
	std::vector<Sprite*> spritebatch = grid->spritebatch();
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

			if ( mousex > left && mousex < right && mousey > top && mousey < bottom ) {
				spritebatch[counter]->color.a = 192;
				if (input()->getMouseDown( 0 )) {
					spritebatch[counter]->frame(rand()%16);
				}
			} else {
				spritebatch[counter]->color.a = 255;
			}
			counter++;
		}
	}
}
