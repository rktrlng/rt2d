/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE07_H
#define SCENE07_H

#include <deque>
#include <rt2d/timer.h>
#include <rt2d/canvas.h>
#include "superscene.h"

struct Particle {
	Point2 position;
	Vector2 velocity;
	RGBAColor color;
};

class Scene07: public SuperScene
{
public:
	Scene07();
	virtual ~Scene07();

	virtual void update(float deltaTime);

private:
	RGBAColor backgroundcolor;
	Canvas* canvas;
	std::deque<Particle> particles;
	Timer timer;
	Timer fpstimer;

	void clearParticles();
};

#endif /* SCENE07_H */
