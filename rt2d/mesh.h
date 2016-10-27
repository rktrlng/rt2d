/**
 * @file mesh.h
 *
 * @brief The Mesh header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef MESH_H
#define MESH_H

#include <rt2d/line.h>
#include <rt2d/vectorx.h>

// Include GLEW
#include <GL/glew.h>

/// @brief The Mesh class generates meshes (vertices, normals, UV coordinates).
class Mesh
{
public:
	Mesh(); ///< @brief Constructor of the Mesh
	virtual ~Mesh(); ///< @brief Destructor of the Mesh

	/// @brief get the vertices of the Mesh
	/// @return GLuint _vertexbuffer
	GLuint vertexbuffer() { return _vertexbuffer; };
	// @brief get the normals of the Mesh
	// @return GLuint _normalbuffer
	//GLuint normalbuffer() { return _normalbuffer; };
	/// @brief get the UV's of the Mesh
	/// @return GLuint _uvbuffer
	GLuint uvbuffer() { return _uvbuffer; };

	/// @brief fills vertices, normals and UV's with values for a Sprite Mesh
	/// @param width the width of the Sprite
	/// @param height the height of the Sprite
	/// @param pivotx the x component of the pivot of the Sprite
	/// @param pivoty the y component of the pivot of the Sprite
	/// @param uvwidth 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
	/// @param uvheight 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
	/// @return void
	void generateSpriteMesh(int width, int height,
		float pivotx, float pivoty,
		float uvwidth, float uvheight
	);

	/// @brief fills vertices with values for a Line Mesh
	/// @param line a Line pointer
	/// @return void
	void generateLineMesh(Line* line);
	/// @brief Create a circle of triangles
	/// @param radius the radius of the circle
	/// @param segments the number of segments
	/// @param uvwidth texture size
	/// @param uvheight texture size
	/// @return void
	void generateCircleMesh(int radius, int segments, float uvwidth, float uvheight);
	/// @brief Create a circle of triangles
	/// @param radius the radius of the circle
	/// @param segments the number of segments (6 if hexagon)
	/// @param which which segment (0-5 if hexagon)
	/// @return void
	void generateSegmentMesh(int radius, int segments, int which);

	/// @brief Get the number of vertices in the Mesh
	/// @return unsigned int _numverts
	unsigned int numverts() { return _numverts; };

private:
	GLuint _vertexbuffer; ///< @brief internal list of vertices
	//GLuint _normalbuffer; ///< @brief internal list of normals
	GLuint _uvbuffer; ///< @brief internal list of UV's

	unsigned int _numverts; ///< @brief number of vertices in the Mesh

	/// @brief Generate _vertexbuffer + _uvbuffer
	/// @param vertex a vector of vertices
	/// @param uv a vector of uv coordinates
	/// @return void
	void generateBuffers(std::vector<glm::vec3>& vertex, std::vector<glm::vec2>& uv);
};

#endif /* MESH_H */
