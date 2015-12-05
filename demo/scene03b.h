/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#ifndef SCENE03B_H
#define SCENE03B_H

#include "superscene.h"
#include "basicentity.h"

class Scene03b: public SuperScene
{
public:
	Scene03b();
	virtual ~Scene03b();

	virtual void update(float deltaTime);

private:
	BasicEntity* container;
	Timer t;
	void makeLines();

	int factor;
	int radius;
	float size;
};

#endif /* SCENE03B_H */
