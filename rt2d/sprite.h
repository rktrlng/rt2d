/**
 * @file sprite.h
 * 
 * @brief The Sprite header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>

#include <rt2d/texture.h>
#include <rt2d/color.h>
#include <rt2d/pointx.h>

/// @brief The Sprite class defines the Texture, Shader, blend Color and pivot point of a Sprite.
class Sprite
{
	public:
		Sprite();			///< @brief Constructor of the Sprite
		virtual ~Sprite();	///< @brief Destructor of the Sprite

		/// @brief get the texturename (path to the file)
		/// @return std::string _texturename
		std::string texturename() { return _texturename; };
		/// @brief get the PixelBuffer
		/// @return PixelBuffer* _pixelbuffer
		PixelBuffer* pixels() { return _pixelbuffer; };
		/*
		// This is an attempt to copy pixels to the PixelBuffer
		// TODO: make it work (@see Renderer::_renderSprite())
		void setPixelBuffer(PixelBuffer* px) { 
			//setupSpriteByPixelBuffer(px);
			deletePixelBuffer();
			_pixelbuffer = new PixelBuffer(px->width, px->height, px->bitdepth, px->filter);
			long file_size = _pixelbuffer->width * _pixelbuffer->height * _pixelbuffer->bitdepth;
			for (long i=0; i<file_size; i++) {
				_pixelbuffer->data[i] = px->data[i];
			}
			// *_pixelbuffer->data = *px->data;
		};
		*/

		/// @brief get the fragmentshader (path to the file)
		/// @return std::string _fragmentshader
		std::string fragmentshader() { return _fragmentshader; };
		/// @brief get the vertexshader (path to the file)
		/// @return std::string _vertexshader
		std::string vertexshader() { return _vertexshader; };
		/// @brief set the fragmentshader (path to the file)
		/// @param fragmentshader path to fragmentshader
		/// @return void
		void fragmentshader(std::string fragmentshader) { _fragmentshader = fragmentshader; };
		/// @brief set the vertexshader (path to the file)
		/// @param vertexshader path to vertexshader
		/// @return void
		void vertexshader(std::string vertexshader) { _vertexshader = vertexshader; };

		/// @brief set the current frame
		/// @return int _frame
		int frame(int f);
		/// @brief get the current frame
		/// @return int _frame
		int frame() { return _frame; };
		
		Point2 pivot;	///< @brief Pivot Point_t of the Sprite
		Point2 uvdim;	///< @brief UVdim Point_t of the Sprite (uvwidth, uvheight. The size of the part we need to render)
		Point2 uvoffset;	///< @brief UVoffset Point_t of the Sprite (which part do we need to render)
		Point2 size;	///< @brief size Point_t of the Sprite (width and height of the Sprite)
		Color color;		///< @brief blend Color of the Sprite

		/// @brief prepare Sprite for creation by ResourceManager
		/// @param filename path to the image.tga
		/// @param pivotx X component of Pivot Point_t of the Sprite
		/// @param pivoty Y component of Pivot Point_t of the Sprite
		/// @param uvwidth 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
		/// @param uvheight 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
		/// @return void
		void setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight);
		/// @brief Fill the PixelBuffer of this Sprite.
		/// @param pixels a PixelBuffer pointer
		/// @return void
		void setupSpriteByPixelBuffer(PixelBuffer* pixels);
	
	protected:
	
	private:
		int _frame;	///< @brief the active frame of the SpriteSheet
		
		std::string _texturename; ///< @brief texturename (path to the file)
		
		std::string _fragmentshader; ///< @brief fragmentshader (path to the file)
		std::string _vertexshader; ///< @brief vertexshader (path to the file)
		
		PixelBuffer* _pixelbuffer; ///< @brief pixelbuffer pointer. Will not be used if NULL.
		
		/// @brief delete the PixelBuffer of this Entity.
		/// @return void
		void deletePixelBuffer() {
			if (_pixelbuffer != NULL) {
				delete _pixelbuffer;
				_pixelbuffer = NULL;
			}
		};
};

#endif /* SPRITE_H */ 
