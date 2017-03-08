/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */
#include "scene03a.h"

Scene03a::Scene03a() : SuperScene()
{
	text[0]->message("Scene03a: Math");

	int border = 50;

	frequency = 5.0f;
	amplitude = 50.0f;
	radius = 150.0f;

	int amount = 360;

	// ###############################
	// sine Line
	Line* dynamic0 = new Line();
	dynamic0->dynamic(true);
	dynamic0->closed(false);
	dynamic0->color = GREEN;
	int i=0;
	for (i = 0; i < amount; i++) {
		dynamic0->addPoint(i, 0);
	}

	sine = new BasicEntity();
	//sine->position.x = (SWIDTH - (spacing*amount))/2;
	sine->position.x = SWIDTH/4 - (amount/2) + border;
	sine->position.y = SHEIGHT/2;
	sine->addLine(dynamic0);
	delete dynamic0;

	// ###############################
	// flower Line
	Line* dynamic1 = new Line();
	dynamic1->dynamic(true);
	dynamic1->closed(true);
	dynamic1->color = GREEN;
	for (i = 0; i < amount; i++) {
		dynamic1->addPoint(0, 0);
	}

	flower = new BasicEntity();
	//flower->position.x = (SWIDTH - (spacing*amount))/2;
	flower->position.x = SWIDTH/4*3 - border;
	flower->position.y = SHEIGHT/2;
	flower->addLine(dynamic1);
	delete dynamic1;

	// ###############################
	gridlines = new BasicEntity();
	gridlines->position.y = SHEIGHT/2;
	Line* gridline = new Line();
	//gridline->closed(true);
	gridline->color = RGBAColor(0,127,0,255);
	gridline->addPoint(-10, 0);
	gridline->addPoint(SWIDTH+10, 0);
	gridlines->addLine(gridline);
	delete gridline;

	// create a tree-structure to send to the Renderer
	// by adding them to each other and/or the scene
	this->addChild(gridlines);
	this->addChild(sine);
	this->addChild(flower);
}


Scene03a::~Scene03a()
{
	this->removeChild(sine);
	this->removeChild(flower);
	this->removeChild(gridlines);

	delete sine;
	delete flower;
	delete gridlines;
}

void Scene03a::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// ###############################################################
	// sine and flower
	// ###############################################################
	Line* line = sine->line();
	unsigned int s = line->points().size();

	for (unsigned int i = 0; i < s; i++) {
		float x = line->points()[i].x;
		float y = sin( (x*frequency) * DEG_TO_RAD )*amplitude;
		line->editPoint(i, x, y+radius);
	}

	line = flower->line();
	s = line->points().size();
	for (unsigned int i = 0; i < s; i++) {
		float a = i * DEG_TO_RAD;
		float r = radius + sin(a*frequency)*amplitude;
		Polar p(a, r);
		Vector2 v = p.cartesian();
		line->editPoint(i, v.x, v.y);
	}

	// ###############################################################
	// text
	// ###############################################################
	std::stringstream radiustxt;
	radiustxt << "<Q/E> radius: " << radius;
	text[5]->message(radiustxt.str());

	std::stringstream amplitudetxt;
	amplitudetxt << "<W/S> amplitude: " << amplitude;
	text[6]->message(amplitudetxt.str());

	std::stringstream frequencytxt;
	frequencytxt << "<A/D> frequency: " << frequency;
	text[7]->message(frequencytxt.str());

	// ###############################################################
	// frequency amplitude
	// ###############################################################
	if (input()->getKeyDown( KeyCode::A )) { frequency -= 1; }
	if (input()->getKeyDown( KeyCode::D )) { frequency += 1; }
	if (input()->getKey(KeyCode::S)) { amplitude -= 50 * deltaTime; }
	if (input()->getKey(KeyCode::W)) { amplitude += 50 * deltaTime; }
	if (input()->getKey(KeyCode::Q)) { radius -= 100 * deltaTime; }
	if (input()->getKey(KeyCode::E)) { radius += 100 * deltaTime; }
}
