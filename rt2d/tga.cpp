/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <rt2d/tga.h>

TGA::TGA()
{
	this->_stgaFile = NULL;
	this->_tex_buf = NULL;
	this->_tex[0] = 0;
	
	// these values change after loading the image file
	_width = 0;
	_height = 0;
	_depth = 3;
	
	//std::cout << "texture created" << std::endl;
}


TGA::~TGA()
{
	if (this->_stgaFile != NULL) {
		delete this->_stgaFile;
	}
	//std::cout << "TGA closed" << std::endl;
}

void TGA::TGABGR2RGB(STGA& stga)
{
	// this also works as BGRA2RGBA
	long counter = 0;
	long s = stga.width * stga.height;
	for (long i=0; i<s; i++) {
		//swap every 1st byte with every 3rd byte
		unsigned char temp = stga.data[counter];
		stga.data[counter] = stga.data[counter+2];
		stga.data[counter+2] = temp;
		
		counter += stga.byteCount;
	}
}

void TGA::generateTexture(STGA& stga)
{
	// set Entity properties
	this->_width = stga.width;
	this->_height = stga.height;
	this->_depth = stga.byteCount;
	this->_tex_buf = stga.data;
	// =================================================================
	
	// generate a number of texturenames (just 1 for now)
	// if you want to create more, fine. Leave &this->_tex[0] on 0 here. Only change the first argument.
	glGenTextures(1, &this->_tex[0]);

	// setup first texture (the only one in this case)
	// if you create more, use this->_tex[x], where x is the id of the texturename.
	glBindTexture(GL_TEXTURE_2D, this->_tex[0]);
	
	// handle transparency
	if (this->_depth == 4) {
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->_width, this->_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_tex_buf);
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->_width, this->_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->_tex_buf);
	}
}

bool TGA::createWhiteTGA(int width, int height)
{
	std::cout << "Creating TGA: white " << width << "x" << height << std::endl;
	
	_stgaFile = new STGA();
	
	_stgaFile->width = width;
	_stgaFile->height = width;
	_stgaFile->byteCount = 3;

	long file_size = _stgaFile->width * _stgaFile->height * _stgaFile->byteCount;

	//allocate memory for image data
	_stgaFile->data = new unsigned char[file_size];

	//read in image data
	// this also works as BGRA2RGBA
	long counter = 0;
	long s = _stgaFile->width * _stgaFile->height;
	for (long i=0; i<s; i++) {
		_stgaFile->data[counter+0] = 255;
		_stgaFile->data[counter+1] = 255;
		_stgaFile->data[counter+2] = 255;
		
		counter += _stgaFile->byteCount;
	}
	
	// Generate the OpenGL Texture
	generateTexture(*_stgaFile);
	
	return true;
}

bool TGA::loadImage(const std::string& filename)
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
	
	_stgaFile = new STGA();
	
	_stgaFile->width = info[0] + info[1] * 256;
	_stgaFile->height = info[2] + info[3] * 256;
	_stgaFile->byteCount = info[4] / 8;

	if (_stgaFile->byteCount != 3 && _stgaFile->byteCount != 4) {
		std::cout << "bytecount not 3 or 4" << std::endl;
		fclose(file);
		return false;
	}
	
	long file_size = _stgaFile->width * _stgaFile->height * _stgaFile->byteCount;

	//allocate memory for image data
	_stgaFile->data = new unsigned char[file_size];

	//read in image data
	s = fread(_stgaFile->data, sizeof(unsigned char), file_size, file);
	if (s == 0) return false;

	//close file
	fclose(file);
	
	// BGR(A) to RGB(A)
	TGABGR2RGB(*_stgaFile);
	
	// =================================================================
	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((_stgaFile->width & (_stgaFile->width - 1)) != 0) {
		//std::cout << "warning: " << filename << "’s width is not a power of 2" << std::endl;
	}
	if ((_stgaFile->height & (_stgaFile->height - 1)) != 0) {
		//std::cout << "warning: " << filename << "’s height is not a power of 2" << std::endl;
	}
	// But we can't handle non-square images. no-show. silent fail.
	if (_stgaFile->width != _stgaFile->height) {
		std::cout << "warning: " << filename << " is not square *** WARNING *** THIS WILL BREAK (softly) ***" << std::endl;
	}
	// =================================================================
	
	// Generate the OpenGL Texture
	generateTexture(*_stgaFile);
	
	return true;
}
