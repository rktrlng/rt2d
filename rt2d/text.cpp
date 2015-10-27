/*
 * text.cpp
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


#include "text.h"


Text::Text() : Entity()
{
	_message = "";
}


Text::~Text()
{
	clearMessage();
}

void Text::clearMessage()
{
	int s = characters.size();
	for (int i=0; i<s; i++) {
		this->removeChild(characters[i]);
		delete characters[i];
		characters[i] = NULL;
	}
	characters.clear();
}

void Text::message(std::string str)
{
	clearMessage();
	_message = str;
	
	for (unsigned int i = 0; i < _message.size(); i++) {
		Character* character = new Character();
		character->addSpriteSheet("assets/font.tga", 16, 8);
		char c = _message[i];
		character->position.x = i*32; // half spacing between 64px wide characters
		int index = 0;
		if (c < 48) {
			index = (int)c-32;
		} else {
			index = (int)c-31;
		}
		if (index<0) { index = 0; }
		character->sprite()->frame(index);
		
		characters.push_back(character);
		this->addChild(character);
	}
}
