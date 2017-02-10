/**
 * This class describes Cube behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <rt2d/entity.h>

class GeoMetric : public Entity
{
public:
	GeoMetric();
	virtual ~GeoMetric();

	virtual void update(float deltaTime);

	void makeCube(int halfwidth, int halfheight, int halfdepth);
	void makeSphere(float radius, int lats, int longs);

private:

};

#endif /* GEOMETRIC_H */
