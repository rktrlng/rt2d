/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <rt2d/scene.h>

Scene::Scene()
	: Entity()
{
	std::cout << "################ new Scene ################" << std::endl;
	_camera = new Camera();
	_input = new Input();

	_isRunning = true;
}

Scene::~Scene()
{
	delete _camera;
	delete _input;
}

void Scene::updateScene(float deltaTime)
{
	this->_updateEntity(this, deltaTime);
}


void Scene::_updateEntity(Entity* entity, float deltaTime)
{
	// call update() for this entity
	entity->update(deltaTime);

	// update() all Children (recursively)
	std::vector<Entity*> children = entity->children();
	std::vector<Entity*>::iterator child;
	for (child = children.begin(); child != children.end(); child++) {
		this->_updateEntity(*child, deltaTime);
	}
}
