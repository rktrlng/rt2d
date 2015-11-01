/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "scene06.h"

Scene06::Scene06() : SuperScene()
{
	t.start();
	
	text[0]->message("Scene06: Hexagons");
	//text[1]->message("");
	text[2]->message("<ESC> quit demo");
	//text[3]->message("<SPACE> pause animation");
	
	// container for Sprite with custom Texture
	hexa_container = new BasicEntity();
	int radius = 64;
	int segments = 6; // 0 = standard square Sprite (Renderer treats this as boolean), 1-2 = non-visible. 3-n do as you would expect.
	hexa_container->addCircleSprite("assets/default.tga", radius, segments); // radius, segments
	hexa_container->position = Point2(SWIDTH/2, SHEIGHT/2);


	layers[0]->addChild(hexa_container);
}


Scene06::~Scene06()
{
	layers[0]->removeChild(hexa_container);
	
	delete hexa_container;
}

void Scene06::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);
	
	// ###############################################################
	// ...
	// ###############################################################
	
}
