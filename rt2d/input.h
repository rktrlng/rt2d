/**
 * @file input.h
 * 
 * @brief The Input header file.
 * 
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#ifndef INPUT_H
#define INPUT_H

// Include GLFW
#include <glfw3.h>

#define NUMKEYS GLFW_KEY_LAST ///< @brief Number of possible keys (GLFW_KEY_LAST = 348) */

/*
#define 	GLFW_KEY_UNKNOWN   -1
#define 	GLFW_KEY_SPACE   32
#define 	GLFW_KEY_APOSTROPHE   39 // '
#define 	GLFW_KEY_COMMA   44 // ,
#define 	GLFW_KEY_MINUS   45 // -
#define 	GLFW_KEY_PERIOD   46 // .
#define 	GLFW_KEY_SLASH   47 // /
#define 	GLFW_KEY_0   48
...
#define 	GLFW_KEY_9   57
#define 	GLFW_KEY_SEMICOLON   59 // ;
#define 	GLFW_KEY_EQUAL   61 // =
#define 	GLFW_KEY_A   65
#define 	GLFW_KEY_B   66
#define 	GLFW_KEY_C   67
...
#define 	GLFW_KEY_Z   90
#define 	GLFW_KEY_LEFT_BRACKET   91 // [
#define 	GLFW_KEY_BACKSLASH   92 // \
#define 	GLFW_KEY_RIGHT_BRACKET   93 // ]
#define 	GLFW_KEY_GRAVE_ACCENT   96 // `
#define 	GLFW_KEY_WORLD_1   161 // non-US #1
#define 	GLFW_KEY_WORLD_2   162 // non-US #2
#define 	GLFW_KEY_ESCAPE   256
#define 	GLFW_KEY_ENTER   257
#define 	GLFW_KEY_TAB   258
#define 	GLFW_KEY_BACKSPACE   259
#define 	GLFW_KEY_INSERT   260
#define 	GLFW_KEY_DELETE   261
#define 	GLFW_KEY_RIGHT   262
#define 	GLFW_KEY_LEFT   263
#define 	GLFW_KEY_DOWN   264
#define 	GLFW_KEY_UP   265
#define 	GLFW_KEY_PAGE_UP   266
#define 	GLFW_KEY_PAGE_DOWN   267
#define 	GLFW_KEY_HOME   268
#define 	GLFW_KEY_END   269
#define 	GLFW_KEY_CAPS_LOCK   280
#define 	GLFW_KEY_SCROLL_LOCK   281
#define 	GLFW_KEY_NUM_LOCK   282
#define 	GLFW_KEY_PRINT_SCREEN   283
#define 	GLFW_KEY_PAUSE   284
#define 	GLFW_KEY_F1   290
...
#define 	GLFW_KEY_F25   314
#define 	GLFW_KEY_KP_0   320
...
#define 	GLFW_KEY_KP_9   329
#define 	GLFW_KEY_KP_DECIMAL   330
#define 	GLFW_KEY_KP_DIVIDE   331
#define 	GLFW_KEY_KP_MULTIPLY   332
#define 	GLFW_KEY_KP_SUBTRACT   333
#define 	GLFW_KEY_KP_ADD   334
#define 	GLFW_KEY_KP_ENTER   335
#define 	GLFW_KEY_KP_EQUAL   336
#define 	GLFW_KEY_LEFT_SHIFT   340
#define 	GLFW_KEY_LEFT_CONTROL   341
#define 	GLFW_KEY_LEFT_ALT   342
#define 	GLFW_KEY_LEFT_SUPER   343
#define 	GLFW_KEY_RIGHT_SHIFT   344
#define 	GLFW_KEY_RIGHT_CONTROL   345
#define 	GLFW_KEY_RIGHT_ALT   346
#define 	GLFW_KEY_RIGHT_SUPER   347
#define 	GLFW_KEY_MENU   348
#define 	GLFW_KEY_LAST   GLFW_KEY_MENU
*/

/// @brief The Input class handles Keyboard and Mouse.
class Input
{
	public:
		Input();			///< @brief Constructor of the Input
		virtual ~Input();	///< @brief Destructor of the Input

		/// @brief updates the input from Keyboard and Mouse.
		/// @param[in] w GLFWwindow*
		void updateInput(GLFWwindow* w);

		// keys while down
		/// @brief Is this key pressed?
		/// @param key as int (see defines)
		/// @return bool key is pressed or not
		bool getKey(int key) { return _keys[key]; }
		/// @brief Is this key pressed?
		/// @param key as char (ie 'a')
		/// @return bool key is pressed or not
		bool getKey(char key) { return getKey((int) key); }
		
		// down
		/// @brief Is this key pressed? Only check first press down
		/// @param key as int (see defines)
		/// @return bool key is pressed first time or not
		bool getKeyDown(int key) { return _keysDown[key]; }
		/// @brief Is this key pressed? Only check first press down
		/// @param key as char (ie 'a')
		/// @return bool key is pressed first time or not
		bool getKeyDown(char key) { return getKeyDown((int) key); }
		
		// up
		/// @brief Is this key released?
		/// @param key as int (see defines)
		/// @return bool true or false
		bool getKeyUp(int key) { return _keysUp[key]; }
		/// @brief Is this key released?
		/// @param key as char (ie 'a')
		/// @return bool key is released or not
		bool getKeyUp(char key) { return getKeyUp((int) key); }

		// mouse
		/// @brief get X position of the Mouse
		/// @return _mouseX as double
		double getMouseX() { return _mouseX; }
		/// @brief get Y position of the Mouse
		/// @return _mouseY as double
		double getMouseY() { return _mouseY; }
		/// @brief Set Mouse cursor to a certain position
		/// @param[in] x The X position
		/// @param[in] y The Y position
		/// @return void
		void setMouse(double x, double y) { glfwSetCursorPos(_window, x, y); };

	private:
		GLFWwindow* _window;		///< @brief GLFWwindow* _window
		void _handleKey(int key);	///< @brief update internal array of keys

		bool _keys[NUMKEYS];		///< @brief internal array of pressed keys
		bool _keysUp[NUMKEYS];		///< @brief internal array of released keys
		bool _keysDown[NUMKEYS];	///< @brief internal array of keys pressed the first time

		double _mouseX;		///< @brief X position of the Mouse
		double _mouseY;		///< @brief Y position of the Mouse
};

#endif /* INPUT_H */ 
