/**
 * @file color.h
 * 
 * @brief The Color header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef COLOR_H_
#define COLOR_H_

/**
 * @brief A 24 bit RGBA color.
 * 
 * A struct that defines an RGBA Color. Each value is a float between 0.0f and 1.0f.
 */
struct Color
{
	/// @brief constructor
	Color() {
		r = 1.0f;
		g = 1.0f;
		b = 1.0f;
		a = 1.0f;
	}
	/// @brief constructor
	/// @param red The red component of the color
	/// @param green The green component of the color
	/// @param blue The blue component of the color
	/// @param alpha The alpha component of the color
	Color(float red, float green, float blue, float alpha) {
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}
	/// @brief constructor
	/// @param red The red component of the color
	/// @param green The green component of the color
	/// @param blue The blue component of the color
	Color(float red, float green, float blue) {
		r = red;
		g = green;
		b = blue;
		a = 1.0f;
	}
	/**
	 * @brief The red component of the color
	 * 
	 * min: 0.0f, max: 1.0f
	 * 
	 * @var r
	 */
	float r = 1.0f;
	/**
	 * @brief The green component of the color
	 * 
	 * min: 0.0f, max: 1.0f
	 * 
	 * @var g
	 */
	float g = 1.0f;
	/**
	 * @brief The blue component of the color
	 * 
	 * min: 0.0f, max: 1.0f
	 * 
	 * @var b
	 */
	float b = 1.0f;
	/**
	 * @brief The alpha component of the color
	 * 
	 * min: 0.0f, max: 1.0f
	 * 
	 * @var a
	 */
	float a = 1.0f;
	
	/// @brief rotate this color with a step
	/// @param step rotate step
	/// @return Color (*this)
	Color rotate(float step) {
		// make sure we're not white (the default color)
		if (this->r == 1.0f && this->g == 1.0f && this->b == 1.0f) { this->b = 0.0f; }
		
		// rotate
		if (this->b == 1.0f && this->r < 1.0f && this->g == 0.0f) { this->r += step; }
		if (this->g == 1.0f && this->r > 0.0f && this->b == 0.0f) { this->r -= step; }
		if (this->r == 1.0f && this->g < 1.0f && this->b == 0.0f) { this->g += step; }
		if (this->b == 1.0f && this->g > 0.0f && this->r == 0.0f) { this->g -= step; }
		if (this->g == 1.0f && this->b < 1.0f && this->r == 0.0f) { this->b += step; }
		if (this->r == 1.0f && this->b > 0.0f && this->g == 0.0f) { this->b -= step; }
		
		// limit
		if (this->r > 1.0f) { this->r = 1.0f; }
		if (this->r < 0.0f) { this->r = 0.0f; }
		if (this->g > 1.0f) { this->g = 1.0f; }
		if (this->g < 0.0f) { this->g = 0.0f; }
		if (this->b > 1.0f) { this->b = 1.0f; }
		if (this->b < 0.0f) { this->b = 0.0f; }
		
		return *this;
	}
};

#define BLACK   Color(0.0f, 0.0f, 0.0f, 1.0f) ///< @brief Color black
#define GRAY    Color(0.5f, 0.5f, 0.5f, 1.0f) ///< @brief Color gray
#define RED     Color(1.0f, 0.0f, 0.0f, 1.0f) ///< @brief Color red
#define ORANGE  Color(1.0f, 0.5f, 0.0f, 1.0f) ///< @brief Color orange
#define YELLOW  Color(1.0f, 1.0f, 0.0f, 1.0f) ///< @brief Color yellow
#define GREEN   Color(0.0f, 1.0f, 0.0f, 1.0f) ///< @brief Color green
#define CYAN    Color(0.0f, 1.0f, 1.0f, 1.0f) ///< @brief Color cyan
#define BLUE    Color(0.0f, 0.0f, 1.0f, 1.0f) ///< @brief Color blue
#define MAGENTA Color(1.0f, 0.0f, 1.0f, 1.0f) ///< @brief Color magenta
#define PINK    Color(1.0f, 0.5f, 1.0f, 1.0f) ///< @brief Color pink
#define WHITE   Color(1.0f, 1.0f, 1.0f, 1.0f) ///< @brief Color white

#endif /* COLOR_H_ */

