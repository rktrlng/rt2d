/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <rt2d/line.h>
#include <rt2d/vectorx.h>

int Line::_nextGuid = 0;

Line::Line()
{
	_guid = _nextGuid;
	_nextGuid++;

	_dynamic = false;
	_closed = false;

	char buf[12]; // should be big enough: "Line99999"
	sprintf(buf, "line%d", _guid);
	std::string linename(buf);

	_filename = linename;
}

Line::Line(const std::string& filename)
{
	_filename = filename;
	loadLineFile(filename);
}


Line::~Line()
{
	_points.clear();
}

void Line::addPoint(float x, float y, float z)
{
	glm::vec3 pnt(x, y, z);
	_points.push_back(pnt);
}


void Line::editPoint(unsigned int id, float x, float y, float z)
{
	if (id < _points.size()) {
		_points[id].x = x;
		_points[id].y = y;
		_points[id].z = z;
	}
}

void Line::createCircle(int radius, int segments)
{
	int step = 360 / segments;

	for (int i = 0; i < 360; i += step) {
		float x = cos(i*DEG_TO_RAD)*radius;
		float y = sin(i*DEG_TO_RAD)*radius;
		this->addPoint(x, y);
	}
	this->addPoint(_points[0].x, _points[0].y);

	char buf[24]; // should be big enough: "circle_r999_s999"
	sprintf(buf, "circle_r%d_s%d", radius, segments);
	std::string linename(buf);

	_filename = linename;
}

void Line::createBox(int hw, int hh)
{
	this->addPoint(-hw, -hh);
	this->addPoint( hw, -hh);
	this->addPoint( hw,  hh);
	this->addPoint(-hw,  hh);
	this->closed(true);

	char buf[24]; // should be big enough: "box_hw999_hh999"
	sprintf(buf, "box_hw%d_hh%d", hw, hh);
	std::string linename(buf);

	_filename = linename;
}

bool Line::loadLineFile(const std::string& filename)
{
	FILE * file = fopen(filename.c_str(), "r");
	if( file == nullptr ){
		printf("Can't open %s\n", filename.c_str());
		return false;
	}

	while(1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF) {
			break; // EOF = End Of File. Quit the loop.
		}
		// else : parse lineHeader
		if (strcmp( lineHeader, "v") == 0) {
			glm::vec3 vertex;
			int matches = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			if (matches != 3) {
				printf("File can't be read by the parser. Not 3 vertices per point.\n");
				return false;
			}
			_points.push_back(vertex);
		} else {
			// Probably a comment, eat up the rest of the line
			char tmpBuffer[1000];
			char * returned = fgets(tmpBuffer, 1000, file);
			if (returned[0] == '#') {
				// yes, a comment
			}
		}
	}

	fclose (file);

	// close the line
	_points.push_back(_points[0]);

	return true;
}
