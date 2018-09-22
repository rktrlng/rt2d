/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <iostream>
#include "mesh.h"

Mesh::Mesh()
{
	_vertexbuffer = 0;
	//_normalbuffer = 0;
	_uvbuffer = 0;

	_numverts = 0;
}

Mesh::~Mesh()
{
	if (_vertexbuffer != 0) {
		glDeleteBuffers(1, &_vertexbuffer);
	//	glDeleteBuffers(1, &_normalbuffer);
		glDeleteBuffers(1, &_uvbuffer);
	}
}

void Mesh::generateSpriteMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight)
{
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A sprite has 1 face (quad) with 2 triangles each, so this makes 1*2=2 triangles, and 2*3 vertices
	_numverts = 6;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	// first triangle
	vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 0.0f));
	vertices.push_back(glm::vec3(-width * pivotx, height - (height * pivoty), 0.0f));
	vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 0.0f));
	// second triangle
	vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 0.0f));
	vertices.push_back(glm::vec3(width - (width * pivotx), -height * pivoty, 0.0f));
	vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 0.0f));

	// UV coordinates for each vertex.
	// uvs for first triangle
	uvs.push_back(glm::vec2(0.0f, uvheight));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	// uvs for second triangle
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, uvheight));
	uvs.push_back(glm::vec2(0.0f, uvheight));

	this->generateBuffers(vertices, uvs);
}

void Mesh::generateLineMesh(Line* line)
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	unsigned int s = line->points().size();

	// Create the vertices
	for (unsigned int i = 0; i < s; i++) {
		vertices.push_back(line->points()[i]);

		// 'double up' every vertex but the first.
		// the endpoint of the previous segment is the startpoint of the next.
		if (i != 0) {
			vertices.push_back(line->points()[i]);
		}
	}
	// close the line by going back to the first point
	vertices.push_back(line->points()[0]);

	// Copy the UV's
	unsigned int s2 = vertices.size();
	for (unsigned int i = 0; i < s2; i++) {
		uvs.push_back(glm::vec2(0.5f, 0.5f));
	}

	_numverts = s2; // doesn't matter, Renderer will recalculate.

	this->generateBuffers(vertices, uvs);
}

void Mesh::generateCircleMesh(int radius, int segments, float uvwidth, float uvheight)
{
	unsigned int step = segments;
	_numverts = step*3; // n triangles with 3 vertices each

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	float x = 0.0f;
	float y = 0.0f;
	float u = 0.5f;
	float v = 0.5f;
	float deg = 360.0f;
	// for each triangle, do ...
	for (unsigned int i = 0; i < step; i++) {
		// ####################################################
		// start at, and always go back to (0,0), UV (0.5,0.5)
		vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		uvs.push_back(glm::vec2(0.5f, 0.5f));

		// #############################
		// create second vertex
		x = cos(deg*DEG_TO_RAD)*radius;
		y = sin(deg*DEG_TO_RAD)*radius;
		u = (x/radius) * uvwidth;
		v = (-y/radius) * uvheight;
		vertices.push_back(glm::vec3(x, y, 0.0f));
		uvs.push_back(glm::vec2(u/2+0.5f, v/2+0.5f)); // translate UV's from (-1, +1) to (0, +1)

		// #############################
		// rotate n degrees for the final vertex
		deg -= 360.0f/step;
		// create third vertex
		x = cos(deg*DEG_TO_RAD)*radius;
		y = sin(deg*DEG_TO_RAD)*radius;
		u = (x/radius) * uvwidth;
		v = (-y/radius) * uvheight;
		vertices.push_back(glm::vec3(x, y, 0.0f));
		uvs.push_back(glm::vec2(u/2+0.5f, v/2+0.5f)); // translate UV's from (-1, +1) to (0, +1)
		// ####################################################
	}

	this->generateBuffers(vertices, uvs);
}

void Mesh::generateSegmentMesh(int radius, int segments, int which)
{
	_numverts = 3;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;

	float x = 0.0f;
	float y = 0.0f;
	float u = 0.5f;
	float v = 0.5f;
	float deg = 360.0f;
	float step = deg/segments;

	// ####################################################
	// start at, and always go back to (0,0), UV (0.5,0.5)
	vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	uvs.push_back(glm::vec2(0.5f, 0.5f));

	// #############################
	deg -= step*which;
	// create second vertex
	x = cos(deg*DEG_TO_RAD)*radius;
	y = sin(deg*DEG_TO_RAD)*radius;
	u = x/radius;
	v = -y/radius;
	vertices.push_back(glm::vec3(x, y, 0.0f));
	uvs.push_back(glm::vec2(u/2+0.5f, v/2+0.5f)); // translate UV's from (-1, +1) to (0, +1)

	// #############################
	// rotate n degrees for the final vertex
	deg -= step;
	// create third vertex
	x = cos(deg*DEG_TO_RAD)*radius;
	y = sin(deg*DEG_TO_RAD)*radius;
	u = x/radius;
	v = -y/radius;
	vertices.push_back(glm::vec3(x, y, 0.0f));
	uvs.push_back(glm::vec2(u/2+0.5f, v/2+0.5f)); // translate UV's from (-1, +1) to (0, +1)
	// ####################################################

	this->generateBuffers(vertices, uvs);
}

void Mesh::generateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv)
{
	//create GLuint _vertexbuffer;
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

	//create GLuint _normalbuffer;
	//glGenBuffers(1, &_normalbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
	//glBufferData(GL_ARRAY_BUFFER, normal.size() * sizeof(glm::vec3), &normal[0], GL_STATIC_DRAW);

	//create GLuint _uvbuffer;
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);
}
