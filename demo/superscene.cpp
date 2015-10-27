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
	
	// text
	text0 = new Text();
	//text0->message("<ESC> next scene");
	//text0->position = Point2(50, 50);
	text0->scale = Point2(0.5f, 0.5f);
	layers[top_layer]->addChild(text0);
	
	text1 = new Text();
	//text1->message("<Arrow keys> move camera");
	//text1->position = Point2(50, 80);
	text1->scale = Point2(0.5f, 0.5f);
	layers[top_layer]->addChild(text1);
}


SuperScene::~SuperScene()
{
	layers[top_layer]->removeChild(logo);
	layers[top_layer]->removeChild(text0);
	layers[top_layer]->removeChild(text1);

	int s = layers.size();
	for (int i=0; i<s; i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = NULL;
	}
	layers.clear();
	
	delete logo;
	delete text0;
	delete text1;
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
	// logo and text follow camera
	// ###############################################################
	Point2 cam_pos = Point2(camera()->position.x, camera()->position.y);
	
	Point2 logo_pos = Point2(cam_pos.x, cam_pos.y - 50 + SHEIGHT/2);
	logo->position = logo_pos;
	
	Point2 text0_pos = Point2(cam_pos.x + 50 - SWIDTH/2, cam_pos.y + 50 - SHEIGHT/2);
	text0->position = text0_pos;

	Point2 text1_pos = Point2(cam_pos.x + 50 - SWIDTH/2, cam_pos.y + 80 - SHEIGHT/2);
	text1->position = text1_pos;
}
