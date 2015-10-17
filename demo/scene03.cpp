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
	default_line = new BasicEntity();
	default_line->addLine("assets/default.line");
	default_line->position.x = SWIDTH/3;
	default_line->position.y = SHEIGHT/3;
	
	//Or create a new Line and add it to an Entity later.
	//It will be deleted when the Entity is deleted.
	//Not adding it to an Entity will create a memory leak.
	Line* tmp = new Line();
	tmp->color = green;
	tmp->addPoint(-10.0f, -10.0f);
	tmp->addPoint(20.0f, 0.0f);
	tmp->addPoint(20.0f, 0.0f);
	tmp->addPoint(-10.0f, 10.0f);
	tmp->addPoint(-10.0f, 10.0f);
	tmp->addPoint(-10.0f, -10.0f);
	
	//Create a BoidEntity this time, and add the Line.
	custom_line = new BoidEntity();
	custom_line->addLine(tmp);
	custom_line->velocity = Vector2(350, 300);
	custom_line->position.x = 600;
	custom_line->position.y = 200;
	
	this->addChild(default_line);
	this->addChild(custom_line);
}


Scene03::~Scene03()
{
	delete default_line;
	delete custom_line;
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
	// color default line
	// ###############################################################
	static int counter = 0;
	if (t.seconds() >= 0.5f) {
		default_line->line()->color = colors[counter%6];
		counter++;
		t.start();
	}
	
	default_line->rotation += 3.14f / 2 * deltaTime;
}
