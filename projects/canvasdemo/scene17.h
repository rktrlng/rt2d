/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE17_H
#define SCENE17_H

#include <vector>
#include <rt2d/canvas.h>
#include "superscene.h"

struct RDCell {
	float A = 1.0f;
	float B = 0.0f;
};

class Scene17: public SuperScene
{
public:
	Scene17();
	virtual ~Scene17();

	virtual void update(float deltaTime);

private:
	float dA;
	float dB;
	float feed;
	float k;

	std::vector<RDCell> field;
	size_t w;
	size_t h;
	size_t pixelsize;

	void reset();
	void addDrop(int x, int y);
	int dropsize;

	int mode;
	void handleModes();

	Pointi wrap(Pointi n);
	inline int getIdFromPos(int x, int y) { return (y*canvas->width())+x; };

	float laplaceA(int x, int y);
	float laplaceB(int x, int y);

	Canvas* canvas;
};

#endif /* SCENE17_H */
