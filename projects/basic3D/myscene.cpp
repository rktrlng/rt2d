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
		cubes.push_back(cube);

		this->addChild(cube);
	}
	//this->camera()->position.x = (SWIDTH/2)-(xstep*1.5);

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
	static float counter = 0;
	size_t s = cubes.size();
	for (size_t i = 0; i < s; i++) {
		cubes[i]->position.y = sin(i+counter)*225;
		cubes[i]->position.z = cos(i+counter)*225;
	}
	counter += deltaTime;

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 600.0f; // 600 units / second

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
