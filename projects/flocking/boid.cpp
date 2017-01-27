/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *
 * code ported from: http://natureofcode.com/book/chapter-6-autonomous-agents/
 */
#include <rt2d/rt2dconfig.h>
#include "boid.h"

Boid::Boid()
	: Entity()
{
	this->addSprite("assets/boid.tga", 0.25f, 0.50f);
	this->sprite()->color = WHITE;

	int range = 4;
	_acceleration = Vector2(0,0);
	_velocity = Vector2((rand()%range)-range/2, (rand()%range)-range/2);
	_location = Vector2((SWIDTH/2)+(rand()%200)-100, ((SHEIGHT/2)+rand()%200)-100);

	_mass = 0.75f;
	_radius = 16.0;
	_maxspeed = 6.0;
	_maxforce = 0.05;			// Maximum steering force
	_desiredseparation = 24.0f;	// minimum distance between each boid
	_viewdistance = 125.0f;		// distance where other boids can be spotted so that we can move closer. higher = more coherence

	_separationfactor = 1.5f;
	_alignmentfactor = 1.0f;
	_cohesionfactor = 1.0f;

	_bordermode = 1;
}


Boid::~Boid()
{

}

void Boid::update(float deltaTime)
{

}

void Boid::updateBoid()
{
	// Update velocity
	_velocity += _acceleration;
	// Limit speed
	_velocity.limit(_maxspeed);
	_location += _velocity;
	// Reset acceleration to 0 each cycle
	_acceleration *= 0;

	// update Entity position & rotation
	this->position = _location;
	this->rotation.z = this->_velocity.getAngle();
}

// We accumulate a new acceleration each time based on rules
void Boid::flock(std::vector<Boid*>& boids)
{
	// call behavior of this boid
	Vector2 sep = _separate(boids);	// Separation (don't collide with neighbors)
	Vector2 ali = _align(boids);	// Alignment (adjust speed and direction to neighbors)
	Vector2 coh = _cohesion(boids);	// Cohesion (stay close to the center of the group)

	// weigh these forces
	sep *= _separationfactor;
	ali *= _alignmentfactor;
	coh *= _cohesionfactor;

	// Add the force vectors to acceleration
	_applyForce(sep);
	_applyForce(ali);
	_applyForce(coh);

	_borders(SWIDTH,SHEIGHT);
}

void Boid::_applyForce(Vector2 force)
{
	// We could add mass here if we want A = F / M
	//acceleration += force;
	_acceleration += (force/_mass);
}

// A method that calculates and applies a steering force towards a target
// STEER = DESIRED - VELOCITY
Vector2 Boid::_seek(Vector2 target)
{
	Vector2 desired = Vector2(_location, target);	// A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired *= _maxspeed;
	// Steering = Desired minus Velocity
	Vector2 steer = desired - _velocity;
	steer.limit(_maxforce);	// Limit to maximum steering force
	return steer;
}

// Wraparound
void Boid::_borders(int width, int height)
{
	if (_bordermode == 1) {
		// as if in a fishtank with fish aware of the boundaries
		Vector2 desired;
		float d = 125;

		if (_location.x < d) {
		  desired = Vector2(_maxspeed, _velocity.y);
		}
		else if (_location.x > width-d) {
		  desired = Vector2(-_maxspeed, _velocity.y);
		}

		if (_location.y < (d/2)) {
		  desired = Vector2(_velocity.x, _maxspeed);
		}
		else if (_location.y > height-(d/2)) {
		  desired = Vector2(_velocity.x, -_maxspeed);
		}

		if (desired.getLength() > 0) {
		  desired.normalize();
		  desired *= _maxspeed;
		  Vector2 steer = desired - _velocity;
		  steer.limit(_maxforce*3); // force steering :)
		  _applyForce(steer);
		}
    } else if (_bordermode == 2) {
		// as if in a fishtank with blind fish
		if (_location.x < _radius) { _location.x = _radius; _velocity.x *= -1; }
		if (_location.y < _radius) { _location.y = _radius; _velocity.y *= -1; }
		if (_location.x > width-_radius) { _location.x = width-_radius; _velocity.x *= -1; }
		if (_location.y > height-_radius) { _location.y = height-_radius; _velocity.y *= -1; }
	} else {
		// up out -> down in / left out -> right in
		if (_location.x < -_radius) _location.x = width+_radius;
		if (_location.y < -_radius) _location.y = height+_radius;
		if (_location.x > width+_radius) _location.x = -_radius;
		if (_location.y > height+_radius) _location.y = -_radius;
	}
}

// Separation
// Check for nearby boids and steer away
Vector2 Boid::_separate(std::vector<Boid*>& boids)
{
	Vector2 steer = Vector2(0,0);
	int count = 0;
	// For every boid in the system, check if it's too close
	int i;
	int s = boids.size();
	for (i=0; i<s; i++) {
		Boid* other = boids[i];
		// Calculate vector pointing away from neighbor
		Vector2 diff = Vector2(other->_location, _location);
		float d = diff.getLength();
		// If the distance is greater than 0 and less than the desired separation (0 is when you find yourself)
		if ((d > 0) && (d < _desiredseparation)) {
			diff.normalize();
			diff /= d;		// Weight by distance
			steer += diff;
			count++;		// Keep track of how many
		}
	}
	// Average: divide by how many
	if (count > 0) {
		steer /= (float)count;
	}

	// As long as the vector is greater than 0
	if (steer.getLength() > 0) {
		// Implement Reynolds: Steering = Desired - Velocity
		steer.normalize();
		steer *= _maxspeed;
		steer -= _velocity;
		steer.limit(_maxforce);
	}

	return steer;
}

// Alignment
// For every nearby boid in the system, calculate the average velocity (and thus heading)
Vector2 Boid::_align(std::vector<Boid*>& boids)
{
	Vector2 sum = Vector2(0,0);
	int count = 0;
	int i;
	int s = boids.size();
	for (i=0; i<s; i++) {
		Boid* other = boids[i];
		float d = Vector2(_location,other->_location).getLength();
		if ((d > 0) && (d < _viewdistance)) {
			sum += other->_velocity;
			count++;
		}
	}

	if (count > 0) {
		sum /= (float)count;
		sum.normalize();
		sum *= _maxspeed;
		Vector2 steer = sum - _velocity; // PVector.sub(sum,velocity)
		steer.limit(_maxforce);
		return steer;
	}

	return Vector2(0,0);
}

// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
Vector2 Boid::_cohesion(std::vector<Boid*>& boids)
{
	Vector2 sum = Vector2(0,0);	 // Start with empty vector to accumulate all locations
	int count = 0;
	int i;
	int s = boids.size();
	for (i=0; i<s; i++) {
		Boid* other = boids[i];
		float d = Vector2(_location,other->_location).getLength();
		if ((d > 0) && (d < _viewdistance)) {
			sum += other->_location;
			count++;
		}
	}

	if (count > 0) {
		sum /= count;
		return _seek(sum);	// Steer towards the location
	}

	return Vector2(0,0);
}
