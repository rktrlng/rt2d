/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
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

	int border = 0;

	// width, height, bitdepth, filter, wrap
	PixelBuffer* tmp = new PixelBuffer((SWIDTH/pixelsize)-border, (SHEIGHT/pixelsize)-border, 3, 0, 0);
	this->addDynamicSprite(tmp);
	delete tmp;

	// get the pixels from the texture and call it the global framebuffer
	this->_framebuffer = this->sprite()->texture()->pixels();

	this->_width = SWIDTH / pixelsize;
	this->_height = SHEIGHT / pixelsize;
}

void Canvas::setPixel(int x, int y, RGBAColor color)
{
	this->_framebuffer->setPixel(x, y, color);
}

void Canvas::clear(RGBAColor color)
{
	// fill framebuffer with color
	for (long y=0; y<_framebuffer->height; y++) {
		for (long x=0; x<_framebuffer->width; x++) {
			this->setPixel(x, y, color);
		}
	}
}
