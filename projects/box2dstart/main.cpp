/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/


/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#include <rt2d/core.h>
#include "scene01.h"

int main( void )
{
	// Core instance
	Core core;

	// scene handle
	Scene* scene = nullptr;

	scene = new Scene01();		// create Scene on the heap
	while(scene->isRunning()) {	// check status of Scene every frame
		core.run(scene);		// update and render the current scene
		core.showFrameRate(5);	// show framerate in output every 5 seconds
	}
	//core.cleanup();				// cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete scene;				// delete Scene from heap to make space for next one

	return 0;
}


// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
// There are no graphics for this example. Box2D is meant to be used
// with your rendering engine in your game engine.
