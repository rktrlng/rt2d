/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE04_H
#define SCENE04_H

#include <vector>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene04: public SuperScene
{
public:
	Scene04();
	virtual ~Scene04();

	virtual void update(float deltaTime);

private:
	BasicEntity* pixel_container;
	Timer t;
	Timer rt;

	void spectrumPixels(PixelBuffer* pixels, int filter);
	void randomPixels(PixelBuffer* pixels, int filter);
	void rainbowPixels(PixelBuffer* pixels, float step, int filter);
	void checkerPixels(PixelBuffer* pixels, int cellwidth, RGBAColor a, RGBAColor b);
	void perlinNoisePixels(PixelBuffer* pixels, int wood = 0);
};

#endif /* SCENE04_H */
