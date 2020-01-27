/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2020 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE01_H
#define SCENE01_H

#include <vector>

#include <rt2d/scene.h>
#include <rt2d/timer.h>
#include <rt2d/canvas.h>

#include "math/matrix4.h"
#include "math/vector4.h"

class Scene01: public Scene
{
public:
	Scene01();
	virtual ~Scene01();

	virtual void update(float deltaTime);
	void matrixtest();

private:
	RGBAColor backgroundcolor;
	Canvas* canvas;
	Timer timer;
	math::Vector4 points[8];
};

#endif /* SCENE01_H */
