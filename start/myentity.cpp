/**
 * This class describes MyEntity behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	// ###############################################################
	// Rotate
	// ###############################################################
	this->rotation += HALF_PI * deltaTime; // 90 deg/sec
	if (this->rotation > TWO_PI) {
		this->rotation -= TWO_PI;
	}
}
