/**
 * This class describes MyScene behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#include "myscene.h"

MyScene::MyScene() : Scene()
{

}

MyScene::~MyScene()
{

}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	float mx = input()->getMouseX();
	float my = input()->getMouseY();

	// clears previous Debug Draw calls
	ddClear();

	// Debug Draw a single line
	// x0, y0, x1, y1, color
	ddLine(SWIDTH/2, SHEIGHT/2, mx, my, YELLOW);

	// Debug Draw a circle
	// x, y, radius, color
	ddCircle(mx, my, 16, GREEN);

	// Debug Draw a square
	// x, y, width, height, color
	int border = 100;
	ddSquare(border, border, SWIDTH-(border*2), SHEIGHT-(border*2), PINK);
}
