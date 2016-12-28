/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <rt2d/entity.h>

struct Pixel {
	Point_t<int> position;
	RGBAColor color;

	Pixel(Point_t<int> pos, RGBAColor c) { position = pos; color = c; };
};

struct PixelSprite {
	std::vector<Pixel> pixels;
	Point_t<int> position;

	PixelSprite rotation(float a) {
		PixelSprite copy;
		copy.position = this->position;
		size_t s = pixels.size();
		for (size_t i = 0; i < s; i++) {
			VectorX_t<float> v = VectorX_t<float>(pixels[i].position.x, pixels[i].position.y, 0);
			v.rotate(a);
			int x = nearbyint(v.x+0.1); // rounding up a bit works a little better
			int y = nearbyint(v.y+0.1);
			copy.pixels.push_back(Pixel(Point_t<int>(x, y), pixels[i].color));
		}
		return copy;
	};
};

class Canvas: public Entity
{
	public:
		Canvas();
		Canvas(int pixelsize);
		virtual ~Canvas();

		virtual void update(float deltaTime);
		void init(int pixelsize);
		void setPixel(int x, int y, RGBAColor color);
		void clearPixel(int x, int y);
		void fill(RGBAColor color);

		int width() { return _width; };
		int height() { return _height; };

		void drawSprite(const PixelSprite& spr);
		void clearSprite(const PixelSprite& spr);
		
		RGBAColor backgroundcolor;

	private:
		PixelBuffer* _framebuffer;

		int _width;
		int _height;
};

#endif /* CANVAS_H */
