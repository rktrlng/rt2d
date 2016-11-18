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
	srand((unsigned)time(NULL));

	text[0]->message("Scene07: Pixel Particles");

	text[4]->message("<SPACE> reset particles");
	text[7]->message("FPS: ---");

	timer.start();
	fpstimer.start();

	// create Canvas
	int pixelsize = 4;
	int border = 0;
	canvas = new BasicEntity();
	canvas->position = Point2(SWIDTH/2, SHEIGHT/2);
	canvas->scale = Point2(pixelsize, pixelsize);
	layers[0]->addChild(canvas);

	// width, height, bitdepth, filter, wrap
	PixelBuffer* tmp = new PixelBuffer((SWIDTH/pixelsize)-border, (SHEIGHT/pixelsize)-border, 3, 0, 0);
	canvas->addDynamicSprite(tmp);
	delete tmp;

	// get the pixels from the texture and call it the global framebuffer
	framebuffer = canvas->sprite()->texture()->pixels();

	// fill framebuffer with background color
	backgroundcolor = RGBAColor(32, 32, 32, 255);
	long counter = 0;
	for (long y=0; y<framebuffer->height; y++) {
		for (long x=0; x<framebuffer->width; x++) {
			framebuffer->data[counter+0] = backgroundcolor.r;
			framebuffer->data[counter+1] = backgroundcolor.g;
			framebuffer->data[counter+2] = backgroundcolor.b;
			if (framebuffer->bitdepth == 4) {
				framebuffer->data[counter+3] = backgroundcolor.a;
			}
			counter += framebuffer->bitdepth;
		}
	}
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
			p.position = Point2(framebuffer->width/2, framebuffer->height/8*7);
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
				setPixel( particles[0].position.x, particles[0].position.y, backgroundcolor );
				particles.pop_front();
			}
		}
		// count the particles
		unsigned int s = particles.size();

		// update message
		std::string msg = "Particles: ";
		msg.append(rt2d::to_string<unsigned int>(s));
		text[6]->message(msg);

		if (fpstimer.seconds() > 1.0f - deltaTime) {
			std::string fpstxt = "FPS: ";
			fpstxt.append(rt2d::to_string<int>(framecounter));
			fpstxt.append(" (capped)");
			framecounter = 0;
			text[7]->message(fpstxt);
			fpstimer.start();
		}

		// update and draw each particle
		for (unsigned int i = 0; i < s; i++) {
			// clear the background
			setPixel(particles[i].position.x, particles[i].position.y, backgroundcolor );

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
			setPixel(particles[i].position.x, particles[i].position.y, particles[i].color );
		}

		framecounter++;
		timer.start();
	}

	// ###############################################################
	// Clear particles
	// ###############################################################
	if (input()->getKeyDown( GLFW_KEY_SPACE )) {
		clearParticles();
	}
}

void Scene07::setPixel(int x, int y, RGBAColor color)
{
	int start = ((y*framebuffer->width) + x) * framebuffer->bitdepth;
	if (start > framebuffer->width * framebuffer->height * framebuffer->bitdepth || start < 0) { return; }

	framebuffer->data[start+0] = color.r;
	framebuffer->data[start+1] = color.g;
	framebuffer->data[start+2] = color.b;
	if (framebuffer->bitdepth == 4) {
		framebuffer->data[start+3] = color.a;
	}
}

void Scene07::clearParticles()
{
	int s = particles.size();

	// clear each particle from the framebuffer
	for (int i = 0; i < s; i++) {
		// clear the background
		setPixel(particles[i].position.x, particles[i].position.y, backgroundcolor);
	}
	particles.clear();
}
