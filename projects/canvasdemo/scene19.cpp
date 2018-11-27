/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene19.h"

Scene19::Scene19() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene19: Diffusion-limited aggregation [SPACE]=reset");

	//text[4]->message("<SPACE> reset particles");
	//text[7]->message("FPS: ---");

	timer.start();

	// create Canvas
	canvas = new Canvas(8); // pixelsize
	canvas->sprite()->texture()->pixels()->wrap = 1;
	canvas->sprite()->texture()->pixels()->filter = 1;
	layers[0]->addChild(canvas);

	w = canvas->width();
	h = canvas->height();

	this->setup();
}


Scene19::~Scene19()
{
	layers[0]->removeChild(canvas);
	delete canvas;

	particles.clear();
	tree.clear();
}

void Scene19::clear()
{
	timer.start();

	canvas->fill(canvas->backgroundcolor);
	particles.clear();
	tree.clear();
}

void Scene19::setup()
{
	this->clear();

	// generate a number of particles with a random position
	unsigned int maxparticles = 800;
	for (unsigned int i = 0; i < maxparticles; i++) {
		Element p;
		p.position = Point2(rand()%w, rand()%h);
		p.color = RED;
		particles.push_back(p);
	}

	// generate initial tree
	Element p;
	p.position = Point2(w/5*2, h/2); p.color = RED; tree.push_back(p);
	p.position = Point2(w/5*3, h/2); p.color = RED; tree.push_back(p);
	p.position = Point2(w/2, h/2); p.color = RED; tree.push_back(p);
}

void Scene19::update(float deltaTime)
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

	// update
	float tsec = timer.seconds();
	if (tsec > 0.01f - deltaTime) { // 0.01f = 100fps
		this->updateDrawTree();
		this->updateDrawParticles();
		timer.start();
	}

	// restart
	if (input()->getKeyDown(KeyCode::Space)) {
		this->setup();
	}
}

void Scene19::updateDrawTree()
{
	// check for particles touching the tree
	unsigned int s = tree.size();
	for (unsigned int i = 0; i < s; i++) {
		std::deque<Element>::iterator it = particles.begin();
		while (it != particles.end()) {
			// look around for particles
			Point2 ul = Point2((*it).position.x-1, (*it).position.y-1);
			Point2 dl = Point2((*it).position.x-1, (*it).position.y+1);
			Point2 ur = Point2((*it).position.x+1, (*it).position.y-1);
			Point2 dr = Point2((*it).position.x+1, (*it).position.y+1);

			Point2 up = Point2((*it).position.x, (*it).position.y-1);
			Point2 down = Point2((*it).position.x, (*it).position.y+1);
			Point2 left = Point2((*it).position.x-1, (*it).position.y);
			Point2 right = Point2((*it).position.x+1, (*it).position.y);

			Point2 pos = tree[i].position;
			if (pos == up || pos == down || pos == left || pos == right ||
				pos == ul || pos == ur || pos == dr || pos == dl)
			{
				tree.push_back((*it));
				it = particles.erase(it);
			} else {
				++it;
			}
		}

		// color pixels in framebuffer
		canvas->setPixel(tree[i].position.x, tree[i].position.y, tree[i].color);
	}
}

void Scene19::updateDrawParticles()
{
	// count the particles
	unsigned int s = particles.size();

	if (s > 0) {
		// decide on color
		RGBAColor c = particles[0].color;
		static long int n = 0;
		if (n%4 == 0) {
			c = Color::rotate(particles[0].color, 0.001f);
		}
		n++;

		// update and draw each particle
		for (unsigned int i = 0; i < s; i++) {
			// clear the background
			canvas->clearPixel(particles[i].position.x, particles[i].position.y);

			// update particle position
			int range = 3;
			float vy = (rand()%range)-1;
			float vx = (rand()%range)-1;
			particles[i].velocity = Vector2(vx, vy);
			particles[i].position += particles[i].velocity;

			particles[i].position.x = floor(constrain(particles[i].position.x, 0, w));
			particles[i].position.y = floor(constrain(particles[i].position.y, 0, h));

			// rotate color
			particles[i].color = c;

			// color pixels in framebuffer
			canvas->setPixel(particles[i].position.x, particles[i].position.y, particles[i].color);
		}
	}
}
