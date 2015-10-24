/**
 * @file image.h
 * 
 * @brief The Image header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <iostream>
#include <cstdio>

// Include GLEW
//#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

/// @brief an Image contains the OpenGL pixeldata
class Image
{
	public:
		/// @brief constructor
		Image();
		/// @brief destructor
		virtual ~Image();

		/// @brief the pixeldata of the Texture
		GLuint textureData() { return _gltexture[0]; };

		/// @brief load a TGA image from disk
		/// @param filename the path to the file
		bool loadTGAImage(const std::string& filename);
		/// @brief create a width x height white PixelBuffer & GL pixeldata
		bool createWhitePixels(int width, int height);

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
		/// @brief defines a PixelBuffer
		struct PixelBuffer
		{
			/// @brief constructor
			PixelBuffer()
			{
				/// @brief initialize the pixel data
				data = (unsigned char*)0;
				/// @brief initialize the width of the buffer
				width = 0;
				/// @brief initialize the height of the buffer
				height = 0;
				/// @brief initialize the color depth of the pixels
				byteCount = 0;
				
				//std::cout << "create PixelBuffer" << std::endl;
			}

			/// @brief destructor
			~PixelBuffer() { delete[] data; data = 0; /*std::cout << "delete PixelBuffer" << std::endl;*/ }

			/// @brief destroy the pixel data
			void destroy() { delete[] data; data = 0; /*std::cout << "destroy PixelBuffer" << std::endl;*/ }

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
		void BGR2RGB(PixelBuffer& pixels);
		/// @brief generate the OpenGL texture
		void generateTexture(PixelBuffer& pixels);

		/// @brief the width of the file
		int _width;
		/// @brief the height of the file
		int _height;
		/// @brief the color depth of the pixels
		int _depth;
		/// @brief a pointer to the TGA file
		PixelBuffer* _pixels;
		/// @brief a number of texture names
		GLuint _gltexture[1];
};

#endif /* IMAGE_H */ 
