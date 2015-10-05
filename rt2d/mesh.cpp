/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include "mesh.h"

Mesh::Mesh()
{
	_vertexbuffer = 0;
	//_normalbuffer = 0;
	_uvbuffer = 0;
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
	GLfloat g_vertex_buffer_data[] = {
		-width * pivotx, -height * pivoty, 0.0f,
		-width * pivotx, height - (height * pivoty), 0.0f,
		 width - (width * pivotx), height - (height * pivoty), 0.0f,
		 
		 width - (width * pivotx), height - (height * pivoty), 0.0f,
		 width - (width * pivotx), -height * pivoty, 0.0f,
		-width * pivotx, -height * pivoty, 0.0f
	};
/*
	// Normals for each vertex.
	GLfloat g_normal_buffer_data[] = {
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f
	};
*/
	// UV coordinates for each vertex.
	GLfloat g_uv_buffer_data[] = {
		0.0f, uvheight,
		0.0f, 0.0f,
		uvwidth, 0.0f,
		
		uvwidth, 0.0f,
		uvwidth, uvheight,
		0.0f, uvheight
	};

	//GLuint _vertexbuffer;
	glGenBuffers(1, &_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
/*
	//GLuint _normalbuffer;
	glGenBuffers(1, &_normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_normal_buffer_data), g_normal_buffer_data, GL_STATIC_DRAW);
*/
	//GLuint _uvbuffer;
	glGenBuffers(1, &_uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}
