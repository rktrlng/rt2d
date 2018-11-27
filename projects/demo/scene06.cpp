/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "scene06.h"

Scene06::Scene06() : SuperScene()
{
	t.start();
	ct.start();

	text[0]->message("Scene06: Hexagons / N-Gons / Circles");

	text[4]->message("<SPACE> pause texture swapping");

	// container for Sprite with custom Texture
	// This is a single, full circle created in 1 piece.
	circle_container = new BasicEntity();
	int radius = 128;
	int segments = 6; // 0 = standard square Sprite (Renderer treats this as boolean), 1-2 = non-visible. 3-n do as you would expect.
	circle_container->addCircleSprite("assets/default.tga", radius, segments); // radius, segments
	//circle_container->sprite()->uvdim = Point(0.5f, 0.5f); // uvwidth, uvheight
	circle_container->position = Point2(SWIDTH/4, SHEIGHT/2);
	layers[0]->addChild(circle_container);


	// container for Entity with single segment Sprites
	hexagon = new BasicEntity();
	hexagon->position = Point2(SWIDTH/2, SHEIGHT/2);
	// individual segments
	northeast = new BasicEntity();
	northeast->addSegmentSprite("assets/default.tga", radius, segments, 0); // radius, segments, which segment
	hexagon->addChild(northeast);
	north = new BasicEntity();
	north->addSegmentSprite("assets/pencils.tga", radius, segments, 1);
	hexagon->addChild(north);
	northwest = new BasicEntity();
	northwest->addSegmentSprite("assets/spritesheet.tga", radius, segments, 2);
	hexagon->addChild(northwest);
	southwest = new BasicEntity();
	southwest->addSegmentSprite("assets/default.tga", radius, segments, 3);
	hexagon->addChild(southwest);
	south = new BasicEntity();
	south->addSegmentSprite("assets/pencils.tga", radius, segments, 4);
	hexagon->addChild(south);
	southeast = new BasicEntity();
	southeast->addSegmentSprite("assets/spritesheet.tga", radius, segments, 5);
	hexagon->addChild(southeast);
	// add hexagon to Scene
	layers[0]->addChild(hexagon);


	// container for Entity with single segment Sprites
	segments_container = new BasicEntity();
	segments_container->position = Point2(SWIDTH/4*3, SHEIGHT/2);
	// create elements
	int amount = 12;
	for (int i=0; i<amount; i++) {
		BasicEntity* b = new BasicEntity();
		//b->addSprite("assets/default.tga");
		b->addSegmentSprite("assets/pencils.tga", radius, amount, i);

		static RGBAColor rgb = RED;
		b->sprite()->color = rgb;
		rgb = Color::rotate(rgb, 1.0f/amount);

		elements.push_back(b);
		segments_container->addChild(b);
	}
	// add segments_container to Scene
	layers[0]->addChild(segments_container);
}


Scene06::~Scene06()
{
	layers[0]->removeChild(circle_container);
	delete circle_container;

	hexagon->removeChild(northeast);
	layers[0]->removeChild(hexagon);

	delete northeast;
	delete north;
	delete northwest;
	delete southwest;
	delete south;
	delete southeast;
	delete hexagon;


	layers[0]->removeChild(segments_container);
	int s = elements.size();
	for (int i=0; i<s; i++) {
		segments_container->removeChild(elements[i]);
		delete elements[i];
		elements[i] = nullptr;
	}
	elements.clear();
	delete segments_container;
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
	if (input()->getKey(KeyCode::Space)) {
		t.pause();
	}
	if (input()->getKeyUp(KeyCode::Space)) {
		t.unpause();
	}
	static int count = 0;
	if (t.seconds() > 1.0f) {
		int s = elements.size();
		int max = 3;
		int swap = count%max;
		switch (swap) {
			case 0:
				circle_container->sprite()->texturename("assets/pencils.tga");
				for (int i=0; i<s; i++) {
					Sprite* sprite = elements[i]->sprite();
					sprite->texturename("assets/default.tga");
				}
				break;
			case 1:
				circle_container->sprite()->texturename("assets/spritesheet.tga");
				for (int i=0; i<s; i++) {
					Sprite* sprite = elements[i]->sprite();
					sprite->texturename(AUTOGENWHITE);
				}
				break;
			case 2:
				circle_container->sprite()->texturename("assets/default.tga");
				for (int i=0; i<s; i++) {
					Sprite* sprite = elements[i]->sprite();
					if (i%2==0) {
						sprite->texturename("assets/spritesheet.tga");
					}
				}
				break;

			default:
				circle_container->sprite()->texturename("assets/default.tga");
				for (int i=0; i<s; i++) {
					Sprite* sprite = elements[i]->sprite();
					sprite->texturename(AUTOGENWHITE);
				}
				break;
		}
		count++; if (count == max) { count = 0; }
		t.start();
	}

	// ###############################################################
	// color cycling
	// ###############################################################
	if (ct.seconds() > 0.1f) {
		int s = elements.size();
		for (int i=0; i<s; i++) {
			Sprite* sprite = elements[i]->sprite();
			sprite->color = Color::rotate(sprite->color, 1.0f/s);
		}
		ct.start();
	}
}
