/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene22.h"

Scene22::Scene22() : SuperScene()
{
	text[0]->message("Scene22: Emulated vertex lighting");

	t.start();

	gridwidth = 41;
	gridheight = 23;
	cellwidth = 32;
	cellheight = 32;

	// fill field of tiles
	field = new BasicEntity();
	//field->addGrid(AUTOGENWHITE, 1, 1, gridwidth, gridheight, cellwidth, cellheight);
	field->addGrid("assets/defaultgray.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);
	std::vector<Sprite*> spritebatch = field->spritebatch();
	int counter = 0;
	for (int x=0; x<gridwidth; x++) {
		for (int y=0; y<gridheight; y++) {
			spritebatch[counter]->frame(rand()%8);
			counter++;
		}
	}

	light.position = Point2(SWIDTH/2, SHEIGHT/2);
	light.velocity = Vector2((rand()%30)-15,(rand()%30)-15);

	// add field_container to Scene
	layers[0]->addChild(field);
}


Scene22::~Scene22()
{
	layers[0]->removeChild(field);
	delete field;
}

void Scene22::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do
	// - Escape key stops Scene
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	//text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[5]->message("");
	text[6]->message("");
	text[10]->message(""); // clear player click count message

	if (t.seconds() > 0.1f) {
		// loop over grid
		std::vector<Sprite*> spritebatch = field->spritebatch();
		int counter = 0;
		for (int x=0; x<gridwidth; x++) {
			for (int y=0; y<gridheight; y++) {
				//spritebatch[counter]->frame(rand()%8);

				float d = Vector2(spritebatch[counter]->spriteposition, light.position).getLength();
				int tint = 255-(d*2); if (tint < 4) { tint = 4; }
				spritebatch[counter]->color.a = tint;

				light.position += light.velocity * deltaTime;
				if(light.position.x<0) {light.position.x=0; light.velocity.x*=-1;}
				if(light.position.y<0) {light.position.y=0; light.velocity.y*=-1;}
				if(light.position.x>SWIDTH) {light.position.x=SWIDTH; light.velocity.x*=-1;}
				if(light.position.y>SHEIGHT) {light.position.y=SHEIGHT; light.velocity.y*=-1;}

				counter++;
			}
		}
		t.start();
	}

}
