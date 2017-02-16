/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	srand((unsigned)time(NULL));

	myentity = new MyEntity();
	myentity->position = Point2(SWIDTH/2, SHEIGHT/2);
	this->addChild(myentity);
}


MyScene::~MyScene()
{
	this->removeChild(myentity);
	delete myentity;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	// ###############################################################
	// Spacebar scales myentity
	// ###############################################################
	if (input()->getKeyDown( GLFW_KEY_SPACE )) {
		myentity->scale = Point(16.0f, 16.0f);
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		myentity->scale = Point(SWIDTH/32.0f, SHEIGHT/32.0f);
	}

	// ###############################################################
	// '[' and ']' switch shaders
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_LEFT_BRACKET )) {
		myentity->activeshader--;
	}
	if (input()->getKeyUp( GLFW_KEY_RIGHT_BRACKET )) {
		myentity->activeshader++;
	}
	if (myentity->activeshader >= (int) myentity->fragshaders.size()) { myentity->activeshader = 0; }
	if (myentity->activeshader < 0) { myentity->activeshader = myentity->fragshaders.size()-1; }
}
