/**
 * This class describes MyScene behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include "raycast.h"

struct Robot {
	std::vector<Ray> rays;
	Point2 position;
	Robot(float x, float y) {
		this->position = Point2(x, y);
		for (size_t i = 0; i < 360; i += 2) {
			Ray r = Ray(this->position.x, this->position.y, 10, 0);
			r.setAngle(i);
			this->rays.push_back(r);
		}
	}

	void update(float x, float y) {
		this->position = Point2(x, y);
		for (size_t i = 0; i < this->rays.size(); i++) {
			this->rays[i].position = this->position;
		}
	}
};

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

	void draw(Boundary& wall);
	void draw(Ray& ray);

private:
	Robot robot = Robot(SWIDTH/2, SHEIGHT/2);
	std::vector<Boundary> walls;
};

#endif /* MYSCENE_H */
