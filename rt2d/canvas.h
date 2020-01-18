/**
 * @file canvas.h
 *
 * @brief The Canvas header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <rt2d/entity.h>

/// @brief A pixel
struct Pixel {
	/// @brief position relative to the 'pivotpoint' of a pixelsprite or canvas (0.0)
	Point2i position;
	/// @brief color of the pixel
	RGBAColor color;

	/// @brief constructor
	/// @param pos the position of the pixel
	/// @param c the color of the pixel
	Pixel(Point2i pos, RGBAColor c) { position = pos; color = c; };
};

/// @brief A pixelsprite
struct PixelSprite {
	/// @brief a collection of pixels
	std::vector<Pixel> pixels;
	/// @brief position of the pixelsprite on the canvas
	Point2i position;

	/// @brief simple color pallete
	RGBAColor pallete[10] = {
		MAGENTA, // 0 shouldn't generate a pixel
		WHITE,
		BLUE,
		MAGENTA,
		RED,
		GREEN,
		YELLOW,
		PINK,
		ORANGE,
		GRAY
	};

	/// @brief initialize the pixelsprite
	/// @param data an array of chars. each char is the index of pallete
	/// @param w the width of the pixelsprite
	/// @param h the height of the pixelsprite
	/// @return void
	void init(char* data, int w, int h) {
		RGBAColor color;
		size_t size = w*h;
		for (size_t i = 0; i < size; i++) {
			int y=i/w;
			int x=i%w;

			int value = (int) data[i];
			if (value != 0) {
				color = pallete[value];
				//this->pixels.push_back( Pixel(Point2i(x, y*-1), color) ); // pivot at (0,0)
				this->pixels.push_back( Pixel(Point2i(x-(w/2), (y*-1)+(h/2)), color) ); // pivot centered
			}
		}
	};

	/// @brief create line pixels from a Vector2
	/// @param vec the Vector2 to draw
	/// @param color the RGBAColor of the line
	/// @return void
	void createLine(Vector2f vec, RGBAColor color) {
		float x0 = 0.0f;
		float y0 = 0.0f;
		float x1 = vec.x;
		float y1 = vec.y;

		bool steep = false;
		if (std::abs(x0-x1) < std::abs(y0-y1)) {
			std::swap(x0, y0);
			std::swap(x1, y1);
			steep = true;
		}
		if (x0 > x1) {
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		int dx = x1-x0;
		int dy = y1-y0;
		int derror2 = std::abs(dy)*2;
		int error2 = 0;
		int y = y0;
		for (int x = x0; x <= x1; x++) {
			if (steep) {
				this->pixels.push_back( Pixel(Point2i(y,x), color) );
			} else {
				this->pixels.push_back( Pixel(Point2i(x,y), color) );
			}
			error2 += derror2;

			if (error2 > dx) {
				y += (y1 > y0 ? 1 : -1);
				error2 -= dx*2;
			}
		}
	};

	/// @brief create circle pixels
	/// @param radius the radius of the circle
	/// @param color the RGBAColor of the circle
	/// @return void
	// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
	void createCircle(int radius, RGBAColor color) {
		int x = radius;
		int y = 0;
		int err = 0;

		while (x >= y) {
			this->pixels.push_back( Pixel(Point2i( x, y), color) );
			this->pixels.push_back( Pixel(Point2i( y, x), color) );
			this->pixels.push_back( Pixel(Point2i(-y, x), color) );
			this->pixels.push_back( Pixel(Point2i(-x, y), color) );
			this->pixels.push_back( Pixel(Point2i(-x, -y), color) );
			this->pixels.push_back( Pixel(Point2i(-y, -x), color) );
			this->pixels.push_back( Pixel(Point2i( y, -x), color) );
			this->pixels.push_back( Pixel(Point2i( x, -y), color) );

			if (err <= 0) {
				y += 1;
				err += 2*y + 1;
			}
			if (err > 0) {
				x -= 1;
				err -= 2*x + 1;
			}
		}
	}

	/// @brief rotate the pixelsprite
	/// @param a angle in radians
	/// @return rotated copy of original unrotated sprite
	PixelSprite rotated(float a) {
		PixelSprite copy;
		copy.position = this->position;
		size_t s = pixels.size();
		for (size_t i = 0; i < s; i++) {
			Vector2f v = Vector2f(pixels[i].position.x, pixels[i].position.y, 0);
			v.rotate(a);
			int x = nearbyint(v.x+0.1); // rounding up a bit works a little better
			int y = nearbyint(v.y+0.1);
			copy.pixels.push_back(Pixel(Point2i(x, y), pixels[i].color));
		}
		return copy;
	};
};

/// @brief The Canvas class is an Entity with a dynamic Texture. It fills the window.
class Canvas: public Entity
{
	public:
		/// @brief constructor
		Canvas();
		/// @brief overloaded constructor
		/// @param pixelsize defines how many screenpixels is 1 texturepixel
		Canvas(int pixelsize);
		/// @brief destructor
		virtual ~Canvas();

		/// @brief empty update function
		virtual void update(float deltaTime);
		/// @brief init the canvas
		/// @param pixelsize defines how many screenpixels is 1 texturepixel
		/// @return void
		void init(int pixelsize);
		/// @brief color a single pixel
		/// @param x position of pixel
		/// @param y position of pixel
		/// @param color of pixel
		/// @return void
		void setPixel(int x, int y, RGBAColor color);
		/// @brief get a single pixel color from canvas
		/// @param x position of pixel
		/// @param y position of pixel
		/// @return color of pixel on canvas
		RGBAColor getPixel(int x, int y);
		/// @brief clears a single pixel color to canvas background color
		/// @param x position of pixel
		/// @param y position of pixel
		/// @return void
		void clearPixel(int x, int y);
		/// @brief fill the canvas with a single color
		/// @param color to fill with
		/// @return void
		void fill(RGBAColor color);

		/// @brief get the width of the canvas
		/// @return _width of canvas
		int width() { return _width; };
		/// @brief get the height of the canvas
		/// @return _height of canvas
		int height() { return _height; };

		/// @brief draw a single pixelsprite on the canvas
		/// @param spr the PixelSprite to draw
		/// @return void
		void drawSprite(const PixelSprite& spr);
		/// @brief clear a single pixelsprite from the canvas
		/// @param spr the PixelSprite to clear to canvas backgroundcolor
		/// @return void
		void clearSprite(const PixelSprite& spr);

		/// @brief the backgroundcolor of the canvas
		RGBAColor backgroundcolor;

		/// @brief create line pixels from a Vector2
		/// @param from start position
		/// @param to end position
		/// @param color the RGBAColor of the line
		/// @return void
		void drawLine(Vector2f from, Vector2f to, RGBAColor color);

	private:
		/// @brief _framebuffer the internal pixelbuffer
		PixelBuffer* _framebuffer;

		/// @brief width of the canvas
		int _width;
		/// @brief height of the canvas
		int _height;
};

#endif /* CANVAS_H */
