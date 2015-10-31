/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <iostream>

#include <rt2d/entity.h>

int Entity::_nextGuid = 0;

Entity::Entity()
{
	_guid = _nextGuid;
	_nextGuid++;
	
	//printf("Entity ctor %d\n", _guid);
	
	_parent = NULL;
	
	position = Vector2(0.0f, 0.0f);
	rotation = 0.0f;
	scale = Vector2(1.0f, 1.0f);
	
	_worldpos = Vector2(0.0f, 0.0f);
	_culled = false;

	_sprite = NULL;
	_line = NULL;
}


Entity::~Entity()
{
	//printf("Entity dtor %d\n", _guid);
	deleteSprite();
	deleteLine();
}

void Entity::addLine(const std::string& filename)
{
	deleteLine();
	_line = new Line(filename);
}

void Entity::addLine(Line* line)
{
	deleteLine();
	_line = new Line();
	*_line = *line;
}

void Entity::addSprite(Sprite* spr)
{
	deleteSprite();
	_sprite = new Sprite();
	*_sprite = *spr;
}

void Entity::addDynamicSprite(PixelBuffer* pixels)
{
	deleteSprite();
	_sprite = new Sprite();
	_sprite->setupSpriteByPixelBuffer(pixels);
}

void Entity::addSprite(const std::string& filename)
{
	this->addSprite(filename, 0.5f, 0.5f);
}

void Entity::addSprite(const std::string& filename, float pivotx, float pivoty)
{
	deleteSprite();
	_sprite = new Sprite();
	_sprite->setupSprite(filename, pivotx, pivoty, 1.0f, 1.0f, DEFAULTFILTER, DEFAULTWRAP); // trilinear filter, mirror repeat
}

void Entity::addSprite(const std::string& filename, float pivotx, float pivoty, int filter, int wrap)
{
	deleteSprite();
	_sprite = new Sprite();
	_sprite->setupSprite(filename, pivotx, pivoty, 1.0f, 1.0f, filter, wrap);
}

void Entity::addSpriteSheet(const std::string& filename, int u, int v)
{
	deleteSprite();
	_sprite = new Sprite();
	float uvwidth = 1.0f / u;
	float uvheight = 1.0f / v;
	_sprite->setupSprite(filename, 0.5f, 0.5f, uvwidth, uvheight, DEFAULTFILTER, DEFAULTWRAP); // trilinear filter, mirror repeat
}

void Entity::addChild(Entity* child)
{
	if(child->_parent != NULL) {
		child->_parent->removeChild(child);
	}
	child->_parent = this;
	this->_children.push_back(child);
}

void Entity::removeChild(Entity* child)
{
	std::vector< Entity* >::iterator it = _children.begin();
	while (it != _children.end()) {
		if ((*it)->_guid == child->_guid) {
			it = _children.erase(it);
		} else {
			++it;
		}
	}
}

Entity* Entity::getChild(unsigned int i)
{
	if (i < _children.size()) {
		return _children[i];
	}
	return NULL;
}
