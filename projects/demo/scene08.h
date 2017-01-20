/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE08_H
#define SCENE08_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

struct Cell
{
	BasicEntity* entity; // visual representation
	Point_t<int> position; // x/y in grid
	//RGBAColor color;
	//int state;
	//...
};

class Scene08: public SuperScene
{
public:
	Scene08();
	virtual ~Scene08();

	virtual void update(float deltaTime);

private:
	BasicEntity* grid;
	std::vector<Cell*> cells;

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;
	int border;
};

#endif /* SCENE08_H */
