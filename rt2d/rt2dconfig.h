/**
 * @file rt2dconfig.h
 *
 * @brief This header file defines some global vars.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>

#include <rt2d/color.h>


// screenwidth, screenheight
#define SWIDTH 1280 ///< The screen width
#define SHEIGHT 720 ///< The screen height

#define FULLSCREEN 0 ///< Fullscreen or not

#define WINDOWNAME "RT2D" ///< The window name

#define CLEARCOLOR_RED 0.1f ///< The red component of the color of the window
#define CLEARCOLOR_GREEN 0.1f ///< The green component of the color of the window
#define CLEARCOLOR_BLUE 0.1f ///< The blue component of the color of the window

// defaultshader for Renderer as fallback if Sprite has no shader defined
#define SPRITEVERTEXSHADER "shaders/sprite.vert" ///< vertexshader name
#define SPRITEFRAGMENTSHADER "shaders/sprite.frag" ///< fragmentshader name
#define AUTOGENWHITE "#autogen-white-TGA#" ///< auto generated Texture

#define VSYNC 0 ///< VSYNC on (1) or off (0)

#define DEFAULTFILTER 3 ///< texture filter
#define DEFAULTWRAP 1 ///< texture clamping (0=repeat, 1=mirror, 2=clamp)

#ifdef _WIN32
	//static std::string _prefix = "C:/Users/[you]/path/to/rt2d/demo/";
	static std::string _prefix = "";
#endif

#ifdef __APPLE__
	//static std::string _prefix = "/Users/[you]/path/to/rt2d/demo/";
	static std::string _prefix = "";
#endif

#ifdef __linux__
	//static std::string _prefix = "/home/[you]/path/to/rt2d/demo/";
	static std::string _prefix = "";
#endif


#endif /* CONFIG_H */


/**
 * @mainpage RT2D - 2D OpenGL Framework
 *
 * @section intro Introduction
 *
 * RT2D is a RealTime 2D framework, based on 'modern' OpenGL (2.1+). It runs on Mac, Linux and Windows.
 *
 * Please see `README.md` for instructions on compiling for your platform of choice.
 *
 * @section license License
 *
 * Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
