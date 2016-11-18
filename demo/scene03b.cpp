/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */
#include "scene03b.h"

Scene03b::Scene03b() : SuperScene()
{
	t.start();
	text[0]->message("Scene03b: Spirograph");

	factor = 7;
	radius = 225;
	size = 1.0f;

	// ###############################
	container = new BasicEntity();
	container->position.x = SWIDTH/2;
	container->position.y = SHEIGHT/2;
	container->scale.x = size;
	container->scale.y = size;

	this->makeLines();

	// create a tree-structure to send to the Renderer
	// by adding them to each other and/or the scene
	this->addChild(container);
}

Scene03b::~Scene03b()
{
	this->removeChild(container);

	delete container;
}

void Scene03b::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// ###############################################################
	// text
	// ###############################################################
	std::string radiustxt = "<Q/E> radius: ";
	radiustxt.append(rt2d::to_string<int>(radius));
	text[5]->message(radiustxt);

	std::string factortxt = "<W/S> factor: ";
	factortxt.append(rt2d::to_string<int>(factor));
	text[6]->message(factortxt);

	std::string scaletxt = "<W/S> scale: ";
	scaletxt.append(rt2d::to_string<float>(size));
	text[7]->message(scaletxt);

	text[8]->message("<R> reset");

	// ######################################################c#########
	// frequency amplitude
	// ###############################################################
	if (input()->getKeyDown( GLFW_KEY_R )) { factor = 7; size = 1.0f; radius = 225; makeLines(); }
	if (input()->getKeyDown( GLFW_KEY_A )) { factor -= 1; makeLines(); }
	if (input()->getKeyDown( GLFW_KEY_D )) { factor += 1; makeLines(); }
	if (input()->getKeyDown( GLFW_KEY_Q )) { radius -= 25; makeLines(); }
	if (input()->getKeyDown( GLFW_KEY_E )) { radius += 25; makeLines(); }
	if (input()->getKey( GLFW_KEY_S )) { size -= 5 * deltaTime; }
	if (input()->getKey( GLFW_KEY_W )) { size += 5 * deltaTime; }
	container->scale.x = size;
	container->scale.y = size;
}

void Scene03b::makeLines()
{
	int numlines = 628;
	static int counter = 0;
	Polar p1 = Polar(0.0f, radius);
	Polar p2 = Polar(0.0f, 300);
	Line* line = new Line();
	line->color = RGBAColor(0,255,0,255);
	while (counter <= numlines) {
		Point2 point1 = p1.cartesian();
		Point2 point2 = p2.cartesian();
		line->addPoint(point1.x, point1.y);
		line->addPoint(point2.x, point2.y);
		line->addPoint(point1.x, point1.y);
		p1.angle += 0.01f;
		p2.angle += 0.01f * factor;
		counter++;
	}
	counter = 0;
	container->addLine(line);
	delete line;
}
