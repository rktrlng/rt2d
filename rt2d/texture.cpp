/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <GL/glew.h>

#include <rt2d/texture.h>

//#pragma GCC diagnostic ignored "-Wstrict-aliasing"

Texture::Texture()
{
	// these values change after handling pixels
	_width = 0;
	_height = 0;
	_depth = 3;

	_gltexture[0] = 0;
	_pixelbuffer = nullptr;

	_warrantybit = 1;

	//std::cout << "texture created" << std::endl;
}

Texture::~Texture()
{
	glDeleteTextures(1, &_gltexture[0]);

	deletePixelBuffer();

	//std::cout << "========> Texture deleted" << std::endl;
}

GLuint Texture::createWhitePixels(int width, int height)
{
	std::cout << "Creating PixelBuffer: white " << width << "x" << height << std::endl;

	PixelBuffer pixels = PixelBuffer(width, height, 3, 0, 0);

	// Generate the OpenGL Texture
	createFromBuffer(&pixels, 2);

	return _gltexture[0];
}

// http://paulbourke.net/dataformats/tga/
GLuint Texture::loadTGAImage(const std::string& filename, int filter, int wrap, int dim)
{
	std::cout << "Loading TGA: " << filename << std::endl;

	// Load .tga file
	FILE *file;
	unsigned char type[4];
	unsigned char info[6];

	file = fopen(filename.c_str(), "rb");

	if (!file) {
		std::cout << "unable to open file" << std::endl;
		return false;
	}

	size_t s;
	s = fread (&type, sizeof (char), 3, file);
	fseek (file, 12, SEEK_SET);
	s = fread (&info, sizeof (char), 6, file);

	//image type needs to be 2 (color) or 3 (grayscale)
	if (type[1] != 0 || (type[2] != 2 && type[2] != 3))
	{
		std::cout << "image type neither color or grayscale" << std::endl;
		fclose(file);
		return false;
	}

	PixelBuffer pixels = PixelBuffer();

	pixels.width = info[0] + info[1] * 256;
	pixels.height = info[2] + info[3] * 256;
	pixels.bitdepth = info[4] / 8;
	pixels.filter = filter;
	pixels.wrap = wrap;

	if (pixels.bitdepth != 1 && pixels.bitdepth != 3 && pixels.bitdepth != 4) {
		std::cout << "bytecount not 1, 3 or 4" << std::endl;
		fclose(file);
		return false;
	}

	long file_size = pixels.width * pixels.height * pixels.bitdepth;

	//allocate memory for image data
	pixels.data = new unsigned char[file_size];

	//read in image data
	s = fread(pixels.data, sizeof(unsigned char), file_size, file);
	if (s == 0) return false;

	//close file
	fclose(file);

	// BGR(A) to RGB(A)
	if (pixels.bitdepth == 3 || pixels.bitdepth == 4) {
		BGR2RGB(&pixels);
	}

	// =================================================================
	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((pixels.width & (pixels.width - 1)) != 0) {
		_warrantybit = 0;
		//std::cout << "warning: " << filename << "’s width is not a power of 2" << std::endl;
	}
	if ((pixels.height & (pixels.height - 1)) != 0) {
		_warrantybit = 0;
		//std::cout << "warning: " << filename << "’s height is not a power of 2" << std::endl;
	}
	if (pixels.width != pixels.height) {
		//_warrantybit = 0;
		//std::cout << "warning: " << filename << " is not square" << std::endl;
	}
	// =================================================================

	// Generate the OpenGL Texture
	createFromBuffer(&pixels, dim);

	return _gltexture[0];
}

// http://paulbourke.net/dataformats/tga/
int Texture::writeTGAImage(std::string filename /* std::string() */)
{
	static int id = 0;

	if (filename.empty()) {
		time_t t = time(nullptr);
		filename = "rt2d_" + std::to_string(t) + "_" + std::to_string(id) + ".tga";
		id++;
	}

	FILE *fp = fopen(filename.c_str(), "wb");
	if (fp == nullptr) {
		return 0;
	}

	// The image header
	unsigned char header[ 18 ] = { 0 };
	header[ 2 ] = 2; // true color
	header[ 12 ] = _pixelbuffer->width & 0xFF;
	header[ 13 ] = (_pixelbuffer->width >> 8) & 0xFF;
	header[ 14 ] = _pixelbuffer->height & 0xFF;
	header[ 15 ] = (_pixelbuffer->height >> 8) & 0xFF;
	header[ 16 ] = _pixelbuffer->bitdepth * 8;

	fwrite((const char*)&header, 1, sizeof(header), fp);

	// The image data is stored bottom-to-top, left-to-right
	unsigned int counter = 0;
	for (int y = _pixelbuffer->height-1; y >= 0; y--) {
		for (int x = 0; x < _pixelbuffer->width; x++) {
			putc((int)(_pixelbuffer->data[counter+2] & 0xFF), fp); // b
			putc((int)(_pixelbuffer->data[counter+1] & 0xFF), fp); // g
			putc((int)(_pixelbuffer->data[counter+0] & 0xFF), fp); // r
			if (_pixelbuffer->bitdepth == 4) {
				putc((int)(_pixelbuffer->data[counter+3] & 0xFF), fp);
			}
			counter += _pixelbuffer->bitdepth;
		}
	}
/*
	// The file footer
	static const char footer[ 26 ] =
	"\0\0\0\0" // no extension area
	"\0\0\0\0" // no developer directory
	"TRUEVISION-XFILE" // https://en.wikipedia.org/wiki/Truevision_TGA
	".";
	fwrite((const char*)&footer, 1, sizeof(footer), fp);
*/
	fclose(fp);
	//std::cout << "WROTE " << filename << std::endl;

	return 1;
}

void Texture::BGR2RGB(PixelBuffer* pixels)
{
	// this also works as BGRA2RGBA
	long counter = 0;
	long s = pixels->width * pixels->height;
	for (long i=0; i<s; i++) {
		//swap every 1st byte with every 3rd byte
		unsigned char temp = pixels->data[counter];
		pixels->data[counter] = pixels->data[counter+2];
		pixels->data[counter+2] = temp;

		counter += pixels->bitdepth;
	}
}

void Texture::createFromBuffer(PixelBuffer* pixels, int dim)
{
	//allocate memory and copy image data to pixelBuffer
	deletePixelBuffer();

	if (pixels->bitdepth == 1) {
		// use 8-bit grayscale texture as 32-bit white + alpha
		_pixelbuffer = new PixelBuffer(pixels->width, pixels->height, 4, pixels->filter, pixels->wrap);
		int size = pixels->width * pixels->height;
		int counter = 0;
		for (int i = 0; i < size; i++) {
			_pixelbuffer->data[counter+0] = 255;
			_pixelbuffer->data[counter+1] = 255;
			_pixelbuffer->data[counter+2] = 255;
			_pixelbuffer->data[counter+3] = pixels->data[(counter+3)/4];

			counter += 4;
		}
	} else {
		_pixelbuffer = new PixelBuffer(pixels->width, pixels->height, pixels->bitdepth, pixels->filter, pixels->wrap);
		int size = pixels->width * pixels->height * pixels->bitdepth;
		for (int i = 0; i < size; i++) {
			_pixelbuffer->data[i] = pixels->data[i];
		}
	}

	// set Entity properties
	this->_width = pixels->width;
	this->_height = pixels->height;
	this->_depth = pixels->bitdepth;
	// =================================================================

	// generate a number of texturenames (just 1 for now)
	glGenTextures(1, this->_gltexture);

	// 2D Texture (diffuse)
	if (dim == 2) {
		// setup first texture (the only one in this case)
		// if you created more, use this->_gltexture[x], where x is the id of the texturename.
		glBindTexture(GL_TEXTURE_2D, this->_gltexture[0]);
		//glEnable(GL_TEXTURE_2D);

		// handle transparency
		if (this->_depth == 4) {
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels->data);
		}
		if (this->_depth == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels->data);
		}
		if (this->_depth == 1) {
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pixelbuffer->data);
		}

		// 0 = GL_REPEAT
		// 1 = GL_MIRRORED_REPEAT
		// 2 = GL_CLAMP_TO_EDGE
		if (pixels->wrap == 0) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		} else if (pixels->wrap == 1) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		} else if (pixels->wrap == 2) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		// filter the Texture
		if (pixels->filter == 0) {
			// No filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		} else if (pixels->filter == 1) {
			// Linear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		} else if (pixels->filter == 2) {
			// Bilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
		} else if (pixels->filter == 3) {
			// Trilinear filtering.
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	// 1D texture (palette)
	if (dim == 1) {
		glBindTexture(GL_TEXTURE_1D, this->_gltexture[0]);

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		// this assumes an RGB palette TODO fix
		glTexImage1D(GL_TEXTURE_1D, 0, 3, pixels->width, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels->data);

		//glEnable(GL_TEXTURE_1D);
	}

}
