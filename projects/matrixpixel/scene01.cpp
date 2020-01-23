/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2020 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene01.h"

Scene01::Scene01() : Scene()
{
	timer.start();

	// create Canvas
	canvas = new Canvas(8); // pixelsize
	this->addChild(canvas);

	// define points of a cube
	points[0] = math::Vector4(-0.5, -0.5, -0.5, 1.0);
	points[1] = math::Vector4( 0.5, -0.5, -0.5, 1.0);
	points[2] = math::Vector4( 0.5,  0.5, -0.5, 1.0);
	points[3] = math::Vector4(-0.5,  0.5, -0.5, 1.0);
	points[4] = math::Vector4(-0.5, -0.5,  0.5, 1.0);
	points[5] = math::Vector4( 0.5, -0.5,  0.5, 1.0);
	points[6] = math::Vector4( 0.5,  0.5,  0.5, 1.0);
	points[7] = math::Vector4(-0.5,  0.5,  0.5, 1.0);
}

Scene01::~Scene01()
{
	this->removeChild(canvas);
	delete canvas;
}

void Scene01::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	static double angle = 0.0;
	float tsec = timer.seconds();
	if (tsec > 0.016667f - deltaTime) { // 0.0167 is 60 fps
		canvas->fill(canvas->backgroundcolor);

		// define transform for object
		math::Vector4 scale = math::Vector4(25.0, 25.0, 25.0, 0.0);
		math::Vector4 rotation = math::Vector4(angle, angle + PI/3, angle - PI/3, 0.0);
		math::Vector4 position = math::Vector4(canvas->width()/2, canvas->height()/2, 0.0, 0.0);

		// math::Vector4 scaled = math::Matrix4::scale(points[i], scale);
		// math::Vector4 rotated = math::Matrix4::rotate(scaled, rotation);
		// math::Vector4 translated = math::Matrix4::translate(rotated, translation);

		// create modelmatrix
		math::Matrix4 modelmatrix = math::Matrix4::modelMatrix(position, rotation, scale);
		//math::Matrix4::print(modelmatrix);

		Vector3 drawpoints[8];
		for (size_t i = 0; i < 8; i++) {
			// transform each point in 3D object to screen coords
			math::Vector4 transformed = math::Matrix4::matmul(modelmatrix, points[i]);

			// convert to Vector3
			drawpoints[i] = Vector3(transformed.x, transformed.y, transformed.z);
		}
		angle += 0.01;

		// define edges between points
		std::vector<Point2i> edges;
		edges.push_back( Point2i(0, 1));
		edges.push_back( Point2i(1, 2));
		edges.push_back( Point2i(2, 3));
		edges.push_back( Point2i(3, 0));

		edges.push_back( Point2i(4, 5));
		edges.push_back( Point2i(5, 6));
		edges.push_back( Point2i(6, 7));
		edges.push_back( Point2i(7, 4));

		edges.push_back( Point2i(0, 4));
		edges.push_back( Point2i(1, 5));
		edges.push_back( Point2i(2, 6));
		edges.push_back( Point2i(3, 7));

		// draw edges on canvas
		for (size_t i = 0; i < edges.size(); i++) {
			int a = edges[i].x;
			int b = edges[i].y;
			RGBAColor color = RGBAColor();
			if (i < 4) {
				color = RED;
			} else if (i > 3 && i < 8) {
				color = GREEN;
			} else {
				color = CYAN;
			}
			Vector2f from = Vector2f(drawpoints[a].x, canvas->height() - drawpoints[a].y);
			Vector2f to = Vector2f(drawpoints[b].x, canvas->height() - drawpoints[b].y);
			canvas->drawLine(from, to, color);
		}

		//draw circles around points
		for (size_t i = 0; i < 8; i++) {
			PixelSprite circle = PixelSprite();
			circle.position = Point2i(drawpoints[i].x, canvas->height() - drawpoints[i].y);
			circle.createCircle(1, MAGENTA);
			canvas->drawSprite(circle);
		}

		// draw debug box
		ddClear();
		for (size_t i = 0; i < edges.size(); i++) {
			int a = edges[i].x;
			int b = edges[i].y;
			if (i < 4) {
				ddLine(drawpoints[a].x, drawpoints[a].y, drawpoints[b].x, drawpoints[b].y, RED);
			} else if (i > 3 && i < 8) {
				ddLine(drawpoints[a].x, drawpoints[a].y, drawpoints[b].x, drawpoints[b].y, GREEN);
			} else {
				ddLine(drawpoints[a].x, drawpoints[a].y, drawpoints[b].x, drawpoints[b].y, CYAN);
			}
		}

		// draw points
		for (size_t i = 0; i < 8; i++) {
			canvas->setPixel(drawpoints[i].x, canvas->height() - drawpoints[i].y, BLACK);
		}

		timer.start();
	}

}
