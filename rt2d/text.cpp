/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
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

	_message = "";
}

void Text::message(std::string str)
{
	this->message(str, WHITE);
}

void Text::message(std::string str, RGBAColor color)
{
	clearMessage();
	_message = str;
	
	unsigned int s = _message.size();
	for (unsigned int i = 0; i < s; i++) {
		Character* character = new Character();
		character->addSpriteSheet("fonts/font.tga", 16, 8);
		character->sprite()->color = color;
		char c = _message[i];
		character->position.x = i*32; // half spacing between 64px wide characters
		int index = (int) c-32;
		if (index<0) { index = 0; }
		character->sprite()->frame(index);
		
		characters.push_back(character);
		this->addChild(character);
	}
}
