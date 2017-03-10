/**
  * This file is part of RT2D, a 2D OpenGL framework.
  *
  * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
  *   - Initial commit
  */

#include "canvas.h"

Canvas::Canvas()
	: Entity()
{
	this->init(16);
}

Canvas::Canvas(int pixelsize)
	: Entity()
{
	this->init(pixelsize);
}

Canvas::~Canvas()
{

}

void Canvas::update(float deltaTime)
{

}

void Canvas::init(int pixelsize)
{
	this->position = Point2(SWIDTH/2, SHEIGHT/2);
	this->scale = Point2(pixelsize, pixelsize);

	// width, height, bitdepth, filter, wrap
	PixelBuffer tmp = PixelBuffer(SWIDTH/pixelsize, SHEIGHT/pixelsize, 4, 0, 0);
	this->addDynamicSprite(&tmp);

	// get the pixels from the texture and make the framebuffer point to it
	this->_framebuffer = this->sprite()->texture()->pixels();

	this->_width = SWIDTH / pixelsize;
	this->_height = SHEIGHT / pixelsize;

	backgroundcolor = RGBAColor(0, 0, 0, 0);
	this->fill(backgroundcolor);
}

void Canvas::setPixel(int x, int y, RGBAColor color)
{
	this->_framebuffer->setPixel(x, y, color);
}

RGBAColor Canvas::getPixel(int x, int y)
{
	return this->_framebuffer->getPixel(x, y);
}

void Canvas::clearPixel(int x, int y)
{
	this->_framebuffer->setPixel(x, y, backgroundcolor);
}

void Canvas::fill(RGBAColor color)
{
	// fill framebuffer with color
	for (long y=0; y<_framebuffer->height; y++) {
		for (long x=0; x<_framebuffer->width; x++) {
			this->setPixel(x, y, color);
		}
	}
}

void Canvas::drawSprite(const PixelSprite& spr)
{
	size_t s = spr.pixels.size();
	for (size_t i = 0; i < s; i++) {
		this->setPixel(spr.pixels[i].position.x + spr.position.x, spr.pixels[i].position.y + spr.position.y, spr.pixels[i].color);
	}
}

void Canvas::clearSprite(const PixelSprite& spr)
{
	size_t s = spr.pixels.size();
	for (size_t i = 0; i < s; i++) {
		this->clearPixel(spr.pixels[i].position.x + spr.position.x, spr.pixels[i].position.y + spr.position.y);
	}
}
