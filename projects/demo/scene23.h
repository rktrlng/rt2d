/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *		 - Initial commit
 */

#ifndef SCENE23_H
#define SCENE23_H

#include <vector>
#include <bitset>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

struct MSCell {
	int col = 0; // x
	int row = 0; // y
	int neighborCount = 0;
	bool mine = false;
	bool revealed = false;
	bool border = false;
};

class Scene23: public SuperScene
{
public:
	Scene23();
	virtual ~Scene23();

	virtual void update(float deltaTime);

private:
	std::vector<MSCell*> cells;
	BasicEntity* grid;

	int countMines(MSCell* msc);
	void clear();
	void reset();
	int getindex(int x, int y, int w, int h);
	void floodFill(MSCell* msc);
	void reveal(MSCell* msc);
	void gameOver();

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;

	int numMines;
};

#endif /* SCENE23_H */
