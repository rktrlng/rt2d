/**
 * This class describes Cube behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#ifndef CUBE_H
#define CUBE_H

#include <rt2d/entity.h>

class Cube : public Entity
{
public:
	Cube();
	virtual ~Cube();

	virtual void update(float deltaTime);

private:
	
};

#endif /* CUBE_H */
