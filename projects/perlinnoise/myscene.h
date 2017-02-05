#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <rt2d/text.h>
#include <rt2d/noise.h>

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
	Timer t;
	BasicEntity* entity;
	Text* text;

	PerlinNoise* pn;
};

#endif /* MYSCENE_H */
