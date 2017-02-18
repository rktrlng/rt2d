/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "myentity.h"

class BasicEntity: public Entity
{
public:
	BasicEntity(): Entity() { };
	virtual ~BasicEntity() { };

	virtual void update(float deltaTime) { };
};

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	MyEntity* myentity;
	BasicEntity* test;
};

#endif /* SCENE00_H */
