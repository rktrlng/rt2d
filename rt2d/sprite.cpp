/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <iostream>

#include <rt2d/rt2dconfig.h>
#include <rt2d/sprite.h>

Sprite::Sprite()
{
	_texturename = AUTOGENWHITE;

	_fragmentshader = SPRITEFRAGMENTSHADER;
	_vertexshader = SPRITEVERTEXSHADER;

	spriteposition = Point3(0.0f, 0.0f, 0.0f); // spritebatch only
	spriterotation = Point3(0.0f, 0.0f, 0.0f); // spritebatch only
	spritescale = Point3(1.0f, 1.0f, 1.0f); // spritebatch only

	pivot = Point2(0.5f, 0.5f);
	uvdim = Point2(1.0f, 1.0f);
	uvoffset = Point2(0.0f, 0.0f);
	size = Point2(0, 0);

	for (size_t i = 0; i < 8; i++) {
		customParams[i] = Point3(0.0f, 0.0f, 0.0f);
	}

	_palette = nullptr;

	_frame = 0;

	_filter = DEFAULTFILTER;
	_wrap = DEFAULTWRAP;

	_dyntexture = nullptr;
	_dynamic = false;

	_circlemesh = 0; // false
	_which = -1; // disabled

	_useculling = 0;

	color = RGBAColor(255, 255, 255, 255);
}

Sprite::~Sprite()
{
	//if (_dyntexture != nullptr) {
	// TODO this leaks the dynamic textures (get rid of !dynamic)
	if (_dyntexture != nullptr && !_dynamic) {
		delete _dyntexture;
		_dyntexture = nullptr;
	}

	if (_palette != nullptr) {
		delete _palette;
		_palette = nullptr;
	}
}

void Sprite::setPalette(const std::string& filename)
{
	if (_palette != nullptr) {
		delete _palette;
		_palette = nullptr;
	}
	_palette = new Texture();
	_palette->loadTGAImage(filename, 0, 0, 1); // filename, filter, wrap, dimension
}

void Sprite::setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight)
{
	this->setupSprite(filename, pivotx, pivoty, uvwidth, uvheight, DEFAULTFILTER, DEFAULTWRAP);
}

void Sprite::setupCircleSprite(const std::string& filename, int radius, int segments)
{
	this->setupSegmentSprite(filename, radius, segments, -1);
}

void Sprite::setupSegmentSprite(const std::string& filename, int radius, int segments, int which)
{
	_texturename = filename;
	_circlemesh = segments; // only a single segment (triangle)
	_which = which; // which segment

	_filter = DEFAULTFILTER;
	_wrap = DEFAULTWRAP;

	size.x = radius * 2;
	size.y = radius * 2;
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
	if (_dyntexture != nullptr) {
		delete _dyntexture;
		_dyntexture = nullptr;
	}

	_filter = pixels->filter;
	_wrap = pixels->wrap;

	size.x = pixels->width;
	size.y = pixels->height;

	_dyntexture = new Texture();
	_dyntexture->createFromBuffer(pixels);
	_dynamic = true;
}

void Sprite::setupSpriteTGAPixelBuffer(const std::string& filename, int filter, int wrap)
{
	std::cout << "Sprite::setupSpriteByPixelBuffer() " <<  std::endl;
	if (_dyntexture != nullptr) {
		delete _dyntexture;
		_dyntexture = nullptr;
	}

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
		uvoffset.x = 0;
		uvoffset.y = 0;
		return _frame;
	}

	int ypos=f/w;
	int xpos=f%w;

	uvoffset.x = xpos * uvdim.x;
	uvoffset.y = ypos * uvdim.y;

	_frame = f;

	return _frame;
}
