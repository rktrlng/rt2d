/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene11.h"

Scene11::Scene11() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene11: Snake");

	timer.start();

	// create Canvas
	canvas = new Canvas(32); // pixelsize
	layers[0]->addChild(canvas);

	// clean up and reset
	resetSnake();
}


Scene11::~Scene11()
{
	layers[0]->removeChild(canvas);
	delete canvas;

	snake.clear();
}

void Scene11::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	//text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[10]->message(""); // clear player click count message

	// ###############################################################
	// move snake head
	// ###############################################################
	if (input()->getKeyDown(KeyCode::Up)) {
		snake[0].velocity = UP;
	}
	if (input()->getKeyDown(KeyCode::Down)) {
		snake[0].velocity = DOWN;
	}
	if (input()->getKeyDown(KeyCode::Left)) {
		snake[0].velocity = LEFT;
	}
	if (input()->getKeyDown(KeyCode::Right)) {
		snake[0].velocity = RIGHT;
	}

	// ###############################################################
	// Update and draw only when it's time
	// ###############################################################
	float tsec = timer.seconds();
	if (tsec > 0.1 - deltaTime) { // 0.1 is 10 fps
		// count the snake blocks
		int s = snake.size();

		int score = s-1;
		std::stringstream scoretxt;
		scoretxt << "score: " << score;
		text[2]->message(scoretxt.str());

		// clear snake to background
		for (int i=0; i<s; i++) {
			canvas->clearPixel(snake[i].position.x, snake[i].position.y);
		}

		// update each block in snake. Check from back to front!
		for (int i=s-1; i>=0; i--) {
			// update position
			snake[i].position += snake[i].velocity;

			// follow the leader
			if (i>0) {
				snake[i].velocity = snake[i-1].velocity;
			}
		}

		// draw each block in snake
		for (int i=0; i<s; i++) {
			// color pixels in canvas
			canvas->setPixel(snake[i].position.x, snake[i].position.y, snake[i].color );
		}

		// draw target
		canvas->clearPixel(target.position.x, target.position.y);
		canvas->setPixel(target.position.x, target.position.y, target.color);

		// head hits target!
		if (target.position == snake[0].position) {
			addBlockToSnake(); // add to the snake tail
		}

		// check self collisions
		for (int i = 0; i < s-1; i++) {
			if ( snake[0].position == snake[i+1].position ) {
				std::cout << "self collision!! score " << score << std::endl;
				resetSnake();
			}
		}

		// check boundaries
		if (snake[0].position.x < 0 ||
			snake[0].position.x > canvas->width()-1 ||
			snake[0].position.y < 0 ||
			snake[0].position.y > canvas->height()-1
		) {
			std::cout << "boundaries collision!! score " << score << std::endl;
			resetSnake();
		}

		timer.start();
	}
}


void Scene11::addBlockToSnake()
{
	// snake always has a head, so s is at least 1
	int snakesize = snake.size();
	Block b;
	// get direction from 'front' neighbour
	b.velocity = snake[snakesize-1].velocity;
	b.position = snake[snakesize-1].position - b.velocity;
	b.color = BLUE;
	// add it to the list of blocks
	snake.push_back(b);

	placeTarget();
}

void Scene11::placeTarget()
{
	// find a new spot for target (don't place it inside the snake)
	canvas->clearPixel(target.position.x, target.position.y);
	Point_t<int> targetPos = snake[0].position; // force a better spot
	while (positionIsInSnake(targetPos)) {
		targetPos = Point_t<int>(rand()%canvas->width(), rand()%canvas->height());
	}
	target.position = targetPos;
	target.color = GREEN;
}

bool Scene11::positionIsInSnake(Point_t<int> testPoint)
{
	int s = snake.size();
	for (int i = 0; i < s; i++) {
		if (snake[i].position == testPoint) {
			return true;
		}
	}
	return false;
}

void Scene11::resetSnake()
{
	int s = snake.size();

	// clear each snake block from the canvas
	for (int i = 0; i < s; i++) {
		canvas->clearPixel(snake[i].position.x, snake[i].position.y);
	}
	snake.clear();

	// create 'head'
	Block b;
	b.position = Point_t<int>(canvas->width()/2, canvas->height()/2);
	b.velocity = RIGHT;
	b.color = RED;
	snake.push_back(b);

	placeTarget();
}
