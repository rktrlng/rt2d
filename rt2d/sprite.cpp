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
	_texturename = AUTOGENWHITE;
	
	_fragmentshader = SPRITEFRAGMENTSHADER;
	_vertexshader = SPRITEVERTEXSHADER;
	
	pivot = Point2(0.5f, 0.5f);
	uvdim = Point2(1.0f, 1.0f);
	uvoffset = Point2(0.0f, 0.0f);
	size = Point2(0, 0);
	
	_frame = 0;
	
	_filter = 3;
	_wrap = 0;
	
	_dyntexture = NULL;
	_dynamic = false;
	
	color = RGBAColor(255, 255, 255, 255);
}

Sprite::~Sprite()
{
	//if (_dyntexture != NULL) {
	// TODO this leaks the dynamic textures (get rid of !dynamic)
	if (_dyntexture != NULL && !_dynamic) {
		delete _dyntexture;
		_dyntexture = NULL;
	}
}

void Sprite::setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight)
{
	this->setupSprite(filename, pivotx, pivoty, uvwidth, uvheight, DEFAULTFILTER, DEFAULTCLAMP);
}

void Sprite::setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap)
{
	_texturename = filename;
	
	_filter = filter;
	_wrap = wrap;

	pivot.x = pivotx;
	pivot.y = pivoty;

	// 1.00000 = 1x1 spritesheet (basic sprite)
	// 0.50000 = 2x2 spritesheet
	// 0.25000 = 4x4 spritesheet
	// 0.12500 = 8x8 spritesheet
	// 0.06250 = 16x16 spritesheet
	// 0.03125 = 32x32 spritesheet
	uvdim.x = uvwidth;
	uvdim.y = uvheight;
}

void Sprite::setupSpriteByPixelBuffer(PixelBuffer* pixels)
{
	std::cout << "Sprite::setupSpriteByPixelBuffer() " <<  std::endl;
	
	_texturename = "PixelBuffer";
	
	_filter = pixels->filter;
	_wrap = pixels->wrap;
	
	pivot.x = 0.5f;
	pivot.y = 0.5f;
	
	uvdim.x = 1.0f;
	uvdim.y = 1.0f;
	
	size.x = pixels->width;
	size.y = pixels->height;
	
	_dyntexture = new Texture();
	_dyntexture->createFromBuffer(pixels);
	_dynamic = true;
}

void Sprite::setupSpriteTGAPixelBuffer(const std::string& filename, int filter, int wrap)
{
	std::cout << "Sprite::setupSpriteByPixelBuffer() " <<  std::endl;
	
	_texturename = "dyn_" + filename;
	
	pivot.x = 0.5f;
	pivot.y = 0.5f;
	
	uvdim.x = 1.0f;
	uvdim.y = 1.0f;
	
	_dyntexture = new Texture();
	_dyntexture->loadTGAImage(filename, filter, wrap);
	_dynamic = true;
	
	size.x = (float) _dyntexture->width();
	size.y = (float) _dyntexture->height();
	
	_filter = filter;
	_wrap = wrap;
}

int Sprite::frame(int f)
{
	int w = 1.0f / uvdim.x;
	int h = 1.0f / uvdim.y;

	if (f >= w*h) {
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
