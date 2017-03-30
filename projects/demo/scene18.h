/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE18_H
#define SCENE18_H

#include <vector>
#include <bitset>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

struct MCell {
	int col = 0; // x
	int row = 0; // y
	// 0001 = top
	// 0010 = right
	// 0100 = bottom
	// 1000 = left
	// 0000 = no walls
	// 1111 = all walls
	std::bitset<4> walls;
	bool visited = false;
};

class Scene18: public SuperScene
{
public:
	Scene18();
	virtual ~Scene18();

	virtual void update(float deltaTime);

private:
	std::vector<MCell*> cells;
	std::vector<MCell*> stack;
	MCell* current;
	BasicEntity* grid;

	MCell* getRandomUnvisitedNeighbour(MCell* mc);
	void removeWalls(MCell* c, MCell* n);
	void clear();
	void reset();
	void export_grid();

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;

	Timer t;
};

#endif /* SCENE18_H */
