/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rt2d/texture.h>
#include <rt2d/image.h>

//#pragma GCC diagnostic ignored "-Wstrict-aliasing"

Texture::Texture()
{
	_texture = 0; // texture handle

	_width = 0;
	_height = 0;
	
	_filtering = 3;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_texture);
	//std::cout << "========> Texture deleted" << std::endl;
}

GLuint Texture::loadImage(const std::string& filename)
{
	//printf("LOADING: %s\n", filename.c_str());
	std::string ext = filename.substr(filename.length()-3);
	if (ext.compare("tga") == 0) {
		return loadTGA(filename.c_str());
	}
	printf("Can not load Texture: %s (only tga)\n", filename.c_str());
	return 0;
}

GLuint Texture::createWhite(int width, int height)
{
	// Create white Texture
	Image image;
	image.createWhitePixels(width, height);
	_texture = image.textureData();
	
	// get Width & Height
	_width = image.width();
	_height = image.height();
	
	_filterTexture(0);
	
	return _texture;
}

void Texture::_filterTexture(int level)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (level == 0) {
		// No filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	} else if (level == 1) {
		// Linear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	} else if (level == 2) {
		// Bilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); 
		glGenerateMipmap(GL_TEXTURE_2D);
	} else if (level == 3) {
		// Trilinear filtering.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
		glGenerateMipmap(GL_TEXTURE_2D);
	}
}

GLuint Texture::loadTGA(const char * imagepath)
{
	// Load texture from TGA file
	Image tga;
	tga.loadTGAImage(imagepath);
	_texture = tga.textureData();
	
	// get Width & Height
	_width = tga.width();
	_height = tga.height();
	
	_filterTexture(_filtering);
	
	return _texture;
}
