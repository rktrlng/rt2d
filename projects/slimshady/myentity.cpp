/**
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include "myentity.h"

MyEntity::MyEntity() : Entity()
{
	fragshaders.push_back("shaders/slimshady0.frag"); // grid
	fragshaders.push_back("shaders/slimshady1.frag"); // colorshifts
	fragshaders.push_back("shaders/metaballs.frag"); // metaballs
	activeshader = 2;

	this->addSprite(AUTOGENWHITE); // 32x32
	this->scale = Point2(SWIDTH/32.0f, SHEIGHT/32.0f); // like a canvas

	this->sprite()->customParams[0] = Point3(1280.0f, 720.0f, 1.0f); // screen resolution
	this->sprite()->setPalette("assets/palette.tga"); // 256x1 sampler1D

	// metaballs positions
	for (size_t i = 2; i < 8; i++) {
		this->sprite()->customParams[i] = Point3((float)(rand()%1000)/1000, (float)(rand()%1000)/1000, 0.0);
	}
	// metaballs velocities
	for (size_t i = 0; i < 8; i++) {
		velocities.push_back(Point3((float)(rand()%1000)/1000/2, (float)(rand()%1000)/1000/2, 0.0));
	}
}

MyEntity::~MyEntity()
{

}

void MyEntity::update(float deltaTime)
{
	// send custom params to fragment shader
	static float total = 0.0f;
	total += deltaTime;
	this->sprite()->customParams[1] = Point3(total, total, total);

	for (size_t i = 2; i < 8; i++) {
		this->sprite()->customParams[i].x += velocities[i].x * deltaTime;
		this->sprite()->customParams[i].y += velocities[i].y * deltaTime;
		if (this->sprite()->customParams[i].x > 1.0) { this->sprite()->customParams[i].x = 1.0; velocities[i].x *= -1; }
		if (this->sprite()->customParams[i].x < 0.0) { this->sprite()->customParams[i].x = 0.0; velocities[i].x *= -1; }
		if (this->sprite()->customParams[i].y > 1.0) { this->sprite()->customParams[i].y = 1.0; velocities[i].y *= -1; }
		if (this->sprite()->customParams[i].y < 0.0) { this->sprite()->customParams[i].y = 0.0; velocities[i].y *= -1; }
	}

	// clamp and set select shader
	if (activeshader >= 0 && activeshader < (int)fragshaders.size()) {
		this->sprite()->fragmentshader(fragshaders[activeshader]);
	}
}
