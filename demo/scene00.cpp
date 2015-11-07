/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include <fstream>
#include <sstream>
#include "scene00.h"

Scene00::Scene00() : SuperScene()
{
	// Start Timer t
	t.start();
	
	text[0]->message("Scene00: License Text");
	//text[1]->message("");
	//text[2]->message("");
	//text[3]->message("");
	text[4]->message("<SPACE> show again from the start");

	numlines = 16;
	filltext();

	// Create an Entity with a custom pivot point.
	consolecontainer = new BasicEntity();
	
	for (unsigned int i = 0; i < numlines; i++) {
		Text* line = new Text();
		line->scale = Point2(0.35f, 0.35f);
		line->position = Point2(200, 225+i*25);
		line->message("", GREEN);
		
		consoletext.push_back(line);
		consolecontainer->addChild(line);
	}

	layers[1]->addChild(consolecontainer);
}


Scene00::~Scene00()
{
	int ts = consoletext.size();
	for (int i=0; i<ts; i++) {
		consolecontainer->removeChild(consoletext[i]);
		delete consoletext[i];
		consoletext[i] = NULL;
	}
	consoletext.clear();
	
	// deconstruct and delete the Tree
	layers[1]->removeChild(consolecontainer);

	delete consolecontainer;
}

void Scene00::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// remove 'clicks' text
	text[10]->message("");

	// ###############################################################
	// Clear text and start again
	// ###############################################################
	if (input()->getKeyDown( GLFW_KEY_SPACE )) {
		filltext();
	}
	
	// ###############################################################
	// Fill consoletext with fulltext
	// ###############################################################
	unsigned int s = consoletext.size();
	
	if (t.seconds() > 0.1f - deltaTime) { // 10 FPS
		for (unsigned int i = 0; i < s; i++) {
			consoletext[i]->message(fulltext[i], GREEN);
		}
		if (fulltext.size() > s) {
			fulltext.pop_front();
		}
		t.start();
	}
}

void Scene00::filltext()
{
	fulltext.clear();
	std::ifstream infile("assets/LICENSE");
	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		fulltext.push_back(line);
	}
}
