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

	// SuperScene::Player in superscene.h
	Player* player = new Player();

	// Scene01
	Scene01* scene01 = new Scene01(); // create Scene on the heap
	scene01->addPlayer(player); // add our Player through the SuperScene to keep track of it
	while(scene01->isRunning()) { // check status of Scene every frame
		core.run(scene01); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds
	}
	core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete scene01; // delete Scene and everything in it from the heap to make space for next Scene


	// Scene02
	Scene02* scene02 = new Scene02();
	scene02->addPlayer(player);
	while(scene02->isRunning()) {
		core.run(scene02);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene02;


	// Scene03
	Scene03* scene03 = new Scene03();
	scene03->addPlayer(player);
	while(scene03->isRunning()) {
		core.run(scene03);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene03;


	// Scene04
	Scene04* scene04 = new Scene04();
	scene04->addPlayer(player);
	while(scene04->isRunning()) {
		core.run(scene04);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene04;


	// Scene05
	Scene05* scene05 = new Scene05();
	scene05->addPlayer(player);
	while(scene05->isRunning()) {
		core.run(scene05);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene05;


	// Scene06
	Scene06* scene06 = new Scene06();
	scene06->addPlayer(player);
	while(scene06->isRunning()) {
		core.run(scene06);
		core.showFrameRate(5);
	}
	core.cleanup();
	delete scene06;


	// Scene07
	Scene07* scene07 = new Scene07();
	scene07->addPlayer(player);
	while(scene07->isRunning()) {
		core.run(scene07);
		core.showFrameRate(5);
	}
	//core.cleanup();
	delete scene07;


	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	std::cout << "Player clicks: " << player->mouseclicks << std::endl;

	return 0;
}
