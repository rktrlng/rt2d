/**
 * This class describes MyScene behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#include "myscene.h"
#include "collider.h"

MyScene::MyScene() : Scene()
{
	// Square1
	square1 = new Shape();
	square1->position = Point2(300, 400);
	Line s1;
	s1.addPoint(0, 0);
	s1.addPoint( 256, 0);
	s1.addPoint( 256, 128);
	s1.addPoint( 0, 128);
	s1.addPoint(0, 0);
	square1->addLine(&s1);
	this->addChild(square1);

	// Square2
	square2 = new Shape();
	square2->position = Point2(800, 400);
	Line s2;
	s2.addPoint(0, 0);
	s2.addPoint( 128, 0);
	s2.addPoint( 128, 256);
	s2.addPoint( 0, 256);
	s2.addPoint(0, 0);
	square2->addLine(&s2);
	this->addChild(square2);

	// Circle1
	circle1 = new Shape();
	circle1->position = Point2(400, 200);
	Line c1;
	c1.createCircle(64, 18);
	circle1->addLine(&c1);
	this->addChild(circle1);

	// Circle2
	circle2 = new Shape();
	circle2->position = Point2(900, 200);
	Line c2;
	c2.createCircle(32, 18);
	circle2->addLine(&c2);
	this->addChild(circle2);
}

MyScene::~MyScene()
{
	this->removeChild(square1);
	this->removeChild(square2);
	this->removeChild(circle1);
	this->removeChild(circle2);

	delete square1;
	delete square2;
	delete circle1;
	delete circle2;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// create shapes ('colliders')
	Rectangle rect1 = Rectangle(square1->position.x, square1->position.y, 256, 128);
	Rectangle rect2 = Rectangle(square2->position.x, square2->position.y, 128, 256);
	Circle circ1 = Circle(circle1->position.x, circle1->position.y, 64);
	Circle circ2 = Circle(circle2->position.x, circle2->position.y, 32);

	//get mouse position
	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH/2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT/2;
	Point2 mouse = Point2(mousex, mousey);

	// reset colors
	square1->line()->color = GREEN;
	square2->line()->color = GREEN;
	circle1->line()->color = GREEN;
	circle2->line()->color = GREEN;

	// check colliders for mouse and make draggable
	if( Collider::point2circle(mouse, circ1) ) {
		circle1->line()->color = YELLOW;
		if (input()->getMouse(0)) {
			circle1->position = mouse;
		}
	}
	if( Collider::point2circle(mouse, circ2) ) {
		circle2->line()->color = YELLOW;
		if (input()->getMouse(0)) {
			circle2->position = mouse;
		}
	}
	if( Collider::point2rectangle(mouse, rect1) ) {
		square1->line()->color = YELLOW;
		if (input()->getMouse(0)) {
			square1->position = mouse - Point2(rect1.width/2, rect1.height/2);
		}
	}
	if( Collider::point2rectangle(mouse, rect2) ) {
		square2->line()->color = YELLOW;
		if (input()->getMouse(0)) {
			square2->position = mouse - Point2(rect2.width/2, rect2.height/2);
		}
	}

	// check colliders against each other
	if( Collider::circle2circle(circ1, circ2) ) {
		circle1->line()->color = RED;
		circle2->line()->color = RED;
	}
	if( Collider::rectangle2rectangle(rect1, rect2) ) {
		square1->line()->color = RED;
		square2->line()->color = RED;
	}

	// check circles to rectangles
	if( Collider::circle2rectangle(circ1, rect1) ) {
		circle1->line()->color = RED;
		square1->line()->color = RED;
	}
	if( Collider::circle2rectangle(circ1, rect2) ) {
		circle1->line()->color = RED;
		square2->line()->color = RED;
	}
	if( Collider::circle2rectangle(circ2, rect1) ) {
		circle2->line()->color = RED;
		square1->line()->color = RED;
	}
	if( Collider::circle2rectangle(circ2, rect2) ) {
		circle2->line()->color = RED;
		square2->line()->color = RED;
	}

}
