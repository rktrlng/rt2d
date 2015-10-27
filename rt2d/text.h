/**
 * @file text.h
 * 
 * @brief The Text header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef TEXT_H
#define TEXT_H

#include <rt2d/entity.h>

/// @brief The Character class is a default Enity container for a Characters' Sprite.
class Character: public Entity
{
	public:
		Character() { }; ///< @brief Constructor of the Character
		virtual ~Character() { }; ///< @brief Destructor of the Character
		
		virtual void update(float deltaTime) { }; ///< @brief empty update function
};

/// @brief The Text class is a collection of drawable Characters.
class Text: public Entity
{
	public:
		Text(); ///< @brief Constructor of the Text
		virtual ~Text(); ///< @brief Destructor of the Text
		
		virtual void update(float deltaTime) { }; ///< @brief empty update function
		
		/// @brief clears all Sprites for characters
		/// @return void
		void clearMessage();
		/// @brief message getter
		/// @return std::string _message
		std::string message() { return _message; };
		/// @brief message setter also creates Characters
		/// @param m the message to be created
		/// @return void
		void message( std::string m );
	
	private:
		std::string _message; ///< @brief the message string
		std::vector<Character*> characters; ///< @brief collection of characters ceated from _message
};

#endif /* TEXT_H */ 
