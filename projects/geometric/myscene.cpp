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

	camera()->boom(175);
	camera()->tilt(-0.25f);

	cube = new GeoMetric();
	cube->position = Point3(-SWIDTH/4, -SHEIGHT/5);
	cube->addCube(64,96,32); // halfwidth, halfheight, halfdepth
	this->addChild(cube);

	sphere = new GeoMetric();
	sphere->position = Point3(0, -SHEIGHT/5);
	sphere->addSphere(96,12,8); // radius, lats, longs
	this->addChild(sphere);

	cone = new GeoMetric();
	cone->position = Point3(SWIDTH/4, -SHEIGHT/5);
	cone->addCone(96,96,8); // radius, height, lats (4 to make pyramid)
	this->addChild(cone);

	cylinder = new GeoMetric();
	cylinder->position = Point3(-SWIDTH/4, SHEIGHT/5);
	cylinder->addCylinder(64,96,12); // radius, height, lats
	this->addChild(cylinder);

	torus = new GeoMetric();
	torus->position = Point3(0, SHEIGHT/5);
	torus->addTorus(75,35,12,4); // radius1, radius, lats, longs
	this->addChild(torus);

	pyramid = new GeoMetric();
	pyramid->position = Point3(SWIDTH/4, SHEIGHT/5);
	pyramid->addCone(96,64,4); // radius, height, lats (4 to make pyramid)
	this->addChild(pyramid);
}


MyScene::~MyScene()
{
	delete cube;
	delete sphere;
	delete cone;
	delete cylinder;
	delete torus;
	delete pyramid;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	torus->rotation.x += deltaTime;
	torus->rotation.y -= deltaTime;

	// ###############################################################
	// First Person Shooter camera controls
	// ###############################################################
	this->fpsCam(deltaTime);
}

void MyScene::fpsCam(float deltaTime)
{
	float movspeed = 500.0f; // units per second
	float rotspeed = PI / 4; // radians per second
	float rollspeed = PI / 400; // radians per second

	// Use keyboard to move and look around
	// tilt
	if (input()->getKey( GLFW_KEY_UP )) 	{ camera()->tilt(deltaTime * rotspeed); }
	if (input()->getKey( GLFW_KEY_DOWN ))	{ camera()->tilt(deltaTime * -rotspeed); }
	// pan
	if (input()->getKey( GLFW_KEY_LEFT )) 	{ camera()->pan(deltaTime * rotspeed); }
	if (input()->getKey( GLFW_KEY_RIGHT ))	{ camera()->pan(deltaTime * -rotspeed); }
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
