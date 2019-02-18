/**
 * This class describes MyScene behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);
};

#endif /* MYSCENE_H */
