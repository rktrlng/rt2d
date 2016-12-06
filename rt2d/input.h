/**
 * @file input.h
 *
 * @brief The Input header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 *   - <meruiden> scaling of window
 */

#ifndef INPUT_H
#define INPUT_H

// Include GLFW
#include <glfw3.h>

#include <config.h>

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

/*
#define 	GLFW_MOUSE_BUTTON_1   0
#define 	GLFW_MOUSE_BUTTON_2   1
#define 	GLFW_MOUSE_BUTTON_3   2
#define 	GLFW_MOUSE_BUTTON_4   3
#define 	GLFW_MOUSE_BUTTON_5   4
#define 	GLFW_MOUSE_BUTTON_6   5
#define 	GLFW_MOUSE_BUTTON_7   6
#define 	GLFW_MOUSE_BUTTON_8   7
#define 	GLFW_MOUSE_BUTTON_LAST   GLFW_MOUSE_BUTTON_8
#define 	GLFW_MOUSE_BUTTON_LEFT   GLFW_MOUSE_BUTTON_1
#define 	GLFW_MOUSE_BUTTON_RIGHT   GLFW_MOUSE_BUTTON_2
#define 	GLFW_MOUSE_BUTTON_MIDDLE   GLFW_MOUSE_BUTTON_3
*/

/// @brief The Input class handles Keyboard and Mouse.
class Input
{
public:
	Input(); ///< @brief Constructor of the Input
	virtual ~Input(); ///< @brief Destructor of the Input

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
	/// @brief Is this mouse button pressed?
	/// @param button num
	/// @return bool button is pressed or not
	bool getMouse(int button) { return _mouse[button]; }

	// down
	/// @brief Is this key pressed? Only check first press down
	/// @param key as int (see defines)
	/// @return bool key is pressed first time or not
	bool getKeyDown(int key) { return _keysDown[key]; }
	/// @brief Is this key pressed? Only check first press down
	/// @param key as char (ie 'a')
	/// @return bool key is pressed first time or not
	bool getKeyDown(char key) { return getKeyDown((int) key); }
	/// @brief Is this mouse button pressed? Only check first press down
	/// @param button num
	/// @return bool button is pressed or not
	bool getMouseDown(int button) { return _mouseDown[button]; }

	// up
	/// @brief Is this key released?
	/// @param key as int (see defines)
	/// @return bool true or false
	bool getKeyUp(int key) { return _keysUp[key]; }
	/// @brief Is this key released?
	/// @param key as char (ie 'a')
	/// @return bool key is released or not
	bool getKeyUp(char key) { return getKeyUp((int) key); }
	/// @brief Is this mouse button released?
	/// @param button num
	/// @return bool button is released or not
	bool getMouseUp(int button) { return _mouseUp[button]; }

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

	// window size
	/// @brief get width of the window
	/// @return _windowWidth as int
	int getWindowWidth() { return _windowWidth; }
	/// @brief get height of the window
	/// @return _windowHeight as int
	int getWindowHeight() { return _windowHeight; }

private:
	GLFWwindow* _window; ///< @brief GLFWwindow* _window
	void _handleKey(int key); ///< @brief update internal array of keys
	void _handleMouse(int key); ///< @brief update internal array of keys

	bool _keys[GLFW_KEY_LAST]; ///< @brief internal array of pressed keys
	bool _keysUp[GLFW_KEY_LAST]; ///< @brief internal array of released keys
	bool _keysDown[GLFW_KEY_LAST]; ///< @brief internal array of keys pressed the first time

	bool _mouse[GLFW_MOUSE_BUTTON_LAST]; ///< @brief internal array of pressed mouse buttons
	bool _mouseUp[GLFW_MOUSE_BUTTON_LAST]; ///< @brief internal array of released mouse buttons
	bool _mouseDown[GLFW_MOUSE_BUTTON_LAST]; ///< @brief internal array of mouse buttons pressed the first time

	double _mouseX; ///< @brief X position of the Mouse
	double _mouseY; ///< @brief Y position of the Mouse

	int _windowWidth; ///< @brief Width of the window
	int _windowHeight; ///< @brief Height of the window
};

#endif /* INPUT_H */
