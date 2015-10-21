/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include <time.h>
#include "scene03.h"

Color colors[6] = { RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA };

Scene03::Scene03() : Scene()
{
	t.start();
	t2.start();
	
	//Load Line from file.
	//This is the preferred method.
	rt2d_line = new BasicEntity();
	rt2d_line->addLine("assets/rt2d.line");
	rt2d_line->position.x = SWIDTH/3;
	rt2d_line->position.y = SHEIGHT/3;
	
	//Load Line from file.
	//This is the preferred method.
	default_line = new BasicEntity();
	default_line->addLine("assets/default.line");
	default_line->position.x = (SWIDTH/3)*2;
	default_line->position.y = SHEIGHT/3;
	
	//Or create a new Line and add it to an Entity later.
	//It will be deleted when the Entity is deleted.
	//Not adding it to an Entity will create a memory leak.
	Line* tmp = new Line();
	tmp->addPoint(-10.0f, -10.0f);
	tmp->addPoint(20.0f, 0.0f);
	tmp->addPoint(-10.0f, 10.0f);
	tmp->addPoint(-10.0f, -10.0f);
	
	//Create a BoidEntity this time, and add the Line.
	custom_line = new BoidEntity();
	custom_line->addLine(tmp);
	custom_line->velocity = Vector2((rand()%500)-250, (rand()%500)-250);
	custom_line->position = Point2(SWIDTH/2, SHEIGHT/2);
	
	// Shapes!!
	shape_container = new BasicEntity();
	shape_container->position = Point2(SWIDTH/2, (SHEIGHT/3)*2);
	int numshapes = 12;
	// fill shapes vector with variants of a circle
	for (int i = 3; i <= numshapes; i++) {
		Line* circle = new Line();
		circle->createCircle(30, i);
		circle->color = colors[(i-3)%6];
		
		BasicEntity* b = new BasicEntity();
		int spacing = 80;
		b->position.x = ((i-3)*spacing) - ((numshapes*spacing)/2) + (1.5f*spacing);
		b->addLine(circle);
		shapes.push_back(b);
		shape_container->addChild(b);
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
	
	// Create Tree
	this->addChild(dynamic_line);
	this->addChild(rt2d_line);
	this->addChild(default_line);
	this->addChild(custom_line);
	this->addChild(shape_container);
}


Scene03::~Scene03()
{
	delete dynamic_line;
	delete rt2d_line;
	delete default_line;
	delete custom_line;
	
	int s = shapes.size();
	for (int i=0; i<s; i++) {
		shape_container->removeChild(shapes[i]);
		delete shapes[i];
		shapes[i] = NULL;
	}
	shapes.clear();
	
	delete shape_container;
}

void Scene03::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}
	
	// ###############################################################
	// custom_line
	// ###############################################################
	static int counter = 0;
	if (t.seconds() >= 0.25f) {
		custom_line->line()->color = colors[counter%6];
		//custom_line->velocity = Vector2((rand()%500)-250, (rand()%500)-250);
		counter++;
		t.start();
	}
	
	// ###############################################################
	// dynamic_line
	// ###############################################################
	if (t2.seconds() >= 0.1f) {
		Line* line = dynamic_line->line();
		unsigned int s = line->points().size();
		for (unsigned int i = 1; i < s-1; i++) {
			float x = line->points()[i].x;
			line->editPoint(i, x, (rand()%100)-50);
		}
		t2.start();
	}
	
	// ###############################################################
	// rt2d_line
	// ###############################################################
	rt2d_line->rotation += 90 * DEG_TO_RAD * deltaTime;
	if (rt2d_line->rotation > TWO_PI) { rt2d_line->rotation -= TWO_PI; }
	rt2d_line->scale.x = sin(rt2d_line->rotation);
	rt2d_line->scale.y = cos(rt2d_line->rotation);
	
	// ###############################################################
	// default_line
	// ###############################################################
	static float s = 0.0f;
	s += 2 * deltaTime;
	if (s > TWO_PI) { s -= TWO_PI; }
	default_line->scale.x = sin(s);
	default_line->scale.y = cos(s);
}
