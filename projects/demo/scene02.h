/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE02_H
#define SCENE02_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Boid
{
public:
	Boid() {
		velocity = Vector2((rand()%500)-250, (rand()%500)-250);
		position = Point2(SWIDTH/2, SHEIGHT/2);
		scale = Point2(1.0f, 1.0f);
		rotation = 0.0f;
		waittime = 0.0f;
		t.start();
	}
	virtual ~Boid() {

	}
	void update(float deltaTime) {
		if (t.seconds() > waittime) {
			velocity = Vector2((rand()%500)-250, (rand()%500)-250);
			waittime = (float) (rand()%10)/10;
			t.start();
		}

		if (position.y < 0) {
			position.y = 0;
			velocity.y *= -1;
		} else if (position.y > SHEIGHT) {
			position.y = SHEIGHT;
			velocity.y *= -1;
		}
		if (position.x < 0) {
			position.x = 0;
			velocity.x *= -1;
		} else if (position.x > SWIDTH) {
			position.x = SWIDTH;
			velocity.x *= -1;
		}
		position += velocity * deltaTime;
		rotation = velocity.getAngle();
	}
	Vector2 velocity;
	Point2 position;
	float rotation;
	Point2 scale;
	float waittime;
	Timer t;
};

class Scene02 : public SuperScene
{
public:
	Scene02();
	virtual ~Scene02();

	virtual void update(float deltaTime);

private:
	std::vector<Boid*> boids;
};

#endif /* SCENE02_H */
