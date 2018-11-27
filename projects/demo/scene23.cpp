/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 *
 */

#include "scene23.h"

Scene23::Scene23() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene23: MineSweeper [SPACE]=reset");

	gridwidth = 24;
	gridheight = 24;
	cellwidth = 16;
	cellheight = 16;

	numMines = 80;

	// create grid
	grid = new BasicEntity();
	grid->addGrid("assets/minesweeper.tga", 4, 4, gridwidth, gridheight, cellwidth, cellheight);

	// center on screen
	grid->position = Point2(SWIDTH/2-(gridwidth*cellwidth)/2, SHEIGHT/2-(gridheight*cellheight)/2);

	layers[0]->addChild(grid);

	this->reset();
}


Scene23::~Scene23()
{
	layers[0]->removeChild(grid);
	delete grid;

	this->clear();
}

void Scene23::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do
	// - Escape key stops Scene
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	//text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[5]->message("");
	text[6]->message("");
	text[10]->message(""); // clear player click count message

	if (input()->getKeyDown(KeyCode::Space)) {
		reset();
	}

	std::vector<Sprite*> spritebatch = grid->spritebatch();
	if (input()->getMouseDown( 0 )) {
		int mousex = input()->getMouseX() - SWIDTH/2;
		int mousey = input()->getMouseY() - SHEIGHT/2;

		int s = cells.size();
		for (int i=0; i<s; i++) {
			Sprite* c = spritebatch[i];
			Point3 pos = c->spriteposition;

			int halfwidth = cellwidth/2;
			int halfheight = cellheight/2;
			int left = pos.x - halfwidth - (gridwidth*cellwidth/2);
			int right = pos.x + halfwidth - (gridwidth*cellwidth/2);
			int top = pos.y - halfheight - (gridheight*cellheight/2);
			int bottom = pos.y + halfheight - (gridheight*cellheight/2);

			if ( mousex > left && mousex < right && mousey > top && mousey < bottom ) {
				cells[i]->revealed = true;

				if (cells[i]->neighborCount == 0) {
					this->floodFill(cells[i]);
				}

				if (cells[i]->mine) {
					this->gameOver();
				}
			}
		}
	}

	// loop over grid and draw each sprite
	for (int y=0; y<gridheight ; y++) {
		for (int x=0; x<gridwidth; x++) {
			int index = this->getindex(x, y, gridwidth, gridheight);
			MSCell* msc = cells[index];

			// draw the correct cell
			if (!msc->revealed) {
				spritebatch[index]->frame(12); // square
			} else {
				if (msc->neighborCount != -1) {
					spritebatch[index]->frame(msc->neighborCount);
				} else {
					spritebatch[index]->frame(10);
				}
			}

			// draw borders
			if (msc->border) {
				spritebatch[index]->frame(13); // border
			}

			// if (msc->mine) {
			// 	spritebatch[index]->frame(14); // debugmine
			// }
		}
	}

}

void Scene23::reveal(MSCell* msc)
{
	msc->revealed = true;
	if (msc->neighborCount == 0) {
		this->floodFill(msc);
	}
}

void Scene23::floodFill(MSCell* msc)
{
	if ((msc->col > 0 && msc->col < gridwidth-1)
	 && (msc->row > 0 && msc->row < gridheight-1)) {
		for (int xoff = -1; xoff <= 1; xoff++) {
			int i = msc->col + xoff;
			for (int yoff = -1; yoff <= 1; yoff++) {
				int j = msc->row + yoff;
				int index = this->getindex(i,j,gridwidth,gridheight);
				MSCell* neighbor = cells[index];
				if (!neighbor->revealed) {
					this->reveal(neighbor);
				}
			}
		}
	}
}

void Scene23::gameOver()
{
	int s = gridwidth * gridheight;
	for (int i = 0; i < s; i++) {
		cells[i]->revealed = true;
	}
}

int Scene23::getindex(int x, int y, int w, int h)
{
	if ( x >= 0 && x < w && y >= 0 && y < h) {
		int i = (y * w) + x;
		return i;
	}
	return -1;
}

void Scene23::clear()
{
	int s = cells.size();
	if (s > 0) {
		for (int i = 0; i < s; i++) {
			delete cells[i];
			cells[i] = nullptr;
		}
		cells.clear();
	}
}

int Scene23::countMines(MSCell* msc) {
	if (msc->mine) {
		msc->neighborCount = -1;
		return -1;
	}

	int total = 0;
	if ((msc->col > 0 && msc->col < gridwidth-1)
	 && (msc->row > 0 && msc->row < gridheight-1)) {
		for (int xoff = -1; xoff <= 1; xoff++) {
			int i = msc->col + xoff;
			for (int yoff = -1; yoff <= 1; yoff++) {
				int j = msc->row + yoff;
				int index = this->getindex(i,j,gridwidth,gridheight);
				MSCell* neighbor = cells[index];
				if (neighbor->mine) {
					total++;
				}
			}
		}
	}

	return total;
}

void Scene23::reset()
{
	this->clear();

	// create all cells and init grid
	std::vector<Sprite*> batch = grid->spritebatch();
	int counter = 0;
	for (int y=0; y<gridheight ; y++) {
		for (int x=0; x<gridwidth; x++) {
			MSCell* msc = new MSCell();
			msc->col = x;
			msc->row = y;
			msc->neighborCount = 0;
		    msc->mine = false;
		    msc->revealed = false;
		    msc->border = false;
			cells.push_back(msc);

			batch[counter]->color = GRAY;
			counter++;
		}
	}

	// some random mines
	int s = gridwidth * gridheight;
	for (int i = 0; i <= numMines; i++) {
		int r = rand()%s;
		cells[r]->mine = true;
	}

	// reset borders
	for (int y=0; y<gridheight ; y++) {
		for (int x=0; x<gridwidth; x++) {
			int index = this->getindex(x,y,gridwidth,gridheight);
			MSCell* msc = cells[index];
			if (msc->col == 0 || msc->col == gridwidth-1 || msc->row == 0 || msc->row == gridheight-1) {
				msc->mine = false;
				msc->border = true;
			}
		}
	}

	// check neighbors
	for (int y=0; y<gridheight ; y++) {
		for (int x=0; x<gridwidth; x++) {
			int index = this->getindex(x,y,gridwidth,gridheight);
			MSCell* msc = cells[index];
			int mines = this->countMines(msc);
			msc->neighborCount = mines;
			//std::cout << mines << ",";
		}
		//std::cout << std::endl;
	}
}
