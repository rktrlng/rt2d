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

	test = new BasicEntity();
	test->addSprite("assets/default.tga");
	//this->addChild(test);
}


MyScene::~MyScene()
{
	this->removeChild(myentity);
	delete myentity;

	this->removeChild(test);
	delete test;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// ###############################################################
	// Spacebar scales myentity
	// ###############################################################
	if (input()->getKeyDown(KeyCode::Space)) {
		myentity->scale = Point(16.0f, 16.0f);
	}
	if (input()->getKeyUp(KeyCode::Space)) {
		myentity->scale = Point(SWIDTH/32.0f, SHEIGHT/32.0f);
	}

	// ###############################################################
	// '[' and ']' switch shaders
	// ###############################################################
	if (input()->getKeyUp(KeyCode::LeftBracket)) {
		myentity->activeshader--;
	}
	if (input()->getKeyUp(KeyCode::RightBracket)) {
		myentity->activeshader++;
	}
	if (myentity->activeshader >= (int) myentity->fragshaders.size()) { myentity->activeshader = 0; }
	if (myentity->activeshader < 0) { myentity->activeshader = myentity->fragshaders.size()-1; }

	// screen resolution fix
	int w = input()->getWindowWidth();
	int h = input()->getWindowHeight();
	myentity->sprite()->customParams[0] = Point3(w, h, 1.0f);
}
