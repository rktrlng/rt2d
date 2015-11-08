/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	t.start();

	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;
	this->position = Point2(SWIDTH/2, SHEIGHT/2);
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	// ###############################################################
	// Color
	// ###############################################################
	if (t.seconds() > 0.0333f) {
		RGBAColor color = this->sprite()->color;
		this->sprite()->color = Color::rotate(color, 0.01f);
		t.start();
	}

	// ###############################################################
	// Rotate
	// ###############################################################
	this->rotation += HALF_PI * deltaTime; // 360 deg/sec
	if (this->rotation > TWO_PI) {
		this->rotation -= TWO_PI;
	}
}
