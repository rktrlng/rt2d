/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 *
 * https://en.wikipedia.org/wiki/Maze_generation_algorithm
 * recursive backtracker
 */

#include "scene18.h"

Scene18::Scene18() : SuperScene()
{
	srand((unsigned)time(nullptr));

	t.start();

	text[0]->message("Scene18: Maze generation [SPACE]=reset");

	gridwidth = 32;
	gridheight = 32;
	cellwidth = 16;
	cellheight = 16;

	// create grid
	grid = new BasicEntity();
	//grid->addGrid("assets/mazewalls.tga", 4, 4, gridwidth, gridheight, cellwidth, cellheight);
	grid->addGrid("assets/mazeroads.tga", 4, 4, gridwidth, gridheight, cellwidth, cellheight);
	// center on screen
	Point2 pos = Point2(SWIDTH/2-(gridwidth*cellwidth)/2, SHEIGHT/2-(gridheight*cellheight)/2);
	grid->position = pos;
	layers[0]->addChild(grid);

	this->reset();
}


Scene18::~Scene18()
{
	layers[0]->removeChild(grid);
	delete grid;
}

void Scene18::update(float deltaTime)
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

	static bool backtracking = false;
	if (t.seconds() > 0.005f)
	{
		// loop over grid and draw each sprite
		std::vector<Sprite*> spritebatch = grid->spritebatch();
		int counter = 0;
		int unvisitedcounter = 0;
		for (int y=0; y<gridheight ; y++) {
			for (int x=0; x<gridwidth; x++) {
				// draw the correct cell
				int fr = (int) cells[counter]->walls.to_ulong();
				spritebatch[counter]->frame(fr);

				// check visited, keep counter
				if (cells[counter]->visited) {
					spritebatch[counter]->color = WHITE;
				} else {
					//grid->spritebatch()[counter]->color = GREEN;
					unvisitedcounter++;
				}

				// color current cell
				if (cells[counter] == current) {
					if (backtracking) {
						spritebatch[counter]->color = RED;
					} else {
						spritebatch[counter]->color = BLUE;
					}
				}

				counter++;
			}
		}

		spritebatch[0]->color = WHITE; // first cell

		// no more unvisited cells. We're done.
		if (unvisitedcounter == 0) {
			text[2]->message("done!");
			this->export_grid();
		} else {
			text[2]->message("generating...");
		}

		// make 'current' find the next place to be
		current->visited = true;
		// STEP 1: while there is a neighbour...
		MCell* next = this->getRandomUnvisitedNeighbour(current);
		if (next != nullptr) { // there's still an unvisited neighbour. We're not stuck
			backtracking = false;
			next->visited = true;

			// STEP 2
			stack.push_back(current); // drop a breadcrumb on the stack

			// STEP 3
			this->removeWalls(current, next); // break through the wall

			// STEP 4
			current = next;
		} else { // we're stuck! backtrack our steps...
			backtracking = true;
			if (stack.size() > 0) {
				current = stack.back(); // make previous our current cell
				stack.pop_back(); // remove from the stack (eat the breadcrumb)
			}
		}

		t.start();
	}

}

void Scene18::export_grid()
{
	static int first_time = 1;
	if (first_time == 1) {
		first_time = 0;
		std::cout << "export " << cells.size() << std::endl;
		int counter = 0;
		for (int y=0; y<gridheight; y++) {
			for (int x=0; x<gridwidth; x++) {
				int fr = (int) cells[counter]->walls.to_ulong();

				if (fr < 10) { std::cout << " "; }
				std::cout << fr << ",";

				counter++;
			}
			std::cout << std::endl;
		}
	}
}

void Scene18::removeWalls(MCell* c, MCell* n)
{
	int dx = c->col - n->col;
	if (dx == 1) {
		c->walls[3] = 0; // left
		n->walls[1] = 0; // right
	} else if (dx == -1) {
		c->walls[1] = 0;
		n->walls[3] = 0;
	}

	int dy = c->row - n->row;
	if (dy == 1) {
		c->walls[0] = 0; // top
		n->walls[2] = 0; // bottom
	} else if (dy == -1) {
		c->walls[2] = 0;
		n->walls[0] = 0;
	}
}

int getindex(int x, int y, int w, int h) {
	if ( x>=0 && x<w && y>=0 && y<h) {
		int i = (y * w) + x;
		return i;
	}
	return -1;
}

MCell* Scene18::getRandomUnvisitedNeighbour(MCell* mc)
{
	// keep a list of possible neighbours
	std::vector<MCell*> neighbours;
	int x = mc->col;
	int y = mc->row;
	int index = 0;

	// look right
	index = getindex(x+1,y,gridwidth,gridheight);
	if( index != -1 ) {
		if (!cells[index]->visited) {
			neighbours.push_back(cells[index]);
		}
	}
	// look left
	index = getindex(x-1,y,gridwidth,gridheight);
	if( index != -1 ) {
		if (!cells[index]->visited) {
			neighbours.push_back(cells[index]);
		}
	}
	// look down
	index = getindex(x,y+1,gridwidth,gridheight);
	if( index != -1 ) {
		if (!cells[index]->visited) {
			neighbours.push_back(cells[index]);
		}
	}
	// look up
	index = getindex(x,y-1,gridwidth,gridheight);
	if( index != -1 ) {
		if (!cells[index]->visited) {
			neighbours.push_back(cells[index]);
		}
	}

	// there's a valid neighbour!
	if (neighbours.size() > 0) {
		// pick one from the list
		int r = rand()%neighbours.size();
		return neighbours[r];
	}

	// no neighbours
	return nullptr;
}

void Scene18::clear()
{
	int s = cells.size();
	if (s>0) {
		for (int i = 0; i < s; i++) {
			delete cells[i]; // we did 'new' when we pushed the cell
			cells[i] = nullptr;
		}
		cells.clear();
	}
	stack.clear(); // just a list of pointers to some cells. Don't delete here.
}

void Scene18::reset()
{
	this->clear();

	// create all cells and init grid
	int counter = 0;
	for (int y=0; y<gridheight ; y++) {
		for (int x=0; x<gridwidth; x++) {
			MCell* mc = new MCell();
			mc->col = x;
			mc->row = y;
			mc->walls = 15; // 0b1111 all walls
			mc->visited = false;
			cells.push_back(mc);

			int fr = (int) cells[counter]->walls.to_ulong();
			grid->spritebatch()[counter]->frame(fr);

			grid->spritebatch()[counter]->color = GRAY;
			counter++;
		}
	}
	current = cells[0];
}
