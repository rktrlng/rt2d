/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene14.h"

Scene14::Scene14() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene14: Tetris");

	starty = 34;
	rot = 0;
	timestep = 25;
	rowscleared = 0;

	timer.start();

	// create Canvas
	canvas = new Canvas(16); // pixelsize
	layers[0]->addChild(canvas);

	left = canvas->width()/2 - field.fieldwidth/2;
	right = canvas->width()/2 + field.fieldwidth/2;
	top = canvas->height()/2 + field.fieldheight/2;
	bottom = canvas->height()/2 - field.fieldheight/2;

	field.reset();

	preparePixelSprites();

	createNewBlock();
}


Scene14::~Scene14()
{
	layers[0]->removeChild(canvas);
	delete canvas;

	block.pixels.clear();
	pixelsprites.clear();
}

void Scene14::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	std::stringstream ss;
	ss << "Scene14: Tetris (rows cleared: " << rowscleared << ")";
	text[0]->message(ss.str());

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[10]->message(""); // clear player click count message

	// ###############################################################
	// Update and draw only when it's time
	// ###############################################################
	static int counter = 0;
	float tsec = timer.seconds();
	if (tsec > 0.01 - deltaTime) { // 0.01 is 100 fps
		if (counter%timestep == 0) {
			canvas->fill(canvas->backgroundcolor);
			drawField();
			int r = findFullRow();
			if (r != -1) {
				clearRow(r);
			}
			updateBlock();
		}

		// restart frametimer
		timer.start();
		counter++;
	}

	// ###############################################################
	// Input
	// ###############################################################
	if (input()->getKeyDown( KeyCode::Up )) {
		rot--; if (rot<0) {rot=3;}
		if (active_block != 3) { // 3 is the 2x2 shape. don't rotate this one.
			PixelSprite spr = pixelsprites[active_block].rotated(rot * HALF_PI);
			spr.position = block.position;
			block = spr;
		}
	}
	if (input()->getKeyDown( KeyCode::Left )) {
		block.position.x--;
		if (block.position.x <= left) { block.position.x = left; }
	}
	if (input()->getKeyDown( KeyCode::Right )) {
		block.position.x++;
		if (block.position.x >= right-1) { block.position.x = right-1; }
	}
	if (input()->getKeyDown( KeyCode::Down )) {
		timestep = 4;
	}
	if (input()->getKeyUp( KeyCode::Down )) {
		timestep = 25;
	}
}

void Scene14::clearRow(int row)
{
	int counter = 0;
	for (int y = 0; y < field.fieldheight-1; y++) {
		for (int x = 0; x < field.fieldwidth; x++) {
			if (y >= row) {
				// row is the row to be cleared, copy pixels from row above
				field.cells[counter].color = field.cells[counter+field.fieldwidth].color;
			}
			counter++;
		}
	}
}

void Scene14::drawField()
{
	int counter = 0;
	for (int y = bottom; y < top-1; y++) {
		for (int x = left; x < right; x++) {
			// fill canvas with pixels from field
			canvas->setPixel(x, y, field.cells[counter].color);
			counter++;
		}
	}
}

int Scene14::findFullRow()
{
	// check each row of pixels in field
	// if there are no gaps, it's a full line
	int counter = 0;
	for (int y = bottom; y < top-1; y++) {
		int gapfound = 0; // assume a full row
		for (int x = left; x < right; x++) {
			// find a gap in this row
			if( field.cells[counter].color == field.clearcolor ) {
				gapfound = 1; // nope, not a full row
			}
			counter++;
		}
		// what to do when there's a full row
		if (gapfound == 0) {
			rowscleared++;
			return y-bottom; // the line that has no gaps
		}

	}
	return -1;
}

void Scene14::updateBlock()
{
	int canmovedownblock = 0;
	int canmovedownpixel = 1;
	size_t s = block.pixels.size();
	for (size_t i = 0; i < s; i++) {
		// calculate position of pixel relative to field
		Pointi p = block.pixels[i].position + block.position;
		Pointi posinfield = p - Pointi(left, bottom);
		//find the index of this pixel in the field
		int pixelindex = (posinfield.y * field.fieldwidth) + posinfield.x;
		int rowbelow = pixelindex-field.fieldwidth;
		if (rowbelow >= 0) {
			if ( field.cells[rowbelow].color == field.clearcolor ) {
				//allow canmovedownpixel to stay 1 (do nothing)
			} else {
				canmovedownpixel = 0;
			}
		} else {
			canmovedownpixel = 0;
		}
	}

	if (canmovedownpixel == 1) {
		canmovedownblock = 1;
	}

	if (canmovedownblock) {
		block.position.y--;
	} else {
		// copy pixels from block to field
		for (size_t i = 0; i < s; i++) {
			Pointi p = block.pixels[i].position + block.position;
			Pointi posinfield = p - Pointi(left, bottom);
			int pixelindex = (posinfield.y * field.fieldwidth) + posinfield.x;
			if (pixelindex >= 0) {
				int x = pixelindex%field.fieldwidth;
				int y = pixelindex/field.fieldwidth;
				field.cells[pixelindex] = block.pixels[i];
				field.cells[pixelindex].position = Pointi(x, y);
			}
		}

		canvas->drawSprite(block);

		createNewBlock();
	}

	canvas->drawSprite(block);
}

void Scene14::createNewBlock()
{
	active_block = rand()%pixelsprites.size();
	block = pixelsprites[active_block];
	block.position = Pointi(canvas->width()/2, starty);
	rot = 0;
}


// ###############################################################
// Predefined PixelSprites
// ###############################################################
void Scene14::preparePixelSprites()
{
	char jshapearray[6] = { // 3*2
		2,2,2,
		0,0,2
	};
	PixelSprite jshape;
	jshape.init(jshapearray, 3, 2);
	pixelsprites.push_back(jshape);

	char lshapearray[6] = { // 3*2
		3,3,3,
		3,0,0
	};
	PixelSprite lshape;
	lshape.init(lshapearray, 3, 2);
	pixelsprites.push_back(lshape);

	char ishapearray[4] = { // 4*1
		4,4,4,4
	};
	PixelSprite ishape;
	ishape.init(ishapearray, 4, 1);
	pixelsprites.push_back(ishape);

	char oshapearray[4] = { // 2*2
		5,5,
		5,5
	};
	PixelSprite oshape;
	oshape.init(oshapearray, 2, 2);
	pixelsprites.push_back(oshape);

	char sshapearray[6] = { // 3*2
		0,6,6,
		6,6,0
	};
	PixelSprite sshape;
	sshape.init(sshapearray, 3, 2);
	pixelsprites.push_back(sshape);

	char tshapearray[6] = { // 3*2
		7,7,7,
		0,7,0
	};
	PixelSprite tshape;
	tshape.init(tshapearray, 3, 2);
	pixelsprites.push_back(tshape);

	char zshapearray[6] = { // 3*2
		8,8,0,
		0,8,8
	};
	PixelSprite zshape;
	zshape.init(zshapearray, 3, 2);
	pixelsprites.push_back(zshape);
}
