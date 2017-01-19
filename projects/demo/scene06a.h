/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE06A_H
#define SCENE06A_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"

struct HexField : Entity {

	virtual void update(float deltaTime)
	{
		// empty
	};

	void setupHexGrid(const std::string& filename, int u, int v, size_t width, size_t height, int r)
	{
		//deleteSpritebatch();
		cols = width;
		rows = height;
		radius = r;
		float xmult = 0.75f;
		float ymult = sin(60*DEG_TO_RAD);
		float uvwidth = 1.0f / u;
		float uvheight = 1.0f / v;

		RGBAColor color = RGBAColor(0,0,255,255); // blue
		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				Sprite* s = new Sprite();

				s->setupCircleSprite(filename, radius/2, 6);
				s->uvdim = Point2(uvwidth, uvheight);
				s->filter(0);
				s->wrap(0);
				s->useCulling(1);

				s->spriteposition.x = x * radius * xmult;
				if (x%2==0) {
					s->spriteposition.y = y * radius * ymult;
				} else {
					s->spriteposition.y = y * radius * ymult + (ymult*radius/2);
				}
				s->spriteposition += Point2(radius, radius);

				s->color = color;
				color = Color::rotate(color, 1.0f/cols);

				int n = u*v;
				s->frame(rand()%n);
				s->uvoffset += Point2(-0.375f, -0.375f); // compensate for circle UV's

				_spritebatch.push_back(s);
			}
		}
	}

	size_t findnearest(Point2 pos)
	{
		size_t n = 0;
		float shortest = 100000.0f;
		size_t counter = 0;
		for (size_t y = 0; y < rows; y++) {
			for (size_t x = 0; x < cols; x++) {
				Vector2 p = Vector2(_spritebatch[counter]->spriteposition, pos);
				float d = p.getLength();
				if (d < shortest) {
					shortest = d;
					n = counter;
				}
				counter++;
			}
		}
		return n;
	}

	size_t cols;
	size_t rows;
	int radius;
};

class Scene06a: public SuperScene
{
public:
	Scene06a();
	virtual ~Scene06a();

	virtual void update(float deltaTime);

private:
	HexField* hexfield;
};

#endif /* SCENE06A_H */
