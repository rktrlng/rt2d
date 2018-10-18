/**
 * This class describes geometric behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#ifndef GEOMETRIC_H
#define GEOMETRIC_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>

#include <rt2d/entity.h>

class GeoMetric : public Entity
{
public:
	GeoMetric();
	virtual ~GeoMetric();

	virtual void update(float deltaTime);

	void addCube(int halfwidth, int halfheight, int halfdepth);
	void addSphere(float radius, int lats, int longs);
	void addTorus(float radius1, float radius, int lats, int longs);
	void addCone(float radius, int height, int lats);
	void addCylinder(float radius, int height, int lats);
	void addLorenz(int numlines);

private:

};

#endif /* GEOMETRIC_H */
