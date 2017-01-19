/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 */
#ifndef BOID_H
#define BOID_H

#include <vector>
#include <rt2d/entity.h>

class Boid: public Entity
{
	public:
		Boid();
		virtual ~Boid();

		virtual void update(float deltaTime);
		virtual void updateBoid();

		void flock(std::vector<Boid*>& boids);
		Vector2 _seek(Vector2 target);
		void _applyForce(Vector2 force);

		float _mass;
		float _radius;
		float _maxforce;
		float _maxspeed;
		float _desiredseparation;
		float _viewdistance;

		float _separationfactor;
		float _alignmentfactor;
		float _cohesionfactor;
		//float _xenofactor;

	private:
		Vector2 _location;
		Vector2 _velocity;
		Vector2 _acceleration;

		int _bordermode;
		void _borders(int width, int height);


		Vector2 _separate(std::vector<Boid*>& boids);
		Vector2 _align(std::vector<Boid*>& boids);
		Vector2 _cohesion(std::vector<Boid*>& boids);
};

#endif /* BOID_H */
