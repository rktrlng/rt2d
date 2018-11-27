/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene06a.h"

Scene06a::Scene06a() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene06a: Hexmap");
	text[4]->message("<Arrow keys> move camera");

	hexfield = new HexField();
	//hexfield->setupHexGrid("assets/defaultgray.tga", 8, 8, gridwidth, gridheight, cellradius);
	//hexfield->setupHexGrid("assets/defaultgray.tga", 8, 8, 25, 11, 64);
	hexfield->setupHexGrid("assets/hexagon256.tga", 4, 4, 25, 11, 64);

	layers[0]->addChild(hexfield);
}

Scene06a::~Scene06a()
{
	layers[0]->removeChild(hexfield);
	delete hexfield;
}

void Scene06a::update(float deltaTime)
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
	Point2 mousepos = Point2(mousex,mousey);

	std::stringstream cursortxt;
	cursortxt << "cursor (" << mousepos.x << "," << mousepos.y << ")";
	text[9]->message(cursortxt.str());

	std::vector<Sprite*> spritebatch = hexfield->spritebatch();

	// find the tile in hexfield that is closest to mousepos
	size_t activeid = hexfield->findnearest(mousepos);
	Pointi activecell = Pointi(0,0);

	// loop over grid to color the tile
	size_t counter = 0;
	for (size_t y=0; y<hexfield->rows; y++) {
		for (size_t x=0; x<hexfield->cols ; x++) {
			if ( activeid == counter ) {
				activecell = Pointi(x,y);
				spritebatch[counter]->color.a = 255;
			} else {
				spritebatch[counter]->color.a = 160;
			}
			counter++;
		}
	}

	std::stringstream postxt;
	postxt << "cell " << activeid << " (" << activecell.x << "," << activecell.y << ")";
	text[8]->message(postxt.str());

	if (input()->getMouseDown(0)) {
		//spritebatch[activeid]->color = Color::rotate(spritebatch[activeid]->color, 1.0f/hexfield->cols);
		int n = spritebatch[activeid]->frame();
		spritebatch[activeid]->frame(++n);
		spritebatch[activeid]->uvoffset += Point2(-0.375f, -0.375f); // compensate for circle UV's
	}
}
