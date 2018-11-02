/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE14_H
#define SCENE14_H

#include <vector>
#include <rt2d/timer.h>
#include <rt2d/vectorx.h>
#include <rt2d/canvas.h>
#include "superscene.h"

struct Field {
	int fieldwidth = 16;
	int fieldheight = 32;
	std::vector<Pixel> cells;
	RGBAColor clearcolor = RGBAColor(0,0,0,255);
	void reset() {
		for (int y = 0; y < fieldheight; y++) {
			for (int x = 0; x < fieldwidth; x++) {
				cells.push_back(Pixel(Point_t<int>(x,y), clearcolor));
			}
		}
	};
};


class Scene14: public SuperScene
{
public:
	Scene14();
	virtual ~Scene14();

	virtual void update(float deltaTime);

private:
	Field field;
	PixelSprite block;
	std::vector<PixelSprite> pixelsprites;
	int active_block;

	void preparePixelSprites();
	void createNewBlock();
	void drawField();
	void updateBlock();
	int findFullRow();
	void clearRow(int row);

	Canvas* canvas;
	Timer timer;

	int rot; // rotation of block (0,1,2,3)
	int starty; // startposition of block
	int timestep;
	int rowscleared;

	int left;
	int right;
	int top;
	int bottom;
};

#endif /* SCENE14_H */
