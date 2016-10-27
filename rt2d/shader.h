/**
 * @file shader.h
 *
 * @brief The Shader header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef SHADER_H
#define SHADER_H

/// @brief The Shader class loads vertex and fragment shader files, and compiles them into a Shader.
class Shader
{
public:
	Shader(); ///< @brief Constructor of the Shader
	virtual ~Shader(); ///< @brief Destructor of the Shader

	/// @brief get the programID
	/// @return GLuint _programID
	GLuint programID() { return _programID; };
	/// @brief get the ModelViewProjection MatrixID
	/// @return GLuint _matrixID
	GLuint matrixID() { return _matrixID; };
	/// @brief get the textureID
	/// @return GLuint _textureID
	GLuint textureID() { return _textureID; };
	/// @brief get the blendColorID
	/// @return GLuint _blendColorID
	GLuint blendColorID() { return _blendColorID; };
	/// @brief get the uvOffsetID
	/// @return GLuint _uvOffsetID
	GLuint uvOffsetID() { return _uvOffsetID; };

	/// @brief load shaders from disk
	/// @param vertex_file_path path to vertexshader
	/// @param fragment_file_path path to fragmentshader
	/// @return GLuint _programID
	GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);

private:
	GLuint _programID; ///< @brief programID (pointer to compiled shader)
	GLuint _matrixID; ///< @brief attaches to MVP uniform in shader
	GLuint _textureID; ///< @brief attaches to textureSampler uniform in shader
	GLuint _blendColorID; ///< @brief attaches to vertexColor uniform in shader
	GLuint _uvOffsetID; ///< @brief attaches to UVoffset uniform in shader

	/// @brief attaches matrixID, textureID, vertexcolorID to uniforms in the shaders
	/// @return void
	void _attachID();
};

#endif
