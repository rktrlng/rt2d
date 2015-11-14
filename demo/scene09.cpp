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

	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 500.0f; // 500 units / second

	// Right and Down vector
	Point2 right = Point2(1, 0);
	Point2 up = Point2(0, 1);
	// Direction
	Vector2 direction = Vector2(0,0);

	if (input()->getKey( GLFW_KEY_UP )) {
		direction -= up;
	}
	if (input()->getKey( GLFW_KEY_DOWN )) {
		direction += up;
	}
	if (input()->getKey( GLFW_KEY_RIGHT )) {
		direction += right;
	}
	if (input()->getKey( GLFW_KEY_LEFT )) {
		direction -= right;
	}
	direction.normalize();
	direction *= deltaTime * speed;
	camera()->position += direction;
}
