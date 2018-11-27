/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene03.h"

RGBAColor colors[10] = { WHITE, GRAY, RED, ORANGE, YELLOW, GREEN, CYAN, BLUE, PINK, MAGENTA };

Scene03::Scene03() : SuperScene()
{
	t.start();

	text[0]->message("Scene03: Static or dynamic lines");

	text[4]->message("<Arrow keys> fly spaceship");

	// Load Line from file (rt2d logo)
	// This is the preferred method.
	rt2d_line = new BasicEntity();
	rt2d_line->addLine("assets/rt2d.line");
	rt2d_line->line()->color = RED;
	rt2d_line->position = Point2(SWIDTH/3, SHEIGHT/3);

	// and another one (default 128x128 square)
	default_line = new BasicEntity();
	default_line->addLine("assets/default.line");
	default_line->line()->color = GREEN;
	default_line->position = Point2((SWIDTH/3)*2, SHEIGHT/3);

	// Or create a new Line and add it to an Entity later.
	// It will be unique once you added it to an Entity.
	// You must delete it yourself after you've added it to all the Entities you want.
	Line* tmp = new Line();
	tmp->addPoint(-10.0f, -10.0f);
	tmp->addPoint(20.0f, 0.0f);
	tmp->addPoint(-10.0f, 10.0f);
	tmp->addPoint(-10.0f, -10.0f);

	//Create a BasicEntity as our spaceship.
	spaceship = new BasicEntity();
	spaceship->addLine(tmp);
	spaceship->position = Point2(SWIDTH/2, SHEIGHT/2);
	delete tmp; // delete when you're done with it.

	// Shapes!!
	shape_container = new BasicEntity();
	shape_container->position = Point2(SWIDTH/2, (SHEIGHT/3)*2);
	int numshapes = 12;
	// fill shapes vector with variants of a circle
	for (int i = 3; i <= numshapes; i++) {
		Line* circle = new Line();
		circle->createCircle(30, i);
		circle->color = colors[(i-3)%10];

		BasicEntity* b = new BasicEntity();
		int spacing = 80;
		// shape_container acts as pivot point (center of the shapes).
		b->position.x = ((i-3)*spacing) - ((numshapes*spacing)/2) + (1.5f*spacing);
		b->addLine(circle);
		shapes.push_back(b);
		shape_container->addChild(b);
		delete circle;
	}

	// Dynamic Line
	Line* dynamic = new Line();
	dynamic->dynamic(true);
	//dynamic->closed(true);
	dynamic->color = GREEN;
	int spacing = 25;
	int amount = SWIDTH/spacing;
	int i=0;
	for (i = 1; i < amount; i++) {
		dynamic->addPoint(i*spacing, 0);
	}

	dynamic_line = new BasicEntity();
	dynamic_line->position.y = SHEIGHT-60;
	dynamic_line->addLine(dynamic);
	delete dynamic;

	cube3d = new Cube3D();
	sphere3d = new Sphere3D();


	// Create Tree
	layers[0]->addChild(dynamic_line);
	layers[0]->addChild(rt2d_line);
	layers[0]->addChild(default_line);
	layers[0]->addChild(spaceship);
	layers[0]->addChild(shape_container);
	layers[0]->addChild(cube3d);
	layers[0]->addChild(sphere3d);
}


Scene03::~Scene03()
{
	layers[0]->removeChild(shape_container);
	layers[0]->removeChild(spaceship);
	layers[0]->removeChild(default_line);
	layers[0]->removeChild(rt2d_line);
	layers[0]->removeChild(dynamic_line);
	layers[0]->removeChild(cube3d);

	delete dynamic_line;
	delete rt2d_line;
	delete default_line;
	delete spaceship;
	delete cube3d;
	delete sphere3d;

	int s = shapes.size();
	for (int i=0; i<s; i++) {
		shape_container->removeChild(shapes[i]);
		delete shapes[i];
		shapes[i] = nullptr;
	}
	shapes.clear();

	delete shape_container;
}

void Scene03::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// ###############################################################
	// dynamic_line
	// ###############################################################
	if (t.seconds() >= 0.1f) {
		Line* line = dynamic_line->line();
		unsigned int s = line->points().size();
		for (unsigned int i = 1; i < s-1; i++) {
			float x = line->points()[i].x;
			line->editPoint(i, x, (rand()%100)-50);
		}
		t.start();
	}

	// ###############################################################
	// rt2d_line
	// ###############################################################
	rt2d_line->rotation.z += 90 * DEG_TO_RAD * deltaTime;
	if (rt2d_line->rotation.z > TWO_PI) { rt2d_line->rotation.z -= TWO_PI; }
	rt2d_line->scale.x = sin(rt2d_line->rotation.z);
	rt2d_line->scale.y = cos(rt2d_line->rotation.z);
	rt2d_line->line()->color = Color::rotate(rt2d_line->line()->color, deltaTime*2);

	// ###############################################################
	// default_line
	// ###############################################################
	static float s = 0.0f;
	s += 2 * deltaTime;
	if (s > TWO_PI) { s -= TWO_PI; }
	default_line->scale.x = sin(s);
	default_line->scale.y = cos(s);
	default_line->line()->color = Color::rotate(default_line->line()->color, deltaTime);

	// ###############################################################
	// spaceship
	// ###############################################################
	this->updateSpaceShip(deltaTime);
}

void Scene03::updateSpaceShip(float deltaTime)
{
	spaceship->line()->color = WHITE;

	float rotspeed = 3.14f;

	static Vector2 velocity = Vector2((rand()%100)-50, (rand()%100)-50);
	static Polar polar = Polar((rand()%360) * DEG_TO_RAD, 400.0f);

	if (input()->getKey( KeyCode::Up )) {
		spaceship->line()->color = RED;
		velocity += polar.cartesian() * deltaTime; // thrust
	}
	if (input()->getKey( KeyCode::Right )) {
		polar.angle += rotspeed * deltaTime; // rotate right
	}
	if (input()->getKey( KeyCode::Left )) {
		polar.angle -= rotspeed * deltaTime; // rotate left
	}

	spaceship->rotation.z = polar.angle;
	spaceship->position += velocity * deltaTime;

	if (spaceship->position.x < 0) { spaceship->position.x = SWIDTH; }
	if (spaceship->position.x > SWIDTH) { spaceship->position.x = 0; }
	if (spaceship->position.y < 0) { spaceship->position.y = SHEIGHT; }
	if (spaceship->position.y > SHEIGHT) { spaceship->position.y = 0; }
}
