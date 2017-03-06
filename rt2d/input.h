/**
 * @file input.h
 *
 * @brief The Input header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 *   - [meruiden] scaling of window
 */

#ifndef INPUT_H
#define INPUT_H

// Include GLFW
#include <glfw3.h>

#include <rt2dconfig.h>
#include <rt2d/keycode.h>
#include <rt2d/singleton.h>

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
	/// @param keyCode as KeyCode
	/// @return bool key is pressed or not
	bool getKey(KeyCode keyCode) { return _keys[keyCode]; }
	/// @brief Is this key pressed?
	/// @param key as int
	/// @return bool key is pressed or not
	bool getKey(int key) { return getKey((KeyCode) key); }
	/// @brief Is this mouse button pressed?
	/// @param button num
	/// @return bool button is pressed or not
	bool getMouse(int button) { return _mouse[button]; }

	// down
	/// @brief Is this key pressed? Only check first press down
	/// @param keyCode as KeyCode (see defines)
	/// @return bool key is pressed first time or not
	bool getKeyDown(KeyCode keyCode) { return _keysDown[keyCode]; }
	/// @brief Is this key pressed? Only check first press down
	/// @param key as int
	/// @return bool key is pressed first time or not
	bool getKeyDown(int key) { return getKeyDown((KeyCode) key); }
	/// @brief Is this mouse button pressed? Only check first press down
	/// @param button num
	/// @return bool button is pressed or not
	bool getMouseDown(int button) { return _mouseDown[button]; }

	// up
	/// @brief Is this key released?
	/// @param keyCode as KeyCode (see defines)
	/// @return bool true or false
	bool getKeyUp(KeyCode keyCode) { return _keysUp[keyCode]; }
	/// @brief Is this key released?
	/// @param key as int
	/// @return bool key is released or not
	bool getKeyUp(int key) { return getKeyUp((KeyCode) key); }
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
