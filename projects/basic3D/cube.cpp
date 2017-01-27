/**
 * This class describes Cube behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include "cube.h"

Cube::Cube() : Entity()
{
	this->rotation.z = PI;

	// we don't really need a grid, we just want 6 sprites in a spritebatch for each side of our cube
	int gridwidth = 6;
	int gridheight = 1;
	int cellwidth = 64;
	int cellheight = 64;
	this->addGrid("assets/default.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);

	//reset all sprites
	for (int i = 0; i < gridwidth*gridheight; i++) {
		this->spritebatch()[i]->useCulling(false);
		this->spritebatch()[i]->frame(i);
		this->spritebatch()[i]->spriteposition = Point3(0.0f, 0.0f, 0.0f);
		this->spritebatch()[i]->spriterotation = Point3(0.0f, 0.0f, 0.0f);
		this->spritebatch()[i]->spritescale = Point3(1.0f, 1.0f, 1.0f);
	}

	// 1 front
	this->spritebatch()[0]->spriteposition.z = -cellwidth/2;

	// 6 back
	this->spritebatch()[5]->spriteposition.z = cellwidth/2;
	this->spritebatch()[5]->spriterotation.y = PI;

	// 3 left
	this->spritebatch()[2]->spriteposition.x = -cellwidth/2;
	this->spritebatch()[2]->spriterotation.y = HALF_PI;

	// 4 right
	this->spritebatch()[3]->spriteposition.x = cellwidth/2;
	this->spritebatch()[3]->spriterotation.y = -HALF_PI;

	// 2 top
	this->spritebatch()[1]->spriteposition.y = -cellwidth/2;
	this->spritebatch()[1]->spriterotation.x = -HALF_PI;

	// 5 bottom
	this->spritebatch()[4]->spriteposition.y = cellwidth/2;
	this->spritebatch()[4]->spriterotation.x = HALF_PI;
}

Cube::~Cube()
{

}

void Cube::update(float deltaTime)
{
	// ###############################################################
	// Rotate
	// ###############################################################
	this->rotation.y += HALF_PI * deltaTime; // 90 deg/sec
	if (this->rotation.y > TWO_PI) {
		this->rotation.y -= TWO_PI;
	}
}
