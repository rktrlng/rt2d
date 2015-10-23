/**
 * @file tga.h
 * 
 * @brief The TGA header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef TGA_H
#define TGA_H

#include <string>
#include <iostream>
#include <cstdio>

// Include GLEW
//#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

/// @brief a TGA contains the OpenGL pixeldata
class TGA
{
	public:
		/// @brief constructor
		TGA();
		/// @brief destructor
		virtual ~TGA();

		/// @brief the pixeldata of the Texture
		GLuint pixelData() { return _tex[0]; };

		/// @brief load an image from disk
		/// @param filename the path to the file
		bool loadImage(const std::string& filename);
		/// @brief create a width x height white TGA file
		bool createWhiteTGA(int width, int height);

		/// @brief width of the tga
		/// @return int _width
		int width() { return _width; };
		/// @brief height of the tga
		/// @return int _height
		int height() { return _height; };
		/// @brief bytes per pixel. 3=RGB, 4=RGBA.
		/// @return int _depth
		int depth() { return _depth; };

	private:
		/// @brief defines a TGA file
		struct STGA
		{
			/// @brief constructor
			STGA()
			{
				/// @brief initialize the pixel data
				data = (unsigned char*)0;
				/// @brief initialize the width of the file
				width = 0;
				/// @brief initialize the height of the file
				height = 0;
				/// @brief initialize the color depth of the pixels
				byteCount = 0;
				
				//std::cout << "create STGA" << std::endl;
			}

			/// @brief destructor
			~STGA() { delete[] data; data = 0; /*std::cout << "delete STGA" << std::endl;*/ }

			/// @brief destroy the pixel data
			void destroy() { delete[] data; data = 0; /*std::cout << "destroy STGA" << std::endl;*/ }

			/// @brief the width of the file
			int width;
			/// @brief the height of the file
			int height;
			/// @brief the size of the file
			unsigned char byteCount;
			/// @brief the pixel data
			unsigned char* data;
		};

		/// @brief swap every first and third byte of the pixels
		void TGABGR2RGB(STGA& stga);
		/// @brief generate the OpenGL texture
		void generateTexture(STGA& stga);

		/// @brief the width of the file
		int _width;
		/// @brief the height of the file
		int _height;
		/// @brief the color depth of the pixels
		int _depth;
		/// @brief a pointer to the TGA file
		STGA * _stgaFile;
		/// @brief a number of texture names
		GLuint _tex[1];
		/// @brief a texture buffer of bytes
		unsigned char * _tex_buf;
};

#endif /* TGA_H */ 
