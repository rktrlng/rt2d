/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#ifndef SCENE03_H
#define SCENE03_H

#include <vector>
#include <rt2d/scene.h>
#include <rt2d/timer.h>
#include "boidentity.h"
#include "basicentity.h"

class Scene03: public Scene
{
	public:
		Scene03();
		virtual ~Scene03();

		virtual void update(float deltaTime);
	
	private:
		Timer t;
		
		BasicEntity* rt2d_line;
		BasicEntity* default_line;
		BasicEntity* spaceship;
		
		BasicEntity* shape_container;
		std::vector<BasicEntity*> shapes;
		
		BasicEntity* dynamic_line;
		
		void updateSpaceShip(float deltaTime);
};

#endif /* SCENE03_H */ 
