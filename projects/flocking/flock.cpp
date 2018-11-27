/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#include "flock.h"

int Flock::_nextGuid = 0;

Flock::Flock(int amount)
	: Entity()
{
	srand((unsigned)time(nullptr)+_nextGuid);
	_nextGuid++;

	t.start();

	for (int i=0; i<amount; i++) {
		Boid* b = new Boid();
		b->sprite()->color = WHITE;
		boids.push_back(b);
		this->addChild(b);
	}
}


Flock::~Flock()
{
	int s = boids.size();
	for (int i=0; i<s; i++) {
		Boid* b = boids[i];
		this->removeChild(b);
		delete b;
	}
	boids.clear();
}

void Flock::update(float deltaTime)
{
	if (VSYNC) {
		int i;
		int s = boids.size();
		for (i=0; i<s; i++) {
			boids[i]->flock(boids);
			boids[i]->updateBoid();
		}
	} else if ( t.seconds() > (1.0f/60.0f) ) {
		int i;
		int s = boids.size();
		for (i=0; i<s; i++) {
			boids[i]->flock(boids);
			boids[i]->updateBoid();
		}
		t.start();
	}
}

void Flock::boidColor(RGBAColor c)
{
	int s = boids.size();
	for (int i=0; i<s; i++) {
		Sprite* s = boids[i]->sprite();
		s->color = c;
	}
}

void Flock::boidWeights(float sf, float af, float cf)
{
	int s = boids.size();
	for (int i=0; i<s; i++) {
		boids[i]->_separationfactor = sf;
		boids[i]->_alignmentfactor = af;
		boids[i]->_cohesionfactor = cf;
	}
}

void Flock::boidViewDistance(float vd)
{
	int s = boids.size();
	for (int i=0; i<s; i++) {
		boids[i]->_viewdistance = vd;
	}
}
