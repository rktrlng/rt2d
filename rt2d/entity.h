/**
 * @file entity.h
 * 
 * @brief The Entity header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
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

#include <rt2d/config.h>
#include <rt2d/sprite.h>
#include <rt2d/line.h>
#include <rt2d/input.h>
#include <rt2d/camera.h>
#include <rt2d/vectorx.h>

/// @brief The Entity class is the Base class for the elements in your Scene.
class Entity
{
	public:
		Entity();			///< @brief Constructor of an Entity
		virtual ~Entity();	///< @brief Destructor of an Entity

		/// @brief update this Entity. This function is Pure virtual. User MUST implement this in subclass.
		/// @param deltaTime The time that's passed since the last update.
		/// @return void
		virtual void update(float deltaTime) = 0;
		
		// transform
		Vector2 position;	/**< @brief The position of the Entity */
		float rotation;		/**< @brief The rotation of the Entity */
		Vector2 scale;		/**< @brief The scale of the Entity */
		
		// data structure
		/// @brief add an Entity as a child of this Entity.
		/// Defines the data structure (parent/children relationship)
		/// @param child The Entity you want to add as a child.
		/// @return void
		void addChild(Entity* child);
		/// @brief remove this Entity from list of children.
		/// @param child The Entity you want to remove from your children.
		/// @return Entity* the child that was removed
		Entity* removeChild(Entity* child);
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
		/// @brief add a SpriteSheet to this Entity.
		/// @param filename The filename of the image you want to add as a SpriteSheet.
		/// @param u number of horizontal textures
		/// @param v number of vertical textures
		/// @return void
		void addSpriteSheet(const std::string& filename, int u, int v);
		
		// line
		/// @brief get the Line from this Entity.
		/// @return Line* _line
		Line* line() { return _line; };
		/// @brief add a Line to this Entity by Line*.
		/// @param line A pointer to a Line.
		/// @return void
		void addLine(Line* line);
		/// @brief add a Line to this Entity.
		/// @param filename The filename of the line you want to add.
		/// @return void
		void addLine(const std::string& filename);
		
		/// @brief get the guid of this Entity.
		/// @return int _guid
		int guid() { return _guid; };
		/// @brief get the parent of this Entity.
		/// @return Entity* _parent
		Entity* parent() { return _parent; };
		
		// updated world position after all transforms
		Vector2 _worldpos;	/**< @brief The position of the Entity in the real world */
		bool _culled;	/**< @brief This Entity should be culled or not */

		void enable() {this->enabled = true;}
		void disable() {this->enabled = false;}

		bool isEnabled() {return this->enabled;}
		
	protected:
		
		
	private:
		// identity
		int _guid;				///< @brief The _guid of this Entity
		static int _nextGuid;	///< @brief The _nextGuid of this Entity

		//Enabled
		bool enabled = true;
		
		// data structure
		Entity* _parent;				///< @brief The _parent of this Entity
		std::vector<Entity*> _children;	///< @brief The _children of this Entity
		
		// sprite
		Sprite* _sprite;		///< @brief The _sprite of this Entity
		Line* _line;		///< @brief The _line of this Entity
		
		/// @brief delete the Sprite of this Entity.
		/// @return void
		void deleteSprite() {
			if (_sprite != NULL) {
				delete _sprite;
				_sprite = NULL;
			}
		};
		/// @brief delete the Line of this Entity.
		/// @return void
		void deleteLine() {
			if (_line != NULL) {
				delete _line;
				_line = NULL;
			}
		};
};

#endif /* ENTITY_H */ 
