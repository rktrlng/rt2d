/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <rt2d/image.h>

Image::Image()
{
	this->_pixels = NULL;
	this->_gltexture[0] = 0;
	
	// these values change after loading the image file
	_width = 0;
	_height = 0;
	_depth = 3;
	
	//std::cout << "texture created" << std::endl;
}


Image::~Image()
{
	if (this->_pixels != NULL) {
		delete this->_pixels;
	}
	//std::cout << "Image closed" << std::endl;
}

void Image::BGR2RGB(PixelBuffer& pixels)
{
	// this also works as BGRA2RGBA
	long counter = 0;
	long s = pixels.width * pixels.height;
	for (long i=0; i<s; i++) {
		//swap every 1st byte with every 3rd byte
		unsigned char temp = pixels.data[counter];
		pixels.data[counter] = pixels.data[counter+2];
		pixels.data[counter+2] = temp;
		
		counter += pixels.byteCount;
	}
}

void Image::generateTexture(PixelBuffer& pixels)
{
	// set Entity properties
	this->_width = pixels.width;
	this->_height = pixels.height;
	this->_depth = pixels.byteCount;
	// =================================================================
	
	// generate a number of texturenames (just 1 for now)
	// if you want to create more, fine. Leave &this->_gltexture[0] on 0 here. Only change the first argument.
	glGenTextures(1, &this->_gltexture[0]);

	// setup first texture (the only one in this case)
	// if you create more, use this->_gltexture[x], where x is the id of the texturename.
	glBindTexture(GL_TEXTURE_2D, this->_gltexture[0]);
	
	// handle transparency
	if (this->_depth == 4) {
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data);
	}
}

bool Image::createWhitePixels(int width, int height)
{
	std::cout << "Creating PixelBuffer: white " << width << "x" << height << std::endl;
	
	_pixels = new PixelBuffer();
	
	_pixels->width = width;
	_pixels->height = width;
	_pixels->byteCount = 3;

	long file_size = _pixels->width * _pixels->height * _pixels->byteCount;

	//allocate memory for image data
	_pixels->data = new unsigned char[file_size];

	//read in image data
	// this also works as BGRA2RGBA
	long counter = 0;
	long s = _pixels->width * _pixels->height;
	for (long i=0; i<s; i++) {
		_pixels->data[counter+0] = 255;
		_pixels->data[counter+1] = 255;
		_pixels->data[counter+2] = 255;
		
		counter += _pixels->byteCount;
	}
	
	// Generate the OpenGL Texture
	generateTexture(*_pixels);
	
	return true;
}

bool Image::loadTGAImage(const std::string& filename)
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
	
	_pixels = new PixelBuffer();
	
	_pixels->width = info[0] + info[1] * 256;
	_pixels->height = info[2] + info[3] * 256;
	_pixels->byteCount = info[4] / 8;

	if (_pixels->byteCount != 3 && _pixels->byteCount != 4) {
		std::cout << "bytecount not 3 or 4" << std::endl;
		fclose(file);
		return false;
	}
	
	long file_size = _pixels->width * _pixels->height * _pixels->byteCount;

	//allocate memory for image data
	_pixels->data = new unsigned char[file_size];

	//read in image data
	s = fread(_pixels->data, sizeof(unsigned char), file_size, file);
	if (s == 0) return false;

	//close file
	fclose(file);
	
	// BGR(A) to RGB(A)
	BGR2RGB(*_pixels);
	
	// =================================================================
	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((_pixels->width & (_pixels->width - 1)) != 0) {
		//std::cout << "warning: " << filename << "’s width is not a power of 2" << std::endl;
	}
	if ((_pixels->height & (_pixels->height - 1)) != 0) {
		//std::cout << "warning: " << filename << "’s height is not a power of 2" << std::endl;
	}
	// But we can't handle non-square images. no-show. silent fail.
	if (_pixels->width != _pixels->height) {
		std::cout << "warning: " << filename << " is not square *** WARNING *** THIS WILL BREAK (softly) ***" << std::endl;
	}
	// =================================================================
	
	// Generate the OpenGL Texture
	generateTexture(*_pixels);
	
	return true;
}
