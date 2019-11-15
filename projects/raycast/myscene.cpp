/**
 * This class describes MyScene behavior.
 *
 * Copyright 2019 Rik Teerling <rik@onandoffables.com>
 */

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	std::srand(std::time(nullptr));
	for (size_t i = 0; i < 5; i++) {
		int x1 = std::rand() % SWIDTH;
		int y1 = std::rand() % SHEIGHT;
		int x2 = std::rand() % SWIDTH;
		int y2 = std::rand() % SHEIGHT;
		Boundary wall = Boundary(x1, y1, x2, y2);
		walls.push_back(wall);
	}
}

MyScene::~MyScene()
{

}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// reset walls + robot
	if (input()->getKeyUp(KeyCode::Space)) {
		for (size_t i = 0; i < walls.size(); i++) {
			int x1 = std::rand() % SWIDTH;
			int y1 = std::rand() % SHEIGHT;
			int x2 = std::rand() % SWIDTH;
			int y2 = std::rand() % SHEIGHT;
			walls[i].begin = Point2(x1, y1);
			walls[i].end = Point2(x2, y2);
		}
		robot = Robot(SWIDTH/2, SHEIGHT/2);
	}

	//get mouse position
	float mousex = input()->getMouseX() + camera()->position.x - SWIDTH/2;
	float mousey = input()->getMouseY() + camera()->position.y - SHEIGHT/2;

	ddClear();

	robot.update(mousex, mousey);

	// check robot against walls
	for (size_t i = 0; i < robot.rays.size(); i++) {
		bool hit = false;
		Ray shortest = robot.rays[i];
		shortest.direction.setLength(400.0f);
		Vector2 coll = Vector2(0, 0);
		for (size_t w = 0; w < walls.size(); w++) {
			coll = robot.rays[i].cast(walls[w]);
			if (coll != Vector2(0, 0)) {
				robot.rays[i].lookAt(coll.x, coll.y);
				if (robot.rays[i].direction.getLengthSquared() < shortest.direction.getLengthSquared()) {
					shortest = robot.rays[i];
					hit = true;
				}
			}
		}
		this->draw(shortest); //  draw robot rays

		float collpointx = shortest.position.x + shortest.direction.x;
		float collpointy = shortest.position.y + shortest.direction.y;
		if (hit) {
			ddCircle(collpointx, collpointy, 4, YELLOW);
		} else {
			ddCircle(collpointx, collpointy, 4, PINK);
		}
	}

	for (size_t i = 0; i < walls.size(); i++) {
		this->draw(walls[i]);
	}
}

void MyScene::draw(Boundary& wall) {
	ddLine(wall.begin, wall.end, RED);
}

void MyScene::draw(Ray& ray) {
	Ray copy(ray.position.x, ray.position.y, ray.direction.x, ray.direction.y);
	ddLine(copy.position.x, copy.position.y, copy.direction.x + copy.position.x, copy.direction.y + copy.position.y, GREEN);
}
