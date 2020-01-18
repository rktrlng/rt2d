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

void Canvas::drawLine(Vector2f from, Vector2f to, RGBAColor color) {
	float x0 = from.x;
	float y0 = from.y;
	float x1 = to.x;
	float y1 = to.y;

	bool steep = false;
	if (std::abs(x0-x1) < std::abs(y0-y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1-x0;
	int dy = y1-y0;
	int derror2 = std::abs(dy)*2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			this->setPixel(y, x, color);
		} else {
			this->setPixel(x, y, color);
		}
		error2 += derror2;

		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx*2;
		}
	}
}
