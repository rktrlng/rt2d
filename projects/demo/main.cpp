/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <rt2d/core.h>

#include "scene00.h"
#include "scene01.h"
#include "scene02.h"
#include "scene03.h"
#include "scene03a.h"
#include "scene04.h"
#include "scene05.h"
#include "scene06.h"
#include "scene06a.h"
#include "scene08.h"
#include "scene09.h"
#include "scene10.h"
#include "scene18.h"
#include "scene21.h"
#include "scene22.h"
#include "scene23.h"

int main( void )
{
	// Core instance
	Core core;

	// Create all scenes on the heap and keep a list
	std::vector<SuperScene*> scenes;
	scenes.push_back(new Scene00()); // text Alice in wonderland
	scenes.push_back(new Scene01()); // parent/child, spritesheet, blending etc
	scenes.push_back(new Scene02()); // spritebatch
	scenes.push_back(new Scene03()); // lines
	scenes.push_back(new Scene03a()); // math lines
	scenes.push_back(new Scene04()); // dynamic pixelbuffer
	scenes.push_back(new Scene05()); // dynamic pixelbuffer from file
	scenes.push_back(new Scene06()); // hexagons, ngons
	scenes.push_back(new Scene06a()); // hex map
	//scenes.push_back(new Scene08()); // mouse vs world
	scenes.push_back(new Scene09()); // spritesheet grid
	scenes.push_back(new Scene10()); // heightmap
	scenes.push_back(new Scene18()); // maze generation recursive backtracking
	scenes.push_back(new Scene21()); // phyllotaxis
	//scenes.push_back(new Scene22()); // emulated vertex lighting
	scenes.push_back(new Scene23()); // mineSweeper
	int s = scenes.size();

	// SuperScene::Player in superscene.h
	Player* player = new Player();

	// add our Player to the (Super)Scenes to keep track of it
	for (int i = 0; i < s; i++) {
		scenes[i]->addPlayer(player);
	}

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

/*
	// Scene01
	scene = new Scene01(); // create Scene on the heap
	scene->addPlayer(player); // add our Player to the SuperScene to keep track of it
	while(scene->isRunning()) { // check status of Scene every frame
		core.run(scene); // update and render the current scene
		core.showFrameRate(5); // show framerate in output every n seconds
	}
	core.cleanup(); // cleanup ResourceManager (Textures + Meshes, but not Shaders)
	delete scene; // delete Scene and everything in it from the heap to make space for next Scene
*/

	// show player results
	std::cout << "Player clicks: " << player->mouseclicks << std::endl;

	// and delete the player
	delete player;

	// No need to explicitly clean up the core.
	// As a local var, core will go out of scope and destroy Renderer->ResourceManager.
	// ResourceManager destructor also deletes Shaders.

	return 0;
}
