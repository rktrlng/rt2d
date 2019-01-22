/**
 * Copyright 2019 Rik Teerling <on@onandoffables.com>
 *
 * @file shape.h
 *
 * @brief description of Shape behavior.
 */

#ifndef SHAPE_H
#define SHAPE_H

#include <rt2d/entity.h>

/// @brief The Shape class is the Entity implementation.
class Shape : public Entity
{
public:
	/// @brief Constructor
	Shape();
	/// @brief Destructor
	virtual ~Shape();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* SHAPE_H */
