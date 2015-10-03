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
	this->_tgaFile = NULL;
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
	if (this->_tgaFile != NULL) {
		delete this->_tgaFile;
	}
	//std::cout << "TGA closed" << std::endl;
}

void TGA::TGABGR2RGB(STGA& tga)
{
	// this also works as BGRA2RGBA
	long counter = 0;
	long s = tga.width * tga.height;
	for (long i=0; i<s; i++) {
		//swap every 1st byte with every 3rd byte
		unsigned char temp = tga.data[counter];
		tga.data[counter] = tga.data[counter+2];
		tga.data[counter+2] = temp;
		
		counter += tga.byteCount;
	}
}

void TGA::generateTexture(STGA& tga)
{
	// set Entity properties
	this->_width = tga.width;
	this->_height = tga.height;
	this->_depth = tga.byteCount;
	this->_tex_buf = tga.data;
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

bool TGA::loadImage(const std::string& filename)
{
	std::cout << "Loading: " << filename << std::endl;
	
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
	
	_tgaFile = new STGA();
	
	_tgaFile->width = info[0] + info[1] * 256;
	_tgaFile->height = info[2] + info[3] * 256;
	_tgaFile->byteCount = info[4] / 8;

	if (_tgaFile->byteCount != 3 && _tgaFile->byteCount != 4) {
		std::cout << "bytecount not 3 or 4" << std::endl;
		fclose(file);
		return false;
	}
	
	long file_size = _tgaFile->width * _tgaFile->height * _tgaFile->byteCount;

	//allocate memory for image data
	_tgaFile->data = new unsigned char[file_size];

	//read in image data
	s = fread(_tgaFile->data, sizeof(unsigned char), file_size, file);
	if (s == 0) return false;

	//close file
	fclose(file);
	
	// BGR(A) to RGB(A)
	TGABGR2RGB(*_tgaFile);
	
	// =================================================================
	// Check if the image's width and height is a power of 2. No biggie, we can handle it.
	if ((_tgaFile->width & (_tgaFile->width - 1)) != 0) {
		//std::cout << "warning: " << filename << "’s width is not a power of 2" << std::endl;
	}
	if ((_tgaFile->height & (_tgaFile->height - 1)) != 0) {
		//std::cout << "warning: " << filename << "’s height is not a power of 2" << std::endl;
	}
	// But we can't handle non-square images. no-show. silent fail.
	if (_tgaFile->width != _tgaFile->height) {
		std::cout << "warning: " << filename << " is not square *** WARNING *** THIS WILL BREAK (softly) ***" << std::endl;
	}
	// =================================================================
	
	// Generate the OpenGL Texture
	generateTexture(*_tgaFile);
	
	return true;
}
