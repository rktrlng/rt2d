/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SUPERSCENE_H
#define SUPERSCENE_H

#include <vector>
#include <rt2d/scene.h>
#include <rt2d/text.h>
#include "basicentity.h"

class SuperScene: public Scene
{
public:
	SuperScene();
	virtual ~SuperScene();

	// must be explicitly called from subclass
	virtual void update(float deltaTime);

	static int activescene;

protected:
	unsigned int top_layer;
	std::vector<BasicEntity*> layers;
	std::vector<Text*> text;
	void moveCamera(float deltaTime);

private:
	BasicEntity* logo;
	Timer fpstimer;
};

#endif /* SUPERSCENE_H */
