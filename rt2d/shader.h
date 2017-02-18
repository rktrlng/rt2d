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
	/// @return GLint _programID
	GLint programID() { return _programID; };
	/// @brief get the ModelViewProjection MatrixID
	/// @return GLint _matrixID
	GLint matrixID() { return _matrixID; };
	/// @brief get the textureID
	/// @return GLint _textureID
	GLint textureID() { return _textureID; };
	/// @brief get the blendColorID
	/// @return GLint _blendColorID
	GLint blendColorID() { return _blendColorID; };
	/// @brief get the uvOffsetID
	/// @return GLint _uvOffsetID
	GLint uvOffsetID() { return _uvOffsetID; };
	/// @brief get the customParamsID
	/// @return GLint _customParamsID[i]
	GLint customParamsID(int i) { return _customParamsID[i]; };
	/// @brief get the paletteID
	/// @return GLint _paletteID
	GLint paletteID() { return _paletteID; };

	/// @brief load shaders from disk
	/// @param vertex_file_path path to vertexshader
	/// @param fragment_file_path path to fragmentshader
	/// @return GLuint _programID
	GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);

private:
	GLint _programID; ///< @brief programID (pointer to compiled shader)
	GLint _matrixID; ///< @brief attaches to MVP uniform in shader
	GLint _textureID; ///< @brief attaches to textureSampler2D uniform in shader
	GLint _blendColorID; ///< @brief attaches to blendColor uniform in shader
	GLint _uvOffsetID; ///< @brief attaches to UVoffset uniform in shader
	GLint _customParamsID[8]; ///< @brief attaches to customParams uniform in shader
	GLint _paletteID; ///< @brief attaches to paletteSampler1D uniform in shader

	/// @brief attaches matrixID, textureID, vertexcolorID to uniforms in the shaders
	/// @return void
	void _attachID();
};

#endif
