/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE10_H
#define SCENE10_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene10: public SuperScene
{
public:
	Scene10();
	virtual ~Scene10();

	virtual void update(float deltaTime);

private:
	// a field of tiles
	BasicEntity* field;
	Sprite* heightmapsprite;

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;
};

#endif /* SCENE10_H */
