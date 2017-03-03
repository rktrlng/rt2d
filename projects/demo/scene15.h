/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE15_H
#define SCENE15_H

#include <vector>
#include <rt2d/timer.h>
#include <rt2d/vectorx.h>
#include <rt2d/canvas.h>
#include "superscene.h"


class Scene15: public SuperScene
{
public:
	Scene15();
	virtual ~Scene15();

	virtual void update(float deltaTime);

private:
	std::vector<bool> field;

	void gameOfLifeUpdate();
	void drawField();

	Pointi wrap(Pointi n);
	inline int getIdFromPos(int x, int y) { return (y*canvas->width())+x; };

	Canvas* canvas;
	Timer timer;

	void randomField();
	void infinitGrowthA();
	void infinitGrowthB();
	void rpentomino();
	void pentadecathlon();
	void pulsar();
	void blinkerToadBeacon();
	void lightweightSpaceship();
	void glider();
	void gliderGun();
};

#endif /* SCENE15_H */
