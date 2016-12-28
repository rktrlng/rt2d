/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <rt2d/entity.h>

class Canvas: public Entity
{
	public:
		Canvas();
		Canvas(int pixelsize);
		virtual ~Canvas();

		virtual void update(float deltaTime);
		void init(int pixelsize);
		void setPixel(int x, int y, RGBAColor color);
		void clear(RGBAColor color);

		int width;
		int height;

	private:
		PixelBuffer* framebuffer;
};

#endif /* CANVAS_H */
