/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include <rt2d/core.h>

#include "scene01.h"
#include "scene02.h"
#include "scene03.h"
#include "scene04.h"

int main( void )
{
	// Core instance
	Core core;

	// scene handle
	Scene* scene = NULL;


	// Scene01
	scene = new Scene01();		// create Scene on the heap
	while(scene->isRunning()) {	// check status of Scene every frame
		core.run(scene);		// update and render the current scene
		core.showFrameRate(5);	// show framerate in output every n seconds
	}
	core.cleanup();				// cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete scene;				// delete Scene and everything in it from the heap to make space for next Scene


	// Scene02
	scene = new Scene02();
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene;


	// Scene03
	scene = new Scene03();
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene;


	// Scene04
	scene = new Scene04();
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	delete scene;

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
