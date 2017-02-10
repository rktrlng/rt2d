/**
 * This class describes Cube behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <rt2d/entity.h>

class GeoMetric : public Entity
{
public:
	GeoMetric();
	virtual ~GeoMetric();

	virtual void update(float deltaTime);

	void makeCube(int halfwidth, int halfheight, int halfdepth);

private:

};

#endif /* GEOMETRIC_H */
