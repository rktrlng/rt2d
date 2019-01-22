/**
 * This class describes Collider behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#ifndef COLLIDER_H
#define COLLIDER_H

#include <algorithm> // std::min + std::max
#include <rt2d/pointx.h> // Point2

struct Circle {
	float x;
	float y;
	float radius;
	Circle(float x_, float y_, float r) {
		this->x = x_;
		this->y = y_;
		this->radius = r;
	}
};

struct Rectangle {
	float x;
	float y;
	float width;
	float height;
	Rectangle(float x_, float y_, float w, float h) {
		this->x = x_;
		this->y = y_;
		this->width = w;
		this->height = h;
	}
};


class Collider
{
public:
	static bool point2point(const Point2& point1, const Point2& point2) {
		return point1 == point2;
	}

	static bool point2circle(const Point2& point, const Circle& circle) {
		float dx = circle.x - point.x;
		float dy = circle.y - point.y;
		return (dx * dx + dy * dy) < (circle.radius * circle.radius);
	}

	static bool point2rectangle(const Point2& point, const Rectangle& rect) {
		bool colx = point.x > rect.x && point.x < rect.x + rect.width;
		bool coly = point.y > rect.y && point.y < rect.y + rect.height;
		return colx && coly;
	}

	static bool circle2circle(const Circle& circle1, const Circle& circle2) {
		float dx = circle1.x - circle2.x;
		float dy = circle1.y - circle2.y;
		float radii = circle1.radius + circle2.radius;
		return (dx * dx + dy * dy) < (radii * radii);
	}

	// https://yal.cc/rectangle-circle-intersection-test/
	static bool circle2rectangle(const Circle& circle, const Rectangle& rect) {
		float mx = std::max(rect.x, std::min(circle.x, rect.x + rect.width));
		float my = std::max(rect.y, std::min(circle.y, rect.y + rect.height));
		float dx = circle.x - mx;
		float dy = circle.y - my;
		return (dx * dx + dy * dy) < (circle.radius * circle.radius);
	}

	// AABB
	static bool rectangle2rectangle(const Rectangle& rect1, const Rectangle& rect2) {
		return (rect1.x < rect2.x + rect2.width &&
		    rect1.x + rect1.width > rect2.x &&
		    rect1.y < rect2.y + rect2.height &&
		    rect1.y + rect1.height > rect2.y);
	}

private:
	// Disallow creating an instance of this object
	Collider() {}
};

#endif /* COLLIDER_H */
