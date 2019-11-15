/**
 * This class describes Raycast behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#ifndef RAYCAST_H
#define RAYCAST_H

#include <algorithm> // std::min + std::max
#include <rt2d/vectorx.h> // Point2 + Vector2

struct Boundary {
	Point2 begin;
	Point2 end;
	Boundary(float x1, float y1, float x2, float y2) {
		this->begin = Vector2(x1, y1);
		this->end   = Vector2(x2, y2);
	}
};

struct Ray {
	Point2 position;
	Vector2 direction;

	Ray(float p1, float p2, float d1, float d2) {
		this->position = Point2(p1, p2);
		this->direction = Vector2(d1, d2);
	}

	void setAngle(float angle) {
		this->direction.rotationDeg(angle);
	}

	void lookAt(float x, float y) {
	    this->direction.x = x - this->position.x;
	    this->direction.y = y - this->position.y;
	}

	Point2 cast(Boundary& wall) {
		float x1 = wall.begin.x;
		float y1 = wall.begin.y;
		float x2 = wall.end.x;
		float y2 = wall.end.y;

		float x3 = this->position.x;
		float y3 = this->position.y;
		float x4 = this->position.x + this->direction.x;
		float y4 = this->position.y + this->direction.y;

		float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
		if (den == 0) { // denominator can't be zero
			return Point2(0, 0);
		}

		float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
		if (t < 0.0f || t > 1.0f) { // no hit
			return Point2(0, 0);
		}

		float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
		if (u >= 0.0f) { // yes, hit!
			Point2 pt = Point2();
			pt.x = x1 + t * (x2 - x1);
			pt.y = y1 + t * (y2 - y1);
			return pt;
		}

		return Point2(0, 0);
	}

};



#endif /* RAYCAST_H */
