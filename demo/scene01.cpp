/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#include "scene01.h"

Scene01::Scene01() : Scene()
{
	// Start Timer t
	t.start();

	// Create an Entity with a custom pivot point.
	default_entity = new BasicEntity();
	default_entity->addSprite("assets/default.tga", 0.75f, 0.25f); // custom pivot point
	default_entity->position = Point2(500, 300);
	
	// Create an Entity that's going to be a Child of the Entity above.
	child1_entity = new BasicEntity();
	child1_entity->addSprite("assets/letterF.tga");
	child1_entity->sprite()->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	child1_entity->position = Point2(100, -100); // position relative to parent (default_entity)
	
	// A different approach: create Sprite first, then add it to an Entity later.
	// It will be unique once you added it to an Entity.
	// You must delete it yourself after you've added it to all the Entities you want.
	Sprite* f_spr = new Sprite();
	f_spr->setupSprite("assets/letterF.tga", 0.5f, 0.5f, 1.0f, 1.0f);
	f_spr->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	child2_entity = new BasicEntity();
	child2_entity->position = Point2(64, 64); // position relative to parent (child1_entity)
	delete f_spr;
	
	// An example of using a SpriteSheet ("animated texture").
	// Remember you also animate UV's of any Sprite (uvoffset).
	animated_entity = new BasicEntity();
	animated_entity->addLine("assets/default.line"); // Add a line (default line fits nicely)
	animated_entity->addSpriteSheet("assets/spritesheet.tga", 4, 4);
	animated_entity->position = Point2(SWIDTH/2, SHEIGHT/2);
	
	// create a tree-structure to send to the Renderer
	// by adding them to each other and/or the scene ('this')
	child1_entity->addChild(child2_entity);
	default_entity->addChild(child1_entity);
	this->addChild(default_entity);
	this->addChild(animated_entity);
}


Scene01::~Scene01()
{
	// deconstruct and delete the Tree
	child1_entity->removeChild(child2_entity);
	default_entity->removeChild(child1_entity);
	this->removeChild(default_entity);
	this->removeChild(animated_entity);
	
	delete animated_entity;
	delete child2_entity;
	delete child1_entity;
	delete default_entity;
}

void Scene01::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}
	
	// ###############################################################
	// Rotate default_entity
	// ###############################################################
	default_entity->rotation += 90 * DEG_TO_RAD * deltaTime; // 90 deg. per sec.
	if (default_entity->rotation > TWO_PI) { default_entity->rotation -= TWO_PI; }
	
	// ###############################################################
	// Animate animated_entity
	// ###############################################################
	animated_entity->rotation -= 22.5 * DEG_TO_RAD * deltaTime;
	if (animated_entity->rotation < -TWO_PI) { animated_entity->rotation += TWO_PI; }
	
	static int f = 0;
	if (f > 15) { f = 0; }
	
	animated_entity->sprite()->frame(f);
	if (t.seconds() > 0.25f) {
		f++;
		t.start();
	}
	
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
