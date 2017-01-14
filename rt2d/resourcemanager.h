/**
 * @file resourcemanager.h
 *
 * @brief The ResourceManager header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <iostream>
#include <string>
#include <map>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

#include <rt2d/rt2dconfig.h>
#include <rt2d/shader.h>
#include <rt2d/texture.h>
#include <rt2d/mesh.h>

/// @brief The ResourceManager class makes sure resources are loaded from disk only once.
class ResourceManager
{
public:
	ResourceManager(); ///< @brief Constructor of the ResourceManager
	virtual ~ResourceManager(); ///< @brief Destructor of the ResourceManager

	/// @brief get a Texture (from disk if need be)
	/// @param filename the path to the TGA file
	/// @param filter the filtering of the Texture
	/// @param wrap the UV wrapping of the Texture
	/// @return Texture* a pointer to a Texture, created from an image file (.tga only).
	Texture* getTexture(const std::string& filename, int filter, int wrap);
	/// @brief Generate a Sprite Mesh
	/// @param width the width of the Sprite
	/// @param height the height of the Sprite
	/// @param pivotx the X component of the pivotpoint of the Sprite
	/// @param pivoty the Y component of the pivotpoint of the Sprite
	/// @param uvwidth the UV width of the SpriteSheet
	/// @param uvheight the UV height of the SpriteSheet
	/// @param circle generate custom Mesh or Circle (0=square Sprite, 6=hexagon)
	/// @param which if a segmentmesh, which segemnt to create (single triangle)
	/// @return Mesh* a pointer to the generated Mesh
	Mesh* getSpriteMesh(int width, int height, float pivotx, float pivoty, float uvwidth, float uvheight, int circle, int which);
	/// @brief Generate a Line Mesh
	/// @param line pointer to a Line
	/// @return Mesh* a pointer to the generated Mesh
	Mesh* getLineMesh(Line* line);
	/// @brief Get a Shader (from disk if need be)
	/// @param vs the vertex Shader
	/// @param fs the fragment Shader ('pixelshader')
	/// @return Shader* a pointer to a Shader
	Shader* getShader(const std::string& vs, const std::string& fs);
	/// @brief clean up resources
	/// @return void
	void cleanup();

private:
	/// @brief delete a Texture from memory
	/// @param filename the name this Texture is known by
	/// @return void
	void deleteTexture(const std::string& filename);
	/// @brief delete a Mesh from memory
	/// @param meshname the name this Mesh is known by
	/// @return void
	void deleteMesh(const std::string& meshname);
	/// @brief delete a Shader from memory
	/// @param shadername the name this Shader is known by
	/// @return void
	void deleteShader(const std::string& shadername);

	std::map<std::string, Texture*> _textures; ///< @brief a map of textures
	std::map<std::string, Mesh*> _meshes; ///< @brief a map of meshes
	std::map<std::string, Shader*> _shaders; ///< @brief a map of shaders
};

#endif /* RESOURCEMANAGER_H */
