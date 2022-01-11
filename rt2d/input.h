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

/// @brief KeyCode used by Input
enum class KeyCode
{
	Space = 32,
	Apostrophe = 39,
	Comma = 44,
	Minus = 45,
	Period = 46,
	Slash = 47,
	Alpha0 = 48,
	Alpha1 = 49,
	Alpha2 = 50,
	Alpha3 = 51,
	Alpha4 = 52,
	Alpha5 = 53,
	Alpha6 = 54,
	Alpha7 = 55,
	Alpha8 = 56,
	Alpha9 = 57,
	Semicolon = 59,
	Equal = 61,
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	LeftBracket = 91,
	Backslash = 92,
	RightBracket = 93,
	GraveAccent = 96,
	Escape = 256,
	Enter = 257,
	Tab = 258,
	Backspace = 259,
	Insert = 260,
	Delete = 261,
	Right = 262,
	Left = 263,
	Down = 264,
	Up = 265,
	PageUp = 266,
	PageDown = 267,
	Home = 268,
	End = 269,
	CapsLock = 280,
	ScrollLock = 281,
	NumLock = 282,
	PrintScreen = 283,
	Pause = 284,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,
	KeyPad0 = 320,
	KeyPad1 = 321,
	KeyPad2 = 322,
	KeyPad3 = 323,
	KeyPad4 = 324,
	KeyPad5 = 325,
	KeyPad6 = 326,
	KeyPad7 = 327,
	KeyPad8 = 328,
	KeyPad9 = 329,
	KeyPadDecimal = 330,
	KeyPadDivide = 331,
	KeyPadMultiply = 332,
	KeyPadSubtract = 333,
	KeyPadAdd = 334,
	KeyPadEnter = 335,
	KeyPadEqual = 336,
	LeftShift = 340,
	LeftControl = 341,
	LeftAlt = 342,
	LeftSuper = 343,
	RightShift = 344,
	RightControl = 345,
	RightAlt = 346,
	RightSuper = 347,
	Menu = 348
};

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
	bool getKey(KeyCode keyCode) { return _keys[(unsigned int)keyCode]; }
	/// @deprecated use KeyCode enum or char, not GLFW_KEY*
	/// @brief Is this key pressed?
	/// @param key as int
	/// @return bool key is pressed or not
	bool getKey(int key) { return getKey((KeyCode)key); }
	/// @brief Is this key pressed? Only check first press down
	/// @param key as char (ie: getKey('A') )
	/// @return bool key is pressed first time or not
	bool getKey(char key) { return getKey((KeyCode)key); }
	/// @brief Is this mouse button pressed?
	/// @param button num
	/// @return bool button is pressed or not
	bool getMouse(unsigned int button) { return _mouse[button]; }

	// down
	/// @brief Is this key pressed? Only check first press down
	/// @param keyCode as KeyCode (see defines)
	/// @return bool key is pressed first time or not
	bool getKeyDown(KeyCode keyCode) { return _keysDown[(unsigned int)keyCode]; }
	/// @deprecated use KeyCode enum or char, not GLFW_KEY*
	/// @brief Is this key pressed? Only check first press down
	/// @param key as int
	/// @return bool key is pressed first time or not
	bool getKeyDown(int key) { return getKeyDown((KeyCode)key); }
	/// @brief Is this key pressed? Only check first press down
	/// @param key as char (ie: getKeyDown('A') )
	/// @return bool key is pressed first time or not
	bool getKeyDown(char key) { return getKeyDown((KeyCode)key); }
	/// @brief Is this mouse button pressed? Only check first press down
	/// @param button num
	/// @return bool button is pressed or not
	bool getMouseDown(unsigned int button) { return _mouseDown[button]; }

	// up
	/// @brief Is this key released?
	/// @param keyCode as KeyCode (see defines)
	/// @return bool true or false
	bool getKeyUp(KeyCode keyCode) { return _keysUp[(unsigned int)keyCode]; }
	/// @deprecated use KeyCode enum or char, not GLFW_KEY*
	/// @brief Is this key released?
	/// @param key as int
	/// @return bool key is released or not
	bool getKeyUp(int key) { return getKeyUp((KeyCode)key); }
	/// @brief Is this key pressed? Only check first press down
	/// @param key as char (ie: getKeyUp('A') )
	/// @return bool key is pressed first time or not
	bool getKeyUp(char key) { return getKeyUp((KeyCode)key); }
	/// @brief Is this mouse button released?
	/// @param button num
	/// @return bool button is released or not
	bool getMouseUp(unsigned int button) { return _mouseUp[button]; }

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
	void _handleKey(unsigned int key); ///< @brief update internal array of keys
	void _handleMouse(unsigned int key); ///< @brief update internal array of keys

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
