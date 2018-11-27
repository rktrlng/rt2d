/**
 * @file entity.h
 *
 * @brief The Entity header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef ENTITY_H
#define ENTITY_H

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <rt2d/rt2dconfig.h>
#include <rt2d/timer.h>
#include <rt2d/sprite.h>
#include <rt2d/line.h>
#include <rt2d/vectorx.h>
#include <rt2d/input.h>
#include <rt2d/singleton.h>

/// @brief The Entity class is the Base class for the elements in your Scene.
class Entity
{
public:
	Entity(); ///< @brief Constructor of an Entity
	virtual ~Entity(); ///< @brief Destructor of an Entity

	/// @brief update this Entity. This function is Pure virtual. User MUST implement this in subclass.
	/// @param deltaTime The time that's passed since the last update.
	/// @return void
	virtual void update(float deltaTime) = 0;

	// transform
	Point3 position; /**< @brief The position of the Entity */
	Point3 rotation; /**< @brief The rotation of the Entity */
	Point3 scale; /**< @brief The scale of the Entity */

	// data structure
	/// @brief add an Entity as a child of this Entity.
	/// Defines the data structure (parent/children relationship)
	/// @param child The Entity you want to add as a child.
	/// @return void
	void addChild(Entity* child);
	/// @brief remove this Entity from list of children.
	/// @param child The Entity you want to remove from your children.
	/// @return void
	void removeChild(Entity* child);
	/// @brief get nth Entity from list of children.
	/// @param i The id of the Entity you want to get.
	/// @return Entity* child
	Entity* getChild(unsigned int i);
	/// @brief get the list of children.
	/// @return std::vector<Entity*>& _children
	const std::vector<Entity*>& children() { return _children; };

	// sprite
	/// @brief get the Sprite from this Entity.
	/// @return Sprite* _sprite
	Sprite* sprite() { return _sprite; };
	/// @brief add a Sprite to this Entity by Sprite*.
	/// @param spr A pointer to a Sprite.
	/// @return void
	void addSprite(Sprite* spr);
	/// @brief add a Sprite to this Entity by filename.
	/// @param filename The filename of the image you want to add as a Sprite.
	/// @return void
	void addSprite(const std::string& filename);
	/// @brief add a Sprite to this Entity.
	/// @param filename The filename of the image you want to add as a Sprite.
	/// @param pivotx The x component of the pivotpoint.
	/// @param pivoty The y component of the pivotpoint.
	/// @return void
	void addSprite(const std::string& filename, float pivotx, float pivoty);
	/// @brief add a Sprite to this Entity.
	/// @param filename The filename of the image you want to add as a Sprite.
	/// @param pivotx The x component of the pivotpoint.
	/// @param pivoty The y component of the pivotpoint.
	/// @param filter The filter.
	/// @param wrap The wrapping.
	/// @return void
	void addSprite(const std::string& filename, float pivotx, float pivoty, int filter, int wrap);
	/// @brief add a SpriteSheet to this Entity.
	/// @param filename The filename of the image you want to add as a SpriteSheet.
	/// @param u number of horizontal textures
	/// @param v number of vertical textures
	/// @return void
	void addSpriteSheet(const std::string& filename, int u, int v);
	/// @brief add a Grid as a Spritebatch to this Entity.
	/// @param filename The filename of the image.
	/// @param u number of horizontal textures
	/// @param v number of vertical textures
	/// @param cols number of cells
	/// @param rows number of vertical cells
	/// @param sizex horizontal size of a cell
	/// @param sizey vertical size of a cell
	/// @return void
	void addGrid(const std::string& filename, int u, int v, int cols, int rows, int sizex, int sizey);
	/// @brief add a Circular Sprite to this Entity by filename.
	/// @param filename The filename of the image you want to add as a Sprite.
	/// @param radius The radius of the circle.
	/// @param segments The number of segments of the circle.
	/// @return void
	void addCircleSprite(const std::string& filename, int radius, int segments);
	/// @brief add a Circular Sprite to this Entity by filename.
	/// @param filename The filename of the image you want to add as a Sprite.
	/// @param radius The radius of the circle.
	/// @param segments The number of segments of the circle.
	/// @param which which segment (0-5 if hexagon).
	/// @return void
	void addSegmentSprite(const std::string& filename, int radius, int segments, int which);
	/// @brief add Dynamic Sprite to this Entity by PixelBuffer*.
	/// @param pixels A pointer to a PixelBuffer.
	/// @return void
	void addDynamicSprite(PixelBuffer* pixels);

	// line
	/// @brief get the Line from this Entity.
	/// @return Line* _line
	Line* line() {
		if (_line != nullptr) {
			return _line;
		} else {
			if (_linebatch.size() > 0) {
				return &_linebatch[0];
			}
		}
		return nullptr;
	};
	/// @brief add a Line to this Entity by Line*.
	/// @param line A pointer to a Line.
	/// @return void
	void addLine(Line* line);
	/// @brief add a Line to this Entity.
	/// @param filename The filename of the line you want to add.
	/// @return void
	void addLine(const std::string& filename);

	// spritebatch, grid
	/// @brief get the spritebatch of this Entity.
	/// @return std::vector<Sprite*>& _spritebatch
	std::vector<Sprite*>& spritebatch() { return _spritebatch; };
	/// @brief get the linebatch of this Entity.
	/// @return std::vector<Line>& _linebatch
	std::vector<Line>& linebatch() { return _linebatch; };

	/// @brief get the guid of this Entity.
	/// @return int _guid
	int guid() { return _guid; };
	/// @brief get the parent of this Entity.
	/// @return Entity* _parent
	Entity* parent() { return _parent; };

	/// @brief get the world position of this Entity.
	/// @return Point3 _worldposition
	Point3 worldposition() { return _worldposition; };
	/// @brief get the world rotation of this Entity.
	/// @return Point3 _worldrotation
	Point3 worldrotation() { return _worldrotation; };
	/// @brief get the world scale of this Entity.
	/// @return Point3 _worldscale
	Point3 worldscale() { return _worldscale; };

	/// @brief get a pointer to the Input
	/// @return Input* a pointer to the Input
	Input* input() { return _input; };

	friend class Renderer;

protected:
	// updated world transforms
	Point3 _worldposition; /**< @brief The position of the Entity in the real world */
	Point3 _worldrotation; /**< @brief The rotation of the Entity in the real world */
	Point3 _worldscale; /**< @brief The scale of the Entity in the real world */

	std::vector<Sprite*> _spritebatch; ///< @brief The _spritebatch of this Entity
	std::vector<Line> _linebatch; ///< @brief The _linebatch of this Entity

private:
	// identity
	int _guid; ///< @brief The _guid of this Entity
	static int _nextGuid; ///< @brief The _nextGuid of this Entity

	// data structure
	Entity* _parent; ///< @brief The _parent of this Entity
	std::vector<Entity*> _children; ///< @brief The _children of this Entity

	// sprite
	Sprite* _sprite; ///< @brief The _sprite of this Entity
	Line* _line; ///< @brief The _line of this Entity

	Input* _input; ///< @brief the Input instance

	/// @brief delete the Sprite of this Entity.
	/// @return void
	void deleteSprite() {
		if (_sprite != nullptr) {
			delete _sprite;
			_sprite = nullptr;
		}
	};
	/// @brief delete the Line of this Entity.
	/// @return void
	void deleteLine() {
		if (_line != nullptr) {
			delete _line;
			_line = nullptr;
		}
	};
	/// @brief delete the Linebatch of this Entity.
	/// @return void
	void deleteLinebatch() {
		_linebatch.clear();
	};
	/// @brief delete the Spritebatch of this Entity.
	/// @return void
	void deleteSpritebatch() {
		int s = _spritebatch.size();
		for (int i = 0; i < s; i++) {
			delete _spritebatch[i];
		}
		_spritebatch.clear();
	};
};

#endif /* ENTITY_H */
