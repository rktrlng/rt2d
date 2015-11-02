/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
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
	_numverts = 6;
	
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A sprite has 1 face (quad) with 2 triangles each, so this makes 1*2=2 triangles, and 2*3 vertices
	std::vector<glm::vec3> vertices;
	
	vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 0.0f));
	vertices.push_back(glm::vec3(-width * pivotx, height - (height * pivoty), 0.0f));
	vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 0.0f));
	vertices.push_back(glm::vec3(width - (width * pivotx), height - (height * pivoty), 0.0f));
	vertices.push_back(glm::vec3(width - (width * pivotx), -height * pivoty, 0.0f));
	vertices.push_back(glm::vec3(-width * pivotx, -height * pivoty, 0.0f));

	// UV coordinates for each vertex.
	std::vector<glm::vec2> uvs;
	
	uvs.push_back(glm::vec2(0.0f, uvheight));
	uvs.push_back(glm::vec2(0.0f, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, 0.0f));
	uvs.push_back(glm::vec2(uvwidth, uvheight));
	uvs.push_back(glm::vec2(0.0f, uvheight));
	
	//GLuint _vertexbuffer;
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
/*
	//GLuint _normalbuffer;
	glGenBuffers(1, &_normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
*/
	//GLuint _uvbuffer;
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}

void Mesh::generateLineMesh(Line* line)
{
	std::vector<glm::vec3> points = line->points();
	std::vector<glm::vec2> uvs = line->uvs();
	
	unsigned int s = points.size();
	const unsigned int maxsize = 100;
	if (s > maxsize) {
		s = maxsize;
	}
	_numverts = s; // doesn't matter, Renderer will recalculate.
	
	GLfloat g_vertex_buffer_data[maxsize*3*2]; // (x,y,z)/point * begin/end.
	GLfloat g_uv_buffer_data[maxsize*3*2];
	//GLfloat g_vertex_buffer_data[s*3*2];
	//GLfloat g_uv_buffer_data[s*3*2];
	
	// Copy the vertices
	int counter = 0;
	for (unsigned int i = 0; i < s; i++) {
		g_vertex_buffer_data[counter+0] = points[i].x;
		g_vertex_buffer_data[counter+1] = points[i].y;
		g_vertex_buffer_data[counter+2] = points[i].z;
		
		// 'double up' every vertex but the first.
		// the endpoint of the previous segment is the startpoint of the next.
		if (i != 0) {
			g_vertex_buffer_data[counter+3] = points[i].x;
			g_vertex_buffer_data[counter+4] = points[i].y;
			g_vertex_buffer_data[counter+5] = points[i].z;
			counter += 3;
		}
		counter += 3;
	}
	// close the line by going back to the first point
	g_vertex_buffer_data[counter+0] = points[0].x;
	g_vertex_buffer_data[counter+1] = points[0].y;
	g_vertex_buffer_data[counter+2] = points[0].z;
	
	// Copy the UV's
	counter = 0;
	for (unsigned int i = 0; i < s*2; i++) {
		g_uv_buffer_data[counter+0] = 0.5f;
		g_uv_buffer_data[counter+1] = 0.5f;
		
		counter += 2;
	}

	//GLuint _vertexbuffer;
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	//GLuint _uvbuffer;
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

void Mesh::generateCircleMesh(int radius, int segments)
{
	unsigned int step = segments;
	_numverts = step*3; // n triangles with 3 vertices each

#ifdef _WIN32
	step = 6;
	GLfloat g_vertex_buffer_data[6*3*3]; // 3 * (x,y,z)
	GLfloat g_uv_buffer_data[6*3*2]; // 2 * (u,v)
	_numverts = step*3;
#else
	GLfloat g_vertex_buffer_data[step*3*3]; // 3 * (x,y,z)
	GLfloat g_uv_buffer_data[step*3*2]; // 2 * (u,v)
#endif

	int vertcounter = 0;
	int uvcounter = 0;
	float x = 0.0f;
	float y = 0.0f;
	float u = 0.5f;
	float v = 0.5f;
	int deg = 360;
	// for each triangle, do ...
	for (unsigned int i = 0; i < step; i++) {
		// #############################
		// start at, and always go back to (0,0), UV (0.5,0.5)
		x = 0.0f;
		y = 0.0f;
		u = 0.5f;
		v = 0.5f;
		
		// fill buffers
		g_vertex_buffer_data[vertcounter++] = x;
		g_vertex_buffer_data[vertcounter++] = y;
		g_vertex_buffer_data[vertcounter++] = 0.0f;
		
		g_uv_buffer_data[uvcounter++] = u;
		g_uv_buffer_data[uvcounter++] = v;

		// #############################
		// create second vertex
		x = cos(deg*DEG_TO_RAD)*radius;
		y = sin(deg*DEG_TO_RAD)*radius;
		u = x/radius;
		v = -y/radius;
		
		// translate UV's from (-1, +1) to (0, +1)
		u /= 2;
		v /= 2;
		u += 0.5f;
		v += 0.5f;
		
		// fill buffers
		g_vertex_buffer_data[vertcounter++] = x;
		g_vertex_buffer_data[vertcounter++] = y;
		g_vertex_buffer_data[vertcounter++] = 0.0f;
		
		g_uv_buffer_data[uvcounter++] = u;
		g_uv_buffer_data[uvcounter++] = v;
		
		// #############################
		// rotate n degrees for the final vertex
		deg -= 360/step;
		
		// create third vertex
		x = cos(deg*DEG_TO_RAD)*radius;
		y = sin(deg*DEG_TO_RAD)*radius;
		u = x/radius;
		v = -y/radius;
		
		// translate UV's from (-1, +1) to (0, +1)
		u /= 2;
		v /= 2;
		u += 0.5f;
		v += 0.5f;
		
		// fill buffers
		g_vertex_buffer_data[vertcounter++] = x;
		g_vertex_buffer_data[vertcounter++] = y;
		g_vertex_buffer_data[vertcounter++] = 0.0f;
		
		g_uv_buffer_data[uvcounter++] = u;
		g_uv_buffer_data[uvcounter++] = v;
	}

	//GLuint _vertexbuffer;
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	//GLuint _uvbuffer;
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

void Mesh::generateSegmentMesh(int radius, int segments, int which)
{
	_numverts = 3;
	
	GLfloat g_vertex_buffer_data[3*3]; // 3 * (x,y,z)
	GLfloat g_uv_buffer_data[3*2]; // 2 * (u,v)
	
	int vertcounter = 0;
	int uvcounter = 0;
	float x = 0.0f;
	float y = 0.0f;
	float u = 0.5f;
	float v = 0.5f;
	int deg = 360;
	int step = deg/segments;

	// ####################################################
	// start at, and always go back to (0,0), UV (0.5,0.5)
	x = 0.0f;
	y = 0.0f;
	u = 0.5f;
	v = 0.5f;
	
	// fill buffers
	g_vertex_buffer_data[vertcounter++] = x;
	g_vertex_buffer_data[vertcounter++] = y;
	g_vertex_buffer_data[vertcounter++] = 0.0f;
	
	g_uv_buffer_data[uvcounter++] = u;
	g_uv_buffer_data[uvcounter++] = v;

	// #############################
	deg -= step*which;
	// create second vertex
	x = cos(deg*DEG_TO_RAD)*radius;
	y = sin(deg*DEG_TO_RAD)*radius;
	u = x/radius;
	v = -y/radius;
	
	// translate UV's from (-1, +1) to (0, +1)
	u /= 2;
	v /= 2;
	u += 0.5f;
	v += 0.5f;
	
	// fill buffers
	g_vertex_buffer_data[vertcounter++] = x;
	g_vertex_buffer_data[vertcounter++] = y;
	g_vertex_buffer_data[vertcounter++] = 0.0f;
	
	g_uv_buffer_data[uvcounter++] = u;
	g_uv_buffer_data[uvcounter++] = v;
	
	// #############################
	// rotate n degrees for the final vertex
	deg -= step;
	
	// create third vertex
	x = cos(deg*DEG_TO_RAD)*radius;
	y = sin(deg*DEG_TO_RAD)*radius;
	u = x/radius;
	v = -y/radius;
	
	// translate UV's from (-1, +1) to (0, +1)
	u /= 2;
	v /= 2;
	u += 0.5f;
	v += 0.5f;
	
	// fill buffers
	g_vertex_buffer_data[vertcounter++] = x;
	g_vertex_buffer_data[vertcounter++] = y;
	g_vertex_buffer_data[vertcounter++] = 0.0f;
	
	g_uv_buffer_data[uvcounter++] = u;
	g_uv_buffer_data[uvcounter++] = v;
	// ####################################################

	//GLuint _vertexbuffer;
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	//GLuint _uvbuffer;
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}
