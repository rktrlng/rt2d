/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene07.h"

Scene07::Scene07() : SuperScene()
{
	srand((unsigned)time(nullptr));

	text[0]->message("Scene07: Pixel Particles");

	text[4]->message("<SPACE> reset particles");
	text[7]->message("FPS: ---");

	timer.start();
	fpstimer.start();

	// create Canvas
	canvas = new Canvas(4); // pixelsize
	layers[0]->addChild(canvas);
}


Scene07::~Scene07()
{
	layers[0]->removeChild(canvas);
	delete canvas;

	particles.clear();
}

void Scene07::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	// ###############################################################
	// Draw particles
	// ###############################################################
	unsigned int maxparticles = 2500;
	static int framecounter = 0;
	float tsec = timer.seconds();
	if (tsec > 0.016667f - deltaTime) { // 0.0167 is 60 fps
		// generate a number of particles with a random velocity
		unsigned int amount = rand()%5;
		for (unsigned int i = 0; i < amount; i++) {
			Particle p;
			p.position = Point2(canvas->width()/2, canvas->height()/8*7);
			int range = 60;
			float vy = rand()%range;
			float vx = 0;
			while (vx == 0) { vx = (rand()%range)-range/2; }
			p.velocity = Vector2(vx, vy) / 33.33f;
			p.color = RED;
			// add it to the list of particles
			particles.push_back(p);
			// too many particles
			if ( particles.size() > maxparticles ) {
				// remove oldest (first) particle and clean up to background color
				canvas->clearPixel( particles[0].position.x, particles[0].position.y );
				particles.pop_front();
			}
		}
		// count the particles
		unsigned int s = particles.size();

		// update message
		std::stringstream msg;
		msg << "Particles: " << s;
		text[6]->message(msg.str());

		if (fpstimer.seconds() > 1.0f - deltaTime) {
			std::stringstream fpstxt;
			fpstxt  << "FPS: " << framecounter << " (capped)";
			framecounter = 0;
			text[7]->message(fpstxt.str());
			fpstimer.start();
		}

		// update and draw each particle
		for (unsigned int i = 0; i < s; i++) {
			// clear the background
			canvas->clearPixel(particles[i].position.x, particles[i].position.y);

			// update particle position
			particles[i].velocity.y -= 0.1f;
			if (particles[i].position.y < 0) {
				particles[i].position.y = 0;
				particles[i].velocity.y *= -1;
			}
			particles[i].velocity.y *= 0.995f;
			particles[i].position += particles[i].velocity;

			// rotate color
			particles[i].color = Color::rotate(particles[i].color, 0.001f);

			// color pixels in framebuffer
			canvas->setPixel(particles[i].position.x, particles[i].position.y, particles[i].color);
		}

		framecounter++;
		timer.start();
	}

	// ###############################################################
	// Clear particles
	// ###############################################################
	if (input()->getKeyDown(KeyCode::Space)) {
		clearParticles();
	}
}

void Scene07::clearParticles()
{
	int s = particles.size();

	// clear each particle from the framebuffer
	for (int i = 0; i < s; i++) {
		canvas->clearPixel(particles[i].position.x, particles[i].position.y);
	}
	particles.clear();
}
