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

}

void GeoMetric::addCube(int halfwidth, int halfheight, int halfdepth)
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
	//conn1.color = YELLOW;
	conn1.addPoint(-halfwidth, -halfheight, halfdepth);
	conn1.addPoint(-halfwidth, -halfheight,-halfdepth);
	this->addLine(&conn1);

	Line conn2;
	//conn2.color = YELLOW;
	conn2.addPoint( halfwidth, -halfheight, halfdepth);
	conn2.addPoint( halfwidth, -halfheight,-halfdepth);
	this->addLine(&conn2);

	Line conn3;
	//conn3.color = YELLOW;
	conn3.addPoint(-halfwidth,  halfheight, halfdepth);
	conn3.addPoint(-halfwidth,  halfheight,-halfdepth);
	this->addLine(&conn3);

	Line conn4;
	//conn4.color = YELLOW;
	conn4.addPoint( halfwidth,  halfheight, halfdepth);
	conn4.addPoint( halfwidth,  halfheight,-halfdepth);
	this->addLine(&conn4);
}

void GeoMetric::addSphere(float radius, int lats, int longs)
{
	std::vector<Point3> longcoords;

	float latitude_increment = 360.0f / lats;
	float longitude_increment = 180.0f / longs;

	// create longitudes
	for (float u = 0; u < 360.0f; u += latitude_increment) {
		Line semicircle;
		for (float t = 0; t <= 180.0f; t += longitude_increment) {
			float x = (float) (radius * sin(t*DEG_TO_RAD) * sin(u*DEG_TO_RAD));
			float y = (float) (radius * cos(t*DEG_TO_RAD));
			float z = (float) (radius * sin(t*DEG_TO_RAD) * cos(u*DEG_TO_RAD));

			semicircle.addPoint(x, y, z);

			// remember points on first latitude to create longitude circles
			if (u == 0) { longcoords.push_back(Point3(x,y,z)); }
		}
		// optionally, some nice colors
		if (u < 0.1f && u > -0.1f) { semicircle.color = GREEN; } // greenwich
		if (u < 180.2f && u > 179.8f) { semicircle.color = GREEN; } // greenwich
		if (u < 90.1f && u > 89.8) { semicircle.color = YELLOW; }
		if (u < 270.1f && u > 269.8) { semicircle.color = YELLOW; }

		this->addLine(&semicircle);
	}

	// create latitudes
	size_t s = longcoords.size();
	for (size_t i = 0; i < s; i++) {
		float rad = longcoords[i].z;
		float height = longcoords[i].y;

		Line circle;
		for (float u = 0; u <= 360.0f; u += latitude_increment) {
			circle.addPoint(rad * sin(u*DEG_TO_RAD), height, rad * cos(u*DEG_TO_RAD));
			if (height < 0.1f && height > -0.1f) { circle.color = RED; } // equator
		}
		this->addLine(&circle);
	}
	longcoords.clear();
}

void GeoMetric::addTorus(float radius1, float radius, int lats, int longs)
{
	std::vector<Point3> longcoords;

	float latitude_increment = 360.0f / lats;
	float longitude_increment = 180.0f / longs;

	// create longitudes
	for (float u = 0; u < 360.0f; u += latitude_increment) {
		Line slice;

		// what slice
		Vector3 r1x = Point3( sin(u*DEG_TO_RAD) * radius1, 0.0f, sin(u*DEG_TO_RAD) * radius1 );
		Vector3 r1z = Point3( sin(u*DEG_TO_RAD) * radius1, 0.0f, cos(u*DEG_TO_RAD) * radius1 );

		for (float t = 0; t <= 360.0f; t += longitude_increment) {
			float x = (float) (r1x.x + radius * sin(t*DEG_TO_RAD) * sin(u*DEG_TO_RAD));
			float y = (float) (radius * cos(t*DEG_TO_RAD));
			float z = (float) (r1z.z + radius * sin(t*DEG_TO_RAD) * cos(u*DEG_TO_RAD));

			slice.addPoint(x, y, z);

			// remember points on first latitude to create longitude circles
			if (u == 0) { longcoords.push_back(Point3(x,y,z)); }
		}
		// optionally, some nice colors
		if (u < 0.1f && u > -0.1f) { slice.color = GREEN; } // greenwich
		if (u < 180.2f && u > 179.8f) { slice.color = GREEN; } // greenwich
		if (u < 90.1f && u > 89.8) { slice.color = YELLOW; }
		if (u < 270.1f && u > 269.8) { slice.color = YELLOW; }

		this->addLine(&slice);
	}

	// create latitudes
	size_t s = longcoords.size();
	for (size_t i = 0; i < s; i++) {
		float rad = longcoords[i].z;
		float height = longcoords[i].y;

		Line circle;
		for (float u = 0; u <= 360.0f; u += latitude_increment) {
			circle.addPoint(rad * sin(u*DEG_TO_RAD), height, rad * cos(u*DEG_TO_RAD));
			if (height < 0.1f && height > -0.1f) { circle.color = RED; } // equator
		}
		this->addLine(&circle);
	}
	longcoords.clear();
}

void GeoMetric::addCone(float radius, int height, int lats)
{
	float latitude_increment = 360.0f / lats;

	for (float u = 0; u < 360.0f; u += latitude_increment) {
		Line semicircle;
		if (u < 0.1f && u > -0.1f) { semicircle.color = YELLOW; } // greenwich
		semicircle.addPoint(0, height, 0);
		float x = (float) (radius * sin(u*DEG_TO_RAD));
		float z = (float) (radius * cos(u*DEG_TO_RAD));
		semicircle.addPoint(x, -height, z);
		//semicircle.addPoint(0, -height, 0);

		this->addLine(&semicircle);
	}

	Line circle;
	circle.color = GREEN;
	for (float u = 0; u <= 360.0f; u += latitude_increment) {
		circle.addPoint(radius * sin(u*DEG_TO_RAD), -height, radius * cos(u*DEG_TO_RAD));
	}
	this->addLine(&circle);
}

void GeoMetric::addCylinder(float radius, int height, int lats)
{
	float latitude_increment = 360.0f / lats;

	for (float u = 0; u < 360.0f; u += latitude_increment) {
		Line semicircle;
		if (u < 0.1f && u > -0.1f) { semicircle.color = YELLOW; } // greenwich
		float x = (float) (radius * sin(u*DEG_TO_RAD));
		float z = (float) (radius * cos(u*DEG_TO_RAD));
		//semicircle.addPoint(0,  height, 0); // top cap
		semicircle.addPoint(x,  height, z);
		semicircle.addPoint(x, -height, z);
		//semicircle.addPoint(0, -height, 0); // bottom cap

		this->addLine(&semicircle);
	}

	Line top;
	top.color = RED;
	for (float u = 0; u <= 360.0f; u += latitude_increment) {
		top.addPoint(radius * sin(u*DEG_TO_RAD), height, radius * cos(u*DEG_TO_RAD));
	}
	this->addLine(&top);

	Line bottom;
	bottom.color = GREEN;
	for (float u = 0; u <= 360.0f; u += latitude_increment) {
		bottom.addPoint(radius * sin(u*DEG_TO_RAD), -height, radius * cos(u*DEG_TO_RAD));
	}
	this->addLine(&bottom);
}

void GeoMetric::addLorenz(int numlines)
{
	float lx = 0.01f;
	float ly = 0.0f;
	float lz = 0.0f;
	float a = 10;
	float b = 28;
	float c = 8.0f/3.0f;

	//Line l; // one single line is cheaper, but single color.
	RGBAColor color = RED;
	for (int i = 0; i < numlines; i++) {
		// update lorenz
		float dt = 0.02f;
		float dx = (a * (ly - lx))*dt;
		float dy = (lx * (b - lz) - ly)*dt;
		float dz = (lx * ly - c * lz)*dt;
		Line l; // individual colored segments
		l.color = color;
		l.addPoint(lx, ly, lz);
		lx = lx + dx;
		ly = ly + dy;
		lz = lz + dz;
		l.addPoint(lx, ly, lz);
		this->addLine(&l); // comment if 1 line
		color = Color::rotate(color, 0.005f);
	}
	//this->addLine(&l); // only with a single line
}
