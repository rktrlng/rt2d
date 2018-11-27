/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <rt2d/core.h>

#include "scene07.h"
#include "scene11.h"
#include "scene12.h"
#include "scene13.h"
#include "scene14.h"
#include "scene15.h"
#include "scene16.h"
#include "scene17.h"
#include "scene19.h"
#include "scene20.h"

int main( void )
{
	// Core instance
	Core core;

	// Create all scenes on the heap and keep a list
	std::vector<SuperScene*> scenes;
	scenes.push_back(new Scene07()); // canvas pixel particles
	scenes.push_back(new Scene11()); // canvas snake
	scenes.push_back(new Scene12()); // canvas pixelsprite
	scenes.push_back(new Scene13()); // canvas space invaders
	scenes.push_back(new Scene14()); // canvas tetris
	scenes.push_back(new Scene15()); // canvas game of life
	scenes.push_back(new Scene16()); // canvas metaballs
	scenes.push_back(new Scene17()); // canvas reaction diffusion
	// scenes.push_back(new Scene19()); // canvas diffusion-limited aggregation
	// scenes.push_back(new Scene20()); // canvas mandelbrot
	int s = scenes.size();

	// start running with the first Scene
	SuperScene* scene = scenes[0];
	int scenecounter = 0;
	int running = 1;
	while (running) {
		scenecounter = scene->activescene;
		if (scenecounter > s-1) { scenecounter = 0; scene->activescene = 0; }
		if (scenecounter < 0) { scenecounter = s-1; scene->activescene = s-1; }
		scene = scenes[scenecounter];
		core.run(scene); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds
		if (!scene->isRunning()) { running = 0; } // check status of Scene every frame
	}

	// delete all scenes
	for (int i = 0; i < s; i++) {
		delete scenes[i];
		scenes[i] = nullptr;
	}
	scenes.clear();

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
