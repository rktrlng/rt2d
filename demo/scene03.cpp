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

Color red     = Color(1.0f, 0.0f, 0.0f, 1.0f);
Color yellow  = Color(1.0f, 1.0f, 0.0f, 1.0f);
Color green   = Color(0.0f, 1.0f, 0.0f, 1.0f);
Color cyan    = Color(0.0f, 1.0f, 1.0f, 1.0f);
Color blue    = Color(0.0f, 0.0f, 1.0f, 1.0f);
Color magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);

Color colors[6] = {red, yellow, green, cyan, blue, magenta};

Scene03::Scene03() : Scene()
{
	t.start();
	
	//Load Line from file.
	//This is the preferred method.
	rt2d_line = new BasicEntity();
	rt2d_line->addLine("assets/rt2d.line");
	rt2d_line->position.x = SWIDTH/3;
	rt2d_line->position.y = SHEIGHT/3;
	
	//Or create a new Line and add it to an Entity later.
	//It will be deleted when the Entity is deleted.
	//Not adding it to an Entity will create a memory leak.
	Line* tmp = new Line();
	tmp->color = green;
	tmp->addPoint(-10.0f, -10.0f);
	tmp->addPoint(20.0f, 0.0f);
	tmp->addPoint(-10.0f, 10.0f);
	
	//Create a BoidEntity this time, and add the Line.
	custom_line = new BoidEntity();
	custom_line->addLine(tmp);
	custom_line->velocity = Vector2((rand()%500)-250, (rand()%500)-250);
	custom_line->position = Point2(SWIDTH/2, SHEIGHT/2);
	
	// Create a BoidEntity with a Circle.
	Line* c = new Line();
	c->createCircle(15, 30);
	circle_line = new BoidEntity();
	circle_line->addLine(c);
	circle_line->velocity = Vector2((rand()%1000)-500, (rand()%1000)-500);
	circle_line->position = Point2(SWIDTH/2, SHEIGHT/2);
	
	// Shapes!!
	shape_container = new BasicEntity();
	shape_container->position = Point2(SWIDTH/2, SHEIGHT/2);
	// fill shapes vector with variants of a circle
	for (int i = 3; i < 11; i++) {
		Line* circle = new Line();
		circle->createCircle(30, i);
		circle->color = colors[i%6];
		
		BasicEntity* b = new BasicEntity();
		b->position.x = (i*80) - 520;
		b->addLine(circle);
		shapes.push_back(b);
		shape_container->addChild(b);
	}
	
	this->addChild(rt2d_line);
	this->addChild(custom_line);
	this->addChild(circle_line);
	this->addChild(shape_container);
}


Scene03::~Scene03()
{
	delete rt2d_line;
	delete custom_line;
	delete circle_line;
	
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
		custom_line->velocity = Vector2((rand()%500)-250, (rand()%500)-250);
		counter++;
		t.start();
	}
	
	rt2d_line->rotation += 3.14f / 2 * deltaTime;
	rt2d_line->scale.x = sin(rt2d_line->rotation);
	rt2d_line->scale.y = cos(rt2d_line->rotation);
	
	shape_container->rotation -= 3.14f / 8 * deltaTime;
}
