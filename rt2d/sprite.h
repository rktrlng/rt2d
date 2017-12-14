/**
 * @file sprite.h
 *
 * @brief The Sprite header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
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
	Sprite(); ///< @brief Constructor of the Sprite
	virtual ~Sprite(); ///< @brief Destructor of the Sprite

	/// @brief get the texturename (path to the file)
	/// @return std::string _texturename
	std::string texturename() { return _texturename; };
	/// @brief set the texturename (path to the file)
	/// @param texturename path to fragmentshader
	/// @return void
	void texturename(std::string texturename) { _texturename = texturename; };

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

	/// @brief get the width (of the texture)
	/// @return int size.x
	int width() { return (int) this->size.x; };
	/// @brief get the height (of the texture)
	/// @return int size.y
	int height() { return (int) this->size.y; };

	Point3 spriteposition; ///< @brief Sprite position Point_t of the Sprite (only for Spritebatches)
	Point3 spriterotation; ///< @brief Sprite rotation of the Sprite (only for Spritebatches)
	Point3 spritescale; ///< @brief Sprite scale Point_t of the Sprite (only for Spritebatches)

	Point2 pivot; ///< @brief Pivot Point_t of the Sprite
	Point2 uvdim; ///< @brief UVdim Point_t of the Sprite (uvwidth, uvheight. The size of the part we need to render)
	Point2 uvoffset; ///< @brief UVoffset Point_t of the Sprite (which part do we need to render)
	Point2 size; ///< @brief size Point_t of the Sprite (width and height of the Sprite)
	RGBAColor color; ///< @brief blend Color of the Sprite

	Point3 customParams[8]; ///< @brief custom Params that are sent to the shader

	/// @brief prepare Sprite for creation by ResourceManager
	/// @param filename path to the image.tga
	/// @param pivotx X component of Pivot Point_t of the Sprite
	/// @param pivoty Y component of Pivot Point_t of the Sprite
	/// @param uvwidth 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
	/// @param uvheight 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
	/// @return void
	void setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight);
	/// @brief prepare Circle Sprite for creation by ResourceManager
	/// @param filename path to the image.tga
	/// @param radius of the circle
	/// @param segments of the circle
	/// @return void
	void setupCircleSprite(const std::string& filename, int radius, int segments);
	/// @brief prepare Circle Sprite for creation by ResourceManager
	/// @param filename path to the image.tga
	/// @param radius of the circle
	/// @param segments of the circle
	/// @param which which part of the circle
	/// @return void
	void setupSegmentSprite(const std::string& filename, int radius, int segments, int which);
	/// @brief prepare Sprite for creation by ResourceManager
	/// @param filename path to the image.tga
	/// @param pivotx X component of Pivot Point_t of the Sprite
	/// @param pivoty Y component of Pivot Point_t of the Sprite
	/// @param uvwidth 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
	/// @param uvheight 1.0f=full texture, 0.5f=2x2 texture, 0.25f=4x4 texture etc.
	/// @param filter filter of the Sprite Texture
	/// @param wrap wrapping of the Sprite Texture
	/// @return void
	void setupSprite(const std::string& filename, float pivotx, float pivoty, float uvwidth, float uvheight, int filter, int wrap);
	/// @brief Fill the PixelBuffer of this Sprite.
	/// @param pixels a PixelBuffer pointer
	/// @return void
	void setupSpriteByPixelBuffer(PixelBuffer* pixels);
	/// @brief Fill the PixelBuffer of this Sprite with pixels from a file.
	/// @param filename path to the image.tga
	/// @param filter filter of the Sprite Texture
	/// @param wrap wrapping of the Sprite Texture
	/// @return void
	void setupSpriteTGAPixelBuffer(const std::string& filename, int filter, int wrap);

	/// @brief set the palette sampler1D
	/// @param filename path to the image.tga
	/// @return void
	void setPalette(const std::string& filename);
	/// @brief get the palette sampler1D
	/// @return Texture* _palette
	Texture* palette() { return _palette; };

	/// @brief get the dynamic texture
	/// @return Texture* _dyntexture
	Texture* texture() { return _dyntexture; };
	/// @brief is this Line dynamic or not?
	/// @return bool _dynamic
	bool dynamic() { return _dynamic; };
	/// @brief set this Line to be dynamic or not
	/// @return void
	void dynamic(bool d) { _dynamic = d; };

	/// @brief set filter for this Sprite
	/// @return void
	void filter(int f) { _filter = f; };
	/// @brief get filter for this Sprite
	/// @return int _filter
	int filter() { return _filter; };
	/// @brief set wrap for this Sprite
	/// @return void
	void wrap(int w) { _wrap = w; };
	/// @brief get wrap for this Sprite
	/// @return int _wrap
	int wrap() { return _wrap; };

	/// @brief get which segment of circle this sprite has.
	/// @return int _which
	int which() { return _which; };
	/// @brief get if this is a circlemesh or not.
	///
	/// 0 = no circlemesh
	/// n = amounts of total segments in the circle (6 for hexagon)
	/// @return int _circlemesh
	int circlemesh() { return _circlemesh; };

	/// @brief check if this Sprite uses culling
	/// @return int _useculling
	int useCulling() { return _useculling; };
	/// @brief use culling on this Sprite or not
	/// @return void
	void useCulling(int c) { _useculling = c; };

protected:

private:
	int _frame; ///< @brief the active frame of the SpriteSheet

	std::string _texturename; ///< @brief texturename (path to the file)

	std::string _fragmentshader; ///< @brief fragmentshader (path to the file)
	std::string _vertexshader; ///< @brief vertexshader (path to the file)

	Texture* _palette; ///< @brief the palette

	Texture* _dyntexture; ///< @brief the dynamic texture
	bool _dynamic; ///< @brief dynamic or not

	int _filter; ///< @brief texture filtering
	int _wrap; ///< @brief texture wrapping

	int _circlemesh; ///< @brief are we a square Sprite (0), or a custom one (not 0)
	int _which; ///< @brief which segment

	int _useculling; ///< @brief use culling or not
};

#endif /* SPRITE_H */
