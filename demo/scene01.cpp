/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "scene01.h"

Scene01::Scene01() : SuperScene()
{
	// Start Timer t
	t.start();
	
	text[0]->message("Scene01: Parent/child, Sprite, Spritesheet, blendcolor");
	//text[1]->message("");
	text[2]->message("<ESC> next scene");
	text[3]->message("<Arrow keys> move camera");
	text[4]->message("<SPACE> reset UV animation");

	// Create an Entity with a custom pivot point.
	default_entity = new BasicEntity();
	default_entity->addSprite("assets/default.tga", 0.75f, 0.25f); // custom pivot point
	default_entity->position = Point2(SWIDTH/3, SHEIGHT/2);
	
	// Create an Entity that's going to be a Child of the Entity above.
	child1_entity = new BasicEntity();
	child1_entity->addSprite("assets/grayscale.tga");
	child1_entity->sprite()->color = Color(1.0f, 0.0f, 0.0f, 1.0f); // red
	child1_entity->position = Point2(100, -100); // position relative to parent (default_entity)
	
	// A different approach: create Sprite first, then add it to an Entity later.
	// It will be unique once you added it to an Entity.
	// You must delete it yourself after you've added it to all the Entities you want.
	Sprite* f_spr = new Sprite();
	f_spr->setupSprite("assets/grayscale.tga", 0.5f, 0.5f, 1.0f, 1.0f); // filename, pivot.x, pivot.y, uvdim.x, uvdim.y
	f_spr->color = Color(0.0f, 1.0f, 0.0f, 1.0f); // green
	child2_entity = new BasicEntity();
	child2_entity->position = Point2(64, 64); // position relative to parent (child1_entity)
	child2_entity->addSprite(f_spr);
	delete f_spr;
	
	// An example of using a SpriteSheet ("animated texture").
	// Remember you can also animate UV's of any Sprite (uvoffset).
	animated_entity = new BasicEntity();
	animated_entity->addLine("assets/default.line"); // Add a line (default line fits nicely)
	animated_entity->addSpriteSheet("assets/spritesheet.tga", 4, 4); // divide Texture in 4x4 slices
	animated_entity->position = Point2(SWIDTH/3*2, SHEIGHT/2);
	
	// Create a UI entity
	ui_element = new BasicEntity();
	//ui_element->position = Point2(SWIDTH-150, 20); // sticks to camera in update()
	ui_element->addSprite("assets/default.tga", 0.5f, 0.0f); // Default texture. Pivot point top middle. Pivot(0,0) is top left.
	ui_element->sprite()->size = Point2(256, 64); // texture is 512x512. Make Mesh half the width, 1 row of squares (512/8).
	ui_element->sprite()->uvdim = Point2(0.5f, 0.125f); // UV 1/8 of the height.
	ui_element->sprite()->uvoffset = Point2(0.0f, 0.125f * 7); // Show top row. UV(0,0) is bottom left.
	
	// create a tree-structure to send to the Renderer
	// by adding them to each other and/or the scene ('this', or one of the layers[])
	child1_entity->addChild(child2_entity);
	default_entity->addChild(child1_entity);
	layers[1]->addChild(default_entity);
	layers[1]->addChild(animated_entity);
	layers[top_layer]->addChild(ui_element);
}


Scene01::~Scene01()
{
	// deconstruct and delete the Tree
	child1_entity->removeChild(child2_entity);
	default_entity->removeChild(child1_entity);
	layers[1]->removeChild(default_entity);
	layers[1]->removeChild(animated_entity);
	layers[top_layer]->removeChild(ui_element);
	
	delete animated_entity;
	delete child2_entity;
	delete child1_entity;
	delete default_entity;
	delete ui_element;
}

void Scene01::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);
	
	// ###############################################################
	// Rotate default_entity
	// ###############################################################
	default_entity->rotation -= 90 * DEG_TO_RAD * deltaTime; // 90 deg. per sec.
	if (default_entity->rotation < TWO_PI) { default_entity->rotation += TWO_PI; }
	
	// ###############################################################
	// Animate animated_entity
	// ###############################################################
	animated_entity->rotation += 22.5 * DEG_TO_RAD * deltaTime;
	if (animated_entity->rotation > -TWO_PI) { animated_entity->rotation -= TWO_PI; }
	
	static int f = 0;
	if (f > 15) { f = 0; }
	
	animated_entity->sprite()->frame(f);
	if (t.seconds() > 0.25f) {
		animated_entity->sprite()->color.rotate(0.5f);
		f++;
		t.start();
	}
	
	// ###############################################################
	// ui_element uvoffset
	// ###############################################################
	static float xoffset = 0.0f;
	xoffset += deltaTime / 2;
	if (input()->getKey( GLFW_KEY_SPACE )) {
		xoffset = 0.0f;
	}
	ui_element->sprite()->uvoffset.x = xoffset;
	ui_element->position = Point2(camera()->position.x + SWIDTH/2 - 150, camera()->position.y - SHEIGHT/2 + 20);
	
	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 300.0f; // 300 units / second
	
	// Right and Down vector
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	
	// Move up
	if (input()->getKey( GLFW_KEY_UP )) {
		camera()->position -= up * deltaTime * speed;
	}
	// Move down
	if (input()->getKey( GLFW_KEY_DOWN )) {
		camera()->position += up * deltaTime * speed;
	}
	// Strafe right
	if (input()->getKey( GLFW_KEY_RIGHT )) {
		camera()->position += right * deltaTime * speed;
	}
	// Strafe left
	if (input()->getKey( GLFW_KEY_LEFT )) {
		camera()->position -= right * deltaTime * speed;
	}
}
