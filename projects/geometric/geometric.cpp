/**
 * This class describes geometric behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 */

#include "geometric.h"

GeoMetric::GeoMetric() : Entity()
{

}

GeoMetric::~GeoMetric()
{

}

void GeoMetric::update(float deltaTime)
{
	// ###############################################################
	// Rotate
	// ###############################################################
	this->rotation.y += HALF_PI * deltaTime; // 90 deg/sec
	if (this->rotation.y > TWO_PI) {
		this->rotation.y -= TWO_PI;
	}
}

void GeoMetric::makeCube(int halfwidth, int halfheight, int halfdepth)
{
	Line front;
	front.color = GREEN;
	front.addPoint(-halfwidth, -halfheight, -halfdepth);
	front.addPoint( halfwidth, -halfheight, -halfdepth);
	front.addPoint( halfwidth,  halfheight, -halfdepth);
	front.addPoint(-halfwidth,  halfheight, -halfdepth);
	front.addPoint(-halfwidth, -halfheight, -halfdepth);
	this->addLine(&front);

	Line back;
	back.color = RED;
	back.addPoint(-halfwidth, -halfheight, halfdepth);
	back.addPoint( halfwidth, -halfheight, halfdepth);
	back.addPoint( halfwidth,  halfheight, halfdepth);
	back.addPoint(-halfwidth,  halfheight, halfdepth);
	back.addPoint(-halfwidth, -halfheight, halfdepth);
	this->addLine(&back);

	Line conn1;
	conn1.color = YELLOW;
	conn1.addPoint(-halfwidth, -halfheight, halfdepth);
	conn1.addPoint(-halfwidth, -halfheight,-halfdepth);
	this->addLine(&conn1);

	Line conn2;
	conn2.color = YELLOW;
	conn2.addPoint( halfwidth, -halfheight, halfdepth);
	conn2.addPoint( halfwidth, -halfheight,-halfdepth);
	this->addLine(&conn2);

	Line conn3;
	conn3.color = YELLOW;
	conn3.addPoint(-halfwidth,  halfheight, halfdepth);
	conn3.addPoint(-halfwidth,  halfheight,-halfdepth);
	this->addLine(&conn3);

	Line conn4;
	conn4.color = YELLOW;
	conn4.addPoint( halfwidth,  halfheight, halfdepth);
	conn4.addPoint( halfwidth,  halfheight,-halfdepth);
	this->addLine(&conn4);
}
