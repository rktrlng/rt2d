/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE03_H
#define SCENE03_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

// Ignore Cube3D and Sphere3D implementations here.
// There are better examples in projects/geometric
class Cube3D: public Entity
{
public:
	Cube3D(): Entity() {
		int halfsize = 32;
		this->position = Point3(SWIDTH/2, SHEIGHT/4);
		this->rotation.x = 0.15f;
		for (int i = 0; i < 4; i++) {
			BasicEntity* c = new BasicEntity();
			this->addChild(c);
			components.push_back(c);
		}
		Line box;
		box.createBox(halfsize, halfsize);

		components[0]->addLine(&box);
		components[0]->position = Point3(0,0,halfsize);

		components[1]->addLine(&box);
		components[1]->position = Point3(0,0,-halfsize);

		components[2]->addLine(&box);
		components[2]->position = Point3(0,-halfsize,0);
		components[2]->rotation.x = HALF_PI;

		components[3]->addLine(&box);
		components[3]->position = Point3(0,halfsize,0);
		components[3]->rotation.x = HALF_PI;
	};
	virtual ~Cube3D() {
		int s = components.size();
		for (int i = 0; i < s; i++) {
			this->removeChild(components[i]);
			delete components[i];
		}
	};

	virtual void update(float deltaTime) {
		this->rotation.y += deltaTime;
		this->rotation.x += deltaTime;
	};
private:
	std::vector<BasicEntity*> components;
};

// Have a quick and very dirty go at drawing a sphere
// Seriously, don't do this...
class Sphere3D: public Entity
{
public:
	Sphere3D(): Entity() {
		int halfsize = 48;
		int segments = 12;
		int numlongs = 8;
		this->position = Point3(SWIDTH/2, SHEIGHT/2);
		this->rotation.x = 0.15f;

		// draw longitude / meridian lines
		float rot = 0.0f;
		for (int i = 0; i < numlongs/2; i++) {
			BasicEntity* c = new BasicEntity();
			Line circle; circle.color = GRAY;
			circle.createCircle(halfsize, segments);
			if (i == 0) { circle.color = GREEN; } // greenwich
			if (i == numlongs/4) { circle.color = BLUE; }
			c->rotation.y = rot;
			rot += TWO_PI / numlongs;
			c->addLine(&circle);
			this->addChild(c);
			components.push_back(c);
		}

		// draw latitude / parallel lines
		for (int i = -2; i < 3; i++) {
			BasicEntity* c = new BasicEntity();
			Line circle; circle.color = GRAY;
			circle.createCircle(halfsize, numlongs);
			c->rotation.x = HALF_PI;
			// TODO pretend you even tried ...
			if (i == -2) { c->position.y = halfsize-segments/2; c->scale = Point3(0.5f, 0.5f, 1.0f); }
			if (i == -1) { c->position.y = -halfsize/2; c->scale = Point3(0.9f, 0.9f, 1.0f); }
			if (i ==  0) { c->position.y = 0; circle.color = RED; } // equator
			if (i ==  1) { c->position.y = halfsize/2; c->scale = Point3(0.9f, 0.9f, 1.0f);}
			if (i ==  2) { c->position.y = -halfsize+segments/2; c->scale = Point3(0.5f, 0.5f, 1.0f); }

			c->addLine(&circle);
			this->addChild(c);
			components.push_back(c);
		}
	};
	virtual ~Sphere3D() {
		int s = components.size();
		for (int i = 0; i < s; i++) {
			this->removeChild(components[i]);
			delete components[i];
		}
	};

	virtual void update(float deltaTime) {
		this->rotation.y += deltaTime;
	};
private:
	std::vector<BasicEntity*> components;
};


class Scene03: public SuperScene
{
public:
	Scene03();
	virtual ~Scene03();

	virtual void update(float deltaTime);

private:
	Timer t;

	BasicEntity* rt2d_line;
	BasicEntity* default_line;
	BasicEntity* spaceship;

	BasicEntity* shape_container;
	std::vector<BasicEntity*> shapes;

	BasicEntity* dynamic_line;

	Cube3D* cube3d;
	Sphere3D* sphere3d;

	void updateSpaceShip(float deltaTime);
};

#endif /* SCENE03_H */
