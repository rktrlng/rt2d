/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2020 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <rt2d/core.h>

#include "scene01.h"

int main( void )
{
	Core core;

	Scene01* scene = new Scene01();
	while (scene->isRunning()) {
		core.run(scene); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds
	}

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
