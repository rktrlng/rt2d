/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "scene09.h"

Scene09::Scene09() : SuperScene()
{
	t.start();

	text[0]->message("Scene09: Spritebatch");
	text[5]->message("<Arrow keys> move camera");
	text[6]->message("<leftclick> random sprite");
	//text[13]->message("<rightclick> dark");
	//text[14]->message("<middleclick> gray");

	gridwidth = 24;
	gridheight = 16;
	cellwidth = 64;
	cellheight = 64;

	// create grid
	grid = new BasicEntity();
	grid->addGrid("assets/default.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);

	layers[0]->addChild(grid);

	//int xgridpos = (SWIDTH/2) - ((gridwidth*cellwidth) / 2);
	//int ygridpos = (SHEIGHT/2) - ((gridheight*cellheight) / 2 );
	//grid->position = Point2(xgridpos, ygridpos);

	// fill Sprites with random number
	int counter = 0;
	for (int x=0; x<gridwidth; x++) {
		for (int y=0; y<gridheight ; y++) {
			grid->sprites()[counter]->frame(rand()%16);
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
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// ###############################################################
	// - link mouse to camera
	// - account for camera offset (center of the screen)
	// - update mouse cursor text
	// ###############################################################
	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH/2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT/2;
	std::string cursortxt = "cursor (";
	cursortxt.append(std::to_string(mousex));
	cursortxt.append(",");
	cursortxt.append(std::to_string(mousey));
	cursortxt.append(")");
	text[9]->message(cursortxt);
/*
	if (t.seconds() > 0.25f) {
		std::vector<Sprite*> sprites = grid->sprites();
		int s = sprites.size();
		for (int i = 0; i < s; i++) {
			sprites[i]->frame(rand()%16);
		}
		t.start();
	}
*/
	// loop over grid
	std::vector<Sprite*> sprites = grid->sprites();
	int counter = 0;
	for (int x=0; x<gridwidth; x++) {
		for (int y=0; y<gridheight ; y++) {
			Point2 pos = sprites[counter]->spritepos;

			int halfwidth = cellwidth/2;
			int halfheight = cellheight/2;
			int left = pos.x - halfwidth;
			int right = pos.x + halfwidth;
			int top = pos.y - halfheight;
			int bottom = pos.y + halfheight;

			if ( mousex > left && mousex < right && mousey > top && mousey < bottom ) {
				sprites[counter]->color.a = 192;
				if (input()->getMouseDown( 0 )) {
					sprites[counter]->frame(rand()%16);
				}
			} else {
				sprites[counter]->color.a = 255;
			}
			counter++;
		}
	}

/*
	// ###############################################################
	// Check mouseover for each cell
	// ###############################################################
	int s = cells.size();
	for (int i=0; i<s; i++) {
		Cell* c = cells[i];
		Point2 pos = c->entity->worldpos();

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
*/
	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 300.0f; // 300 units / second

	// Right and Down vector
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);

	// Move up
	if (input()->getKey( GLFW_KEY_UP )) {
		camera()->position -= up * deltaTime * speed;
	}
	// Move down
	if (input()->getKey( GLFW_KEY_DOWN )) {
		camera()->position += up * deltaTime * speed;
	}
	// Strafe right
	if (input()->getKey( GLFW_KEY_RIGHT )) {
		camera()->position += right * deltaTime * speed;
	}
	// Strafe left
	if (input()->getKey( GLFW_KEY_LEFT )) {
		camera()->position -= right * deltaTime * speed;
	}
}
