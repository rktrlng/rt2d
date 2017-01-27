#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "cube.h"

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
	std::vector<Cube*> cubes;
	Timer t;
	BasicEntity* entity;
	void fpsCam(float deltaTime);
};

#endif /* MYSCENE_H */
