/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#ifndef SCENE04_H
#define SCENE04_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "boidentity.h"
#include "basicentity.h"

class Scene04: public SuperScene
{
	public:
		Scene04();
		virtual ~Scene04();

		virtual void update(float deltaTime);
	
	private:
		BasicEntity* pixel_container;
		Timer t;
		Timer rt;
		
		void randomPixels(PixelBuffer* pixels, int filter);
		void rainbowPixels(PixelBuffer* pixels, float step, int filter);
};

#endif /* SCENE04_H */ 
