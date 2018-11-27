/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene08.h"

Scene08::Scene08() : SuperScene()
{
	text[0]->message("Scene08: MouseOver in world coordinates");
	text[5]->message("<Arrow keys> move camera");
	text[12]->message("<leftclick> light");
	text[13]->message("<rightclick> dark");
	text[14]->message("<middleclick> gray");

	gridwidth = 24;
	gridheight = 16;
	cellwidth = 64;
	cellheight = 64;
	border = 1;

	// create grid in the middle of the screen
	grid = new BasicEntity();
	int xgridpos = (SWIDTH/2) - (gridwidth*(cellwidth+border) / 2);
	int ygridpos = (SHEIGHT/2) - (gridheight*(cellheight+border) / 2 );
	grid->position = Point2(xgridpos, ygridpos);

	// create cells
	for (int x=0; x<gridwidth; x++) {
		for (int y=0; y<gridheight ; y++) {
			Cell* cell = new Cell();
			cell->position.x = x;
			cell->position.y = y;

			cell->entity = new BasicEntity();
			cell->entity->addSprite(AUTOGENWHITE);
			cell->entity->sprite()->size.x = cellwidth;
			cell->entity->sprite()->size.y = cellheight;
			cell->entity->sprite()->color = GRAY;

			// initial position
			cell->entity->position.x = x*(cellwidth+border);
			cell->entity->position.y = y*(cellheight+border);

			cells.push_back(cell);
			grid->addChild(cell->entity);
			layers[0]->addChild(grid);
		}
	}
}


Scene08::~Scene08()
{
	int s = cells.size();
	for (int i=0; i<s; i++) {
		layers[0]->removeChild(cells[i]->entity);
		delete cells[i]->entity;
		delete cells[i];
		cells[i] = nullptr;
	}
	cells.clear();

	delete grid;
}

void Scene08::update(float deltaTime)
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

	// ###############################################################
	// Check mouseover for each cell
	// ###############################################################
	int s = cells.size();
	for (int i=0; i<s; i++) {
		Cell* c = cells[i];
		Point2 pos = c->entity->worldposition();

		int halfwidth = cellwidth/2;
		int halfheight = cellheight/2;
		int left = pos.x - halfwidth;
		int right = pos.x + halfwidth;
		int top = pos.y - halfheight;
		int bottom = pos.y + halfheight;

		if ( mousex > left && mousex < right && mousey > top && mousey < bottom ) {
			c->entity->sprite()->color.a = 127;
			if (input()->getMouseDown( 0 )) {
				c->entity->sprite()->color = RGBAColor(192, 192, 192, 255);
			}
			if (input()->getMouseDown( 1 )) {
				c->entity->sprite()->color = RGBAColor(64, 64, 64, 255);
			}
			if (input()->getMouseDown( 2 )) {
				c->entity->sprite()->color = GRAY;
			}
		} else {
			c->entity->sprite()->color.a = 255;
		}
	}
/*
	// ###############################################################
	// Update Entity position if we change cell position in grid
	// ###############################################################
	for (int i=0; i<s; i++) {
		int x = cells[i]->position.x;
		int y = cells[i]->position.y;
		cells[i]->entity->position.x = x*(cellwidth+border);
		cells[i]->entity->position.y = y*(cellheight+border);
	}
*/
}
