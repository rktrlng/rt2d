/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#ifndef SCENE06_H
#define SCENE06_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene06: public SuperScene
{
	public:
		Scene06();
		virtual ~Scene06();

		virtual void update(float deltaTime);
	
	private:
		BasicEntity* hexa_container;
		Timer t;
};

#endif /* SCENE06_H */ 
