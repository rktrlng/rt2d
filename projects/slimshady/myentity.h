/**
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#ifndef MYENTITY_H
#define MYENTITY_H

#include <rt2d/entity.h>

class MyEntity : public Entity
{
public:
	MyEntity();
	virtual ~MyEntity();

	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* MYENTITY_H */
