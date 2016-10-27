/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
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
	int s = _spritebatch.size();
	for (int i=0; i<s; i++) {
		delete _spritebatch[i];
	}
	_spritebatch.clear();

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
		Sprite* character = new Sprite();
		float uvwidth = 1.0f / 16;
		float uvheight = 1.0f / 8;
		character->setupSprite("fonts/font.tga", 0.5f, 0.5f, uvwidth, uvheight, DEFAULTFILTER, DEFAULTWRAP);
		character->color = color;
		char c = _message[i];
		character->spriteposition.x = i*32; // half spacing between 64px wide characters
		int index = (int) c-32;
		if (index<0) { index = 0; }
		character->frame(index);

		_spritebatch.push_back(character);
	}
}
