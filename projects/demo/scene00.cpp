/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <fstream>
#include <sstream>
#include "scene00.h"

Scene00::Scene00() : SuperScene()
{
	// Start Timer t
	t.start();

	text[0]->message("Scene00: Alice's adventures in wonderland");
	//text[1]->message("");
	//text[2]->message("");
	//text[3]->message("");
	text[4]->message("<Arrow up/down> scroll text");

	numlines = 17;
	index = 0;

	// Create an Entity with a custom pivot point.
	consolecontainer = new BasicEntity();

	// txt is ~830px wide
	int left = (SWIDTH-830)/2;
	for (unsigned int i = 0; i < numlines; i++) {
		Text* line = new Text();
		line->scale = Point2(0.35f, 0.35f);
		line->position = Point2(left, 210+i*25);
		line->message("", GREEN);

		consoletext.push_back(line);
		consolecontainer->addChild(line);
	}
	filltext();

	layers[1]->addChild(consolecontainer);
}


Scene00::~Scene00()
{
	int ts = consoletext.size();
	for (int i=0; i<ts; i++) {
		consolecontainer->removeChild(consoletext[i]);
		delete consoletext[i];
		consoletext[i] = nullptr;
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
	// Scroll text with arrow up/down
	// ###############################################################
	static int first = 1;
	if (first) {
		updateconsoletext();
		first=0;
	}
	float scrolldelay = 0.025f; // 40 FPS
	if (input()->getKey( KeyCode::Down )) {
		if (t.seconds() > scrolldelay) {
			index++;
			updateconsoletext();
			t.start();
		}
	}
	if (input()->getKey( KeyCode::Up )) {
		if (t.seconds() > scrolldelay) {
			index--; if (index<0) {index=0;}
			updateconsoletext();
			t.start();
		}
	}
}

void Scene00::updateconsoletext()
{
	// ###############################################################
	// Fill consoletext with fulltext
	// ###############################################################
	unsigned int s = fulltext.size();
	int maxid = s - numlines;
	if (index > maxid) {
		index = maxid;
	}
	for (unsigned int i = 0; i < numlines; i++) {
		consoletext[i]->message(fulltext[index+i], GREEN);
	}
}

void Scene00::filltext()
{
	fulltext.clear();
	std::ifstream infile("assets/alice.txt");
	std::string line;
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		fulltext.push_back(line);
	}
}
