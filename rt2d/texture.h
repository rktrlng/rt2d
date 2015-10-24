/**
 * @file texture.h
 * 
 * @brief The Texture header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <GL/glew.h>

#include <glfw3.h>

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

/// @brief The Texture class loads images from files and converts them to OpenGL textures.
class Texture
{
	public:
		Texture();			///< @brief Constructor of the Texture
		virtual ~Texture();	///< @brief Destructor of the Texture

		/// @brief get the OpenGL texture
		/// @return GLuint _texture
		GLuint getGLTexture() { return _gltexture[0]; };

		/// @brief get the width of the OpenGL texture
		/// @return int _width
		int width() { return _width; };
		/// @brief get the height of the OpenGL texture
		/// @return int _height
		int height() { return _height; };
		/// @brief bytes per pixel. 3=RGB, 4=RGBA.
		/// @return int _depth
		int depth() { return _depth; };
		
		/// @brief load an image from file (tga only)
		/// @param filename the path to the image
		/// @return GLuint _texture, 0 if failed
		GLuint loadTGAImage(const std::string& filename);
		/// @brief create a width x height white PixelBuffer & GLpixeldata
		/// @param width the width of the white Texture
		/// @param height the height of the white Texture
		/// @return GLuint _texture, 0 if failed
		GLuint createWhitePixels(int width, int height);
	
	private:
		/// @brief swap every first and third byte of the pixels
		//void BGR2RGB(PixelBuffer& pixels);
		void BGR2RGB();
		/// @brief generate the OpenGL texture
		void generateTexture();

		/// @brief the width of the file
		int _width;
		/// @brief the height of the file
		int _height;
		/// @brief the color depth of the pixels
		int _depth;
		/// @brief a pointer to the PixelBuffer
		PixelBuffer* _pixels;
		/// @brief a number of texture names (1 for now)
		GLuint _gltexture[1];
		
		/// @brief save filter level for this Texture
		int _filtering;
		/**
		 * @brief level of filtering
		 * 
		 * 0 = no filtering.
		 * 1 = Linear filtering.
		 * 2 = Bilinear filtering.
		 * 3 = Trilinear filtering.
		 * 
		 * @param level
		 */
		void _filterTexture(int level);
};

#endif
