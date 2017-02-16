/**
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	this->addSprite(AUTOGENWHITE); // 32x32
	this->scale = Point2(SWIDTH/32.0f, SHEIGHT/32.0f); // like a canvas

	fragshaders.push_back("shaders/slimshady0.frag");
	fragshaders.push_back("shaders/slimshady1.frag");
	activeshader = 1;

	this->sprite()->customParams[0] = Point3(1280.0f, 720.0f, 1.0f); // resolution
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	// send custom params to fragment shader
	static float total = 1.0f;
	total += deltaTime;
	this->sprite()->customParams[1] = Point3(total, total, total);

	// clamp and set select shader
	if (activeshader >= 0 && activeshader < (int)fragshaders.size()) {
		this->sprite()->fragmentshader(fragshaders[activeshader]);
	}
}
