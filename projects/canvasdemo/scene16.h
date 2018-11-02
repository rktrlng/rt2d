/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE16_H
#define SCENE16_H

#include <vector>
#include <rt2d/canvas.h>
#include <rt2d/timer.h>
#include <rt2d/vectorx.h>
#include <rt2d/util.h>
#include "superscene.h"
#include "canvas.h"

struct Blob
{
	Point3 pos;
	Point3 vel;
	float radius;
	int w;
	int h;

	Blob(int width, int height) {
		pos = Point3(rand()%width, rand()%height);
		vel = Point3((rand()%6)-3, (rand()%6)-3);
		radius = (rand()%200)+50;
		w = width;
		h = height;
	}

	void update() {
		pos += vel;
		if (pos.x < 0) { pos.x = 0; vel.x *= -1; }
		if (pos.x > w) { pos.x = w; vel.x *= -1; }
		if (pos.y < 0) { pos.y = 0; vel.y *= -1; }
		if (pos.y > h) { pos.y = h; vel.y *= -1; }
	}
};


class Scene16: public SuperScene
{
public:
	Scene16();
	virtual ~Scene16();

	virtual void update(float deltaTime);

private:
	std::vector<Blob> blobs;

	Canvas* canvas;
	Timer timer;
};

#endif /* SCENE16_H */
