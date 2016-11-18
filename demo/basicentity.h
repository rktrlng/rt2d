/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef BASICENTITY_H
#define BASICENTITY_H

#include <rt2d/entity.h>

class BasicEntity: public Entity
{
	public:
		BasicEntity();
		virtual ~BasicEntity();

		virtual void update(float deltaTime);

	private:
		/* add your private declarations */
};

#endif /* BASICENTITY_H */
