/**
 * This class describes MyScene behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	camera()->perspective();

	t.start();

	int amount = 16;
	int xstep = SWIDTH/(amount+1);
	for (int i = 0; i < amount; i++) {
		Cube* cube = new Cube();
		cube->position.x = i*xstep;
		cube->position.x -= (SWIDTH/2)-xstep;
		//cube->scale = Point3(0.5f,0.5f,0.5f);
		cubes.push_back(cube);

		this->addChild(cube);
	}

	entity = new BasicEntity();
	entity->addSprite("assets/pencils.tga");
	entity->rotation.x = PI;
	this->addChild(entity);
}


MyScene::~MyScene()
{
	size_t s = cubes.size();
	for (size_t i = 0; i < s; i++) {
		this->removeChild(cubes[i]);
		delete cubes[i];
	}

	this->removeChild(entity);
	delete entity;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Rotate all cubes
	// ###############################################################
	static float counter = 0;
	size_t s = cubes.size();
	for (size_t i = 0; i < s; i++) {
		cubes[i]->position.y = sin(i+counter)*225;
		cubes[i]->position.z = cos(i+counter)*225;
	}
	counter += deltaTime;

	// ###############################################################
	// First Person Shooter camera controls
	// ###############################################################
	this->fpsCam(deltaTime);

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}
}

void MyScene::fpsCam(float deltaTime)
{
	float movspeed = 500.0f; // units per second
	float rotspeed = PI / 4; // radians per second
	float rollspeed = PI / 400; // radians per second

	// Use keyboard to move and look around
	// tilt
	if (input()->getKey(KeyCode::Up)) 	{ camera()->tilt(deltaTime * rotspeed); }
	if (input()->getKey(KeyCode::Down))	{ camera()->tilt(deltaTime * -rotspeed); }
	// pan
	if (input()->getKey(KeyCode::Left)) 	{ camera()->pan(deltaTime * rotspeed); }
	if (input()->getKey(KeyCode::Right))	{ camera()->pan(deltaTime * -rotspeed); }
	// roll
	if (input()->getKey('I'))	{ camera()->roll(deltaTime * rollspeed); }
	if (input()->getKey('O'))	{ camera()->rotation.z = 0.0f; }
	if (input()->getKey('P'))	{ camera()->roll(deltaTime * -rollspeed); }
	// dolly
	if (input()->getKey('W'))	{ camera()->dolly(deltaTime * movspeed / 2.0f); }
	if (input()->getKey('S'))	{ camera()->dolly(deltaTime * -movspeed / 2.0f); }
	// track
	if (input()->getKey('A'))	{ camera()->track(deltaTime * -movspeed); }
	if (input()->getKey('D'))	{ camera()->track(deltaTime * movspeed); }
	// boom
	if (input()->getKey('Q'))	{ camera()->boom(deltaTime * movspeed); }
	if (input()->getKey('Z'))	{ camera()->boom(deltaTime * -movspeed); }

	//camera()->fov(45.0f - 5 * glfwGetMouseWheel());
}
