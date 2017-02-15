/**
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	this->addSprite(AUTOGENWHITE); // 32x32
	this->scale = Point2(SWIDTH/32.0f, SHEIGHT/32.0f); // like a canvas

	this->sprite()->fragmentshader("assets/slimshady.frag");
	this->sprite()->vertexshader("assets/slimshady.vert");

	this->sprite()->customParams[0] = Point3(1280.0f, 720.0f, 1.0f); // resolution
	this->sprite()->customParams[1] = Point3(1.0f, 1.0f, 1.0f);
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	static float total = 1.0f;
	total += deltaTime;
	this->sprite()->customParams[1] = Point3(total, total, total);

	// ###############################################################
	// Rotate
	// ###############################################################
/*
	this->rotation.z += HALF_PI * deltaTime; // 90 deg/sec
	if (this->rotation.z > TWO_PI) {
		this->rotation.z -= TWO_PI;
	}
*/
}
