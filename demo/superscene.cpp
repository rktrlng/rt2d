/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "superscene.h"

SuperScene::SuperScene() : Scene()
{
	top_layer = 7; // 8 layers (0-7)

	for (unsigned int i = 0; i <= top_layer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	// Create a logo entity on the top layer
	logo = new BasicEntity();
	logo->position = Point2(SWIDTH/2, SHEIGHT - 50);
	logo->addLine("assets/rt2d.line");
	layers[top_layer]->addChild(logo);
}


SuperScene::~SuperScene()
{
	layers[top_layer]->removeChild(logo);
	delete logo;

	int s = layers.size();
	for (int i=0; i<s; i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = NULL;
	}
	layers.clear();
}

// must be explicitly called from subclass
void SuperScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}
	
	// ###############################################################
	// logo follows camera
	// ###############################################################
	Point2 logo_pos = Point2(camera()->position.x, camera()->position.y - 50 + SHEIGHT/2);
	logo->position = logo_pos;
}
