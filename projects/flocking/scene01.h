/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#ifndef SCENE01_H
#define SCENE01_H

#include <rt2d/scene.h>
#include "flock.h"

class Scene01: public Scene
{
	public:
		Scene01();
		virtual ~Scene01();

		virtual void update(float deltaTime);

	private:
		Flock* flock1;
		Flock* flock2;
		Flock* flock3;
		Flock* flock4;
		Flock* flock5;
};

#endif /* SCENE01_H */
