/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene17.h"

Scene17::Scene17() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene17: Reaction Diffusion [CLICK]=add Drop [SPACE]=reset [S]=save image");

	// create Canvas
	pixelsize = 4;
	canvas = new Canvas(pixelsize);
	canvas->sprite()->texture()->pixels()->filter = 3;
	layers[0]->addChild(canvas);

	w = canvas->width();
	h = canvas->height();
	std::cout << w << "," << h << std::endl;

	dropsize = 5;
	mode = 1;
	this->handleModes();

	this->reset();
}


Scene17::~Scene17()
{
	layers[0]->removeChild(canvas);
	delete canvas;
}

void Scene17::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[10]->message(""); // clear player click count message

	this->handleModes();

	if (input()->getKeyDown(KeyCode::Space)) {
		this->reset();
	}

	if (input()->getMouseDown( 0 )) {
		int mousex = floor(input()->getMouseX()/pixelsize);
		int mousey = floor(input()->getMouseY()/pixelsize);
		this->addDrop(mousex, h-mousey);
	}

	if (input()->getKeyDown(KeyCode::S)) {
		canvas->sprite()->texture()->writeTGAImage();
	}

	// ###############################################################
	// Update and draw as fast as you can
	// ###############################################################
	// update 'next' field
	RDCell c;
	std::vector<RDCell> next = std::vector<RDCell>(w*h, c);

	// http://www.karlsims.com/rd.html
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			size_t index = (y * w) + x;
			float a = field[index].A;
			float b = field[index].B;
			next[index].A = a +
							(dA * laplaceA(x, y)) -
							(a * b * b) +
							(feed * (1 - a));

			next[index].B = b +
							(dB * laplaceB(x, y)) +
							(a * b * b) -
							((k + feed) * b);
		}
	}

	// draw 'next' field
	for (size_t y = 0; y < h; y++) {
		for (size_t x = 0; x < w; x++) {
			size_t index = (y * w) + x;
			RGBAColor color;
			int grayscale = 0;
			if (grayscale) {
				float value = 255 - (next[index].A*255);
				color = RGBAColor(value, value, value, 255);
			} else {
				HSVColor hsv = HSVColor(next[index].A, 1.0f, 1.0f);
				color = Color::HSV2RGBA(hsv);

			}
			canvas->setPixel(x, y, color);
		}
	}

	field = next;
}

void Scene17::reset()
{
	// create field (filled with A)
	RDCell c;
	field = std::vector<RDCell>(w*h, c);
}

void Scene17::handleModes()
{
	//http://mrob.com/pub/comp/xmorphia/pearson-classes.html

	if (input()->getKeyDown(KeyCode::Alpha1)) { mode = 1; }
	if (input()->getKeyDown(KeyCode::Alpha2)) { mode = 2; }
	if (input()->getKeyDown(KeyCode::Alpha3)) { mode = 3; }
	if (input()->getKeyDown(KeyCode::Alpha4)) { mode = 4; }

	dA = 1.0f; // diffusion rate A
	dB = 0.5f; // diffusion rate B

	// "coral growth" simulation (f=.0545, k=.062)
	if (mode == 1) {
		feed = 0.0545; // feed rate
		k = 0.062; // kill rate
	}
	// "string" simulation (f=.0385, k=.062)
	if (mode == 2) {
		feed = 0.0385; // feed rate
		k = 0.062; // kill rate
	}
	// "mitosis" simulation (f=.0367, k=.0649)
	if (mode == 3) {
		feed = 0.0367; // feed rate
		k = 0.0649; // kill rate
	}
	// "test" simulation
	if (mode == 4) {
		feed = 0.0745; // feed rate
		k = 0.0615; // kill rate
		dropsize = 10;
	}
}

void Scene17::addDrop(int x_, int y_)
{
	int maxindex = field.size();
	for (int y = y_-dropsize; y < y_+dropsize; y++) {
		for (int x = x_-dropsize; x < x_+dropsize; x++) {
			int index = (y * w) + x;
			if (index >= 0 && index < maxindex) {
				field[index].B = 1.0f;
			}
		}
	}
}

Pointi Scene17::wrap(Pointi n)
{
	Pointi w = n;

	if (n.x < 0) { w.x = canvas->width()-1; }
	if (n.x > canvas->width()-1) { w.x = 0; }
	if (n.y < 0) { w.y = canvas->height()-1; }
	if (n.y > canvas->height()-1) { w.y = 0; }

	return w;
}

float Scene17::laplaceA(int x, int y)
{
	float sumA = 0.0f;
	Pointi n;

	n = this->wrap(Pointi(x+0, y+0));
	sumA += field[getIdFromPos(n.x,n.y)].A * -1.0f;
	n = this->wrap(Pointi(x-1, y+0));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.2f;
	n = this->wrap(Pointi(x+1, y+0));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.2f;
	n = this->wrap(Pointi(x+0, y+1));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.2f;
	n = this->wrap(Pointi(x+0, y-1));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.2f;
	n = this->wrap(Pointi(x-1, y+1));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.05f;
	n = this->wrap(Pointi(x+1, y+1));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.05f;
	n = this->wrap(Pointi(x+1, y-1));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.05f;
	n = this->wrap(Pointi(x-1, y-1));
	sumA += field[getIdFromPos(n.x,n.y)].A * 0.05f;
	return sumA;
}

float Scene17::laplaceB(int x, int y)
{
	float sumB = 0.0f;
	Pointi n;

	n = this->wrap(Pointi(x+0, y+0));
	sumB += field[getIdFromPos(n.x,n.y)].B * -1.0f;
	n = this->wrap(Pointi(x-1, y+0));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.2f;
	n = this->wrap(Pointi(x+1, y+0));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.2f;
	n = this->wrap(Pointi(x+0, y+1));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.2f;
	n = this->wrap(Pointi(x+0, y-1));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.2f;
	n = this->wrap(Pointi(x-1, y+1));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.05f;
	n = this->wrap(Pointi(x+1, y+1));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.05f;
	n = this->wrap(Pointi(x+1, y-1));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.05f;
	n = this->wrap(Pointi(x-1, y-1));
	sumB += field[getIdFromPos(n.x,n.y)].B * 0.05f;
	return sumB;
}
