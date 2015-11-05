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
#include "scene05.h"
#include "scene06.h"
#include "scene07.h"

int main( void )
{
	// Core instance
	Core core;

	// Scene handle
	SuperScene* scene = NULL;

	// SuperScene::Player in superscene.h
	Player* player = new Player();

	// Scene01
	scene = new Scene01(); // create Scene on the heap
	scene->addPlayer(player); // add our Player through the SuperScene to keep track of it
	while(scene->isRunning()) { // check status of Scene every frame
		core.run(scene); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds
	}
	core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete scene; // delete Scene and everything in it from the heap to make space for next Scene


	// Scene02
	scene = new Scene02();
	scene->addPlayer(player);
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene;


	// Scene03
	scene = new Scene03();
	scene->addPlayer(player);
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene;


	// Scene04
	scene = new Scene04();
	scene->addPlayer(player);
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene;


	// Scene05
	scene = new Scene05();
	scene->addPlayer(player);
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene;


	// Scene06
	scene = new Scene06();
	scene->addPlayer(player);
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene;


	// Scene07
	scene = new Scene07();
	scene->addPlayer(player);
	while(scene->isRunning()) {
		core.run(scene);
		core.showFrameRate(5);
	}
	//core.cleanup();
	delete scene;


	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	std::cout << "Player clicks: " << player->mouseclicks << std::endl;
	delete player;

	return 0;
}
