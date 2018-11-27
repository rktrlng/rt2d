/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 *
 * loadShaders() code originally from: http://www.opengl-tutorial.org
 */

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>
using namespace std;

#include <GL/glew.h>

#include <rt2d/shader.h>

Shader::Shader()
{
	_programID =     -1;
	_matrixID =      -1;
	_textureID  =    -1;
	_blendColorID =  -1;
	_uvOffsetID =    -1;
	for (int i = 0; i < 8; i++) {
		_customParamsID[i] = -1;
	}
	_paletteID =     -1;
}

Shader::~Shader()
{
	glDeleteProgram(_programID);
	//glDeleteTextures(1, &_textureID);
}

void Shader::_attachID()
{
	// Get handles for our uniforms and buffers and send them to the shader
	_matrixID =      glGetUniformLocation(_programID, "MVP"); // MVP uniform in vertex shader

	_textureID  =    glGetUniformLocation(_programID, "textureSampler"); // textureSampler uniform in fragment shader
	_blendColorID =  glGetUniformLocation(_programID, "blendColor"); // blendColor uniform in fragment shader
	_uvOffsetID = 	 glGetUniformLocation(_programID, "UVoffset"); // UVoffset uniform in fragment shader
	_paletteID =     glGetUniformLocation(_programID, "palette"); // palette uniform in fragment shader

	// probably not the best way to set the shader variables, but here we are...
	for (int i = 0; i < 8; i++) {
		char customParams[18]; // should be enough
		customParams[17] = '\0';
		sprintf(customParams,"customParams[%d]",i);
		_customParamsID[i] = glGetUniformLocation(_programID, customParams);
	}
}

GLuint Shader::loadShaders(const char * vertex_file_path, const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line)) {
			VertexShaderCode += "\n" + Line;
		}
		VertexShaderStream.close();
	}else{
		printf("Can't open %s\n", vertex_file_path);
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line)) {
			FragmentShaderCode += "\n" + Line;
		}
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		printf("%s", &VertexShaderErrorMessage[0]);
	}


	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		printf("%s", &FragmentShaderErrorMessage[0]);
	}


	// Link the program
	//printf("Linking program\n");
	_programID = glCreateProgram();
	glAttachShader(_programID, VertexShaderID);
	glAttachShader(_programID, FragmentShaderID);
	glLinkProgram(_programID);

	// Check the program
	glGetProgramiv(_programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(_programID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s", &ProgramErrorMessage[0]);
	}

	glDetachShader(_programID, VertexShaderID);
	glDetachShader(_programID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	this->_attachID();

	return _programID;
}
