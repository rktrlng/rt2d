/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <rt2d/line.h>


Line::Line()
{
	// TODO make unique for each Line
	_filename = "none";
}

Line::Line(const std::string& filename)
{
	_filename = filename;
	loadLineFile(filename);
}


Line::~Line()
{
	_points.clear();
	_uvs.clear();
}

void Line::addPoint(float x, float y)
{
	glm::vec3 pnt(x, y, 0.0f);
	glm::vec2 uv(0.5f, 0.5f);
	_points.push_back(pnt);
	_uvs.push_back(uv);
}

bool Line::loadLineFile(const std::string& filename)
{
	FILE * file = fopen(filename.c_str(), "r");
	if( file == NULL ){
		printf("Can't open %s\n", filename.c_str());
		return false;
	}

	while(1) {
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

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

	// fill uv's
	std::vector<glm::vec3>::iterator v;
	for (v = _points.begin(); v != _points.end(); v++) {
		glm::vec2 uv(0.5f, 0.5f);
		_uvs.push_back(uv);
	}
	
	return true;
}
