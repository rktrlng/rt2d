#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>

#include "geometric.h"

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	GeoMetric* cube;
	GeoMetric* sphere;
	GeoMetric* cone;
	GeoMetric* cylinder;
	GeoMetric* torus;
	//GeoMetric* pyramid;
	GeoMetric* lorenz;
	// we need a container to offset the pivot point of lorenz.
	GeoMetric* lorenzcontainer;

	Timer t;
	void fpsCam(float deltaTime);
};

#endif /* MYSCENE_H */
