/*
 * text.h
 * 
 * Copyright 2015 rik <rik@4770K>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#ifndef TEXT_H
#define TEXT_H

#include <rt2d/entity.h>

class Character: public Entity
{
	public:
		Character() { };
		virtual ~Character() { };
		
		virtual void update(float deltaTime) { };
};


class Text: public Entity
{
	public:
		Text();
		virtual ~Text();
		
		virtual void update(float deltaTime) { }; // implementation is empty
		
		void clearMessage();
		std::string message() { return _message; };
		void message( std::string m );
	
	private:
		std::string _message;
		
		std::vector<Character*> characters;
};

#endif /* TEXT_H */ 
