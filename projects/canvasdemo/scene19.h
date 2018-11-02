/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE19_H
#define SCENE19_H

#include <deque>
#include <rt2d/canvas.h>
#include <rt2d/timer.h>
#include <rt2d/util.h>
#include "superscene.h"

struct Element {
	Point2 position;
	Vector2 velocity;
	RGBAColor color;
};

class Scene19: public SuperScene
{
public:
	Scene19();
	virtual ~Scene19();

	virtual void update(float deltaTime);

private:
	Canvas* canvas;
	std::deque<Element> particles;
	std::deque<Element> tree;
	Timer timer;

	int w;
	int h;

	void clear();
	void setup();
	void updateDrawParticles();
	void updateDrawTree();
};

#endif /* SCENE19_H */
