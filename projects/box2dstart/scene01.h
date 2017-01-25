/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#ifndef SCENE01_H
#define SCENE01_H

#include <Box2D/Box2D.h>
#include <rt2d/scene.h>

#define MAX_BODIES 250

class BasicEntity: public Entity
{
public:
	BasicEntity(): Entity() { };
	virtual ~BasicEntity() { };

	virtual void update(float deltaTime) { };
};


class Scene01: public Scene
{
public:
	Scene01();
	virtual ~Scene01();

	virtual void update(float deltaTime);

	void addCircleBody(float radius, float x, float y);
	void addBoxBody(float hw, float hh, float x, float y);

private:
	void setupWorld();
	b2World* world;
	std::vector<b2Body*> bodies;
	std::vector<BasicEntity*> entities;

	Timer t; // simulate timer (1/60)
	Timer st; // spawn timer

	BasicEntity* ge; // groundentity
	BasicEntity* lw; // leftwall
	BasicEntity* rw; // rightwall
};

#endif /* SCENE01_H */
