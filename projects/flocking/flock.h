/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#ifndef FLOCK_H
#define FLOCK_H

#include <vector>
#include <rt2d/entity.h>
#include "boid.h"

class Flock: public Entity
{
	public:
		Flock(int amount);
		virtual ~Flock();

		virtual void update(float deltaTime);

		void boidColor(RGBAColor);
		void boidWeights(float sf, float af, float cf);
		void boidViewDistance(float vd);

	private:
		std::vector<Boid*> boids;
		Timer t;
		static int _nextGuid;
};

#endif /* FLOCK_H */
