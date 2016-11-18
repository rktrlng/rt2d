/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include "boidentity.h"

BoidEntity::BoidEntity()
	: Entity()
{
	position = Vector2(SWIDTH/2, SHEIGHT/2);
	velocity = Vector2((rand()%500)-250, (rand()%500)-250);
	waittime = 0.0f;
	t.start();
}


BoidEntity::~BoidEntity()
{

}

void BoidEntity::update(float deltaTime)
{
	if (t.seconds() > waittime) {
		velocity = Vector2((rand()%500)-250, (rand()%500)-250);
		waittime = (float) (rand()%10)/10;
		t.start();
	}

	// ###############################################################
	// Keep this Entity within borders of Screen
	// ###############################################################
	if (position.y < 0) {
		position.y = 0;
		velocity.y *= -1;
	} else if (position.y > SHEIGHT) {
		position.y = SHEIGHT;
		velocity.y *= -1;
	}
	if (position.x < 0) {
		position.x = 0;
		velocity.x *= -1;
	} else if (position.x > SWIDTH) {
		position.x = SWIDTH;
		velocity.x *= -1;
	}

	position += velocity * deltaTime;
	rotation = velocity.getAngle();
}
