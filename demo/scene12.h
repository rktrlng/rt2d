/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE12_H
#define SCENE12_H

#include <vector>
#include <rt2d/stringutil.h>
#include <rt2d/timer.h>
#include <rt2d/vectorx.h>
#include "superscene.h"
#include "canvas.h"

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

class Scene12: public SuperScene
{
public:
	Scene12();
	virtual ~Scene12();

	virtual void update(float deltaTime);

private:
	PixelSprite sprite;
	PixelSprite bob;

	RGBAColor backgroundcolor;
	Canvas* canvas;
	Timer timer;

	void drawSprite(const PixelSprite& spr);
	void clearSprite(const PixelSprite& spr);
};

#endif /* SCENE12_H */
