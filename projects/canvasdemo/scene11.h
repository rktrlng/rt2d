/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE11_H
#define SCENE11_H

#include <vector>
#include <rt2d/timer.h>
#include <rt2d/canvas.h>
#include "superscene.h"

const Point_t<int> UP = Point_t<int>(0,1);
const Point_t<int> DOWN = Point_t<int>(0,-1);
const Point_t<int> LEFT = Point_t<int>(-1,0);
const Point_t<int> RIGHT = Point_t<int>(1,0);

struct Block {
	Point_t<int> position;
	Point_t<int> velocity;
	RGBAColor color;
};

class Scene11: public SuperScene
{
public:
	Scene11();
	virtual ~Scene11();

	virtual void update(float deltaTime);

private:
	std::vector<Block> snake;
	Block target;

	Canvas* canvas;
	Timer timer;

	void resetSnake();
	void addBlockToSnake();
	void placeTarget();
	bool positionIsInSnake(Point_t<int> testPoint);
};

#endif /* SCENE11_H */
