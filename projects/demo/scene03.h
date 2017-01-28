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

	void updateSpaceShip(float deltaTime);
};

#endif /* SCENE03_H */
