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
	text[3]->message("<SPACE> pause texture swapping");
	
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
	// texture swapping
	// ###############################################################
	// pause timer when SPACE is pressed
	if (input()->getKey( GLFW_KEY_SPACE )) {
		t.pause();
	}
	if (input()->getKeyUp( GLFW_KEY_SPACE )) {
		t.unpause();
	}
	static int count = 0;
	if (t.seconds() > 1.0f) {
		int max = 3;
		int swap = count%max;
		switch (swap) {
			case 0:
				hexa_container->sprite()->texturename("assets/pencils.tga");
				break;
			case 1:
				hexa_container->sprite()->texturename("assets/spritesheet.tga");
				break;
			case 2:
				hexa_container->sprite()->texturename("assets/default.tga");
				break;
			
			default:
				hexa_container->sprite()->texturename("assets/default.tga");
				break;
		}
		count++; if (count == max) { count = 0; }
		t.start();
	}
}
