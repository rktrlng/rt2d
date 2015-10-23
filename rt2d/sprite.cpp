/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <iostream>

#include <rt2d/config.h>
#include <rt2d/sprite.h>

Sprite::Sprite()
{
	_texturename = "";
	
	_fragmentshader = SPRITEFRAGMENTSHADER;
	_vertexshader = SPRITEVERTEXSHADER;
	
	pivot = Point2(0.5f, 0.5f);
	uvdim = Point2(1.0f, 1.0f);
	uvoffset = Point2(0.0f, 0.0f);
	size = Point2(0, 0);
	
	_frame = 0;
	
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;
	color.a = 1.0f;
}

Sprite::~Sprite()
{
	
}

void Sprite::setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight)
{
	_texturename = filename;

	pivot.x = pivotx;
	pivot.y = pivoty;

	// 1.00  = 1x1 spritesheet (basic sprite)
	// 0.50  = 2x2 spritesheet
	// 0.25  = 4x4 spritesheet
	// 0.125 = 8x8 spritesheet
	uvdim.x = uvwidth;
	uvdim.y = uvheight;
}

int Sprite::frame(int f)
{
	int w = 1.0f / uvdim.x;
	int h = 1.0f / uvdim.y;

	if (f >= w*h) {
		/// TODO take modulo to wrap around?
		_frame = 0;
		return _frame;
	}

	int ypos=f/w;
	int xpos=f%w;

	uvoffset.x = xpos * uvdim.x;
	uvoffset.y = ypos * uvdim.y;

	_frame = f;

	return _frame;
}
