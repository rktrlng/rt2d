/**
 * This file is part of RT2D, a 2D OpenGL framework.
 * 
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 * - Copyright [year] [your name] <you@yourhost.com>
 *   - [description]
 */

#include <iostream>
#include <rt2d/input.h>

Input::Input()
{
	_window = NULL;
	
	int i;
	for(i=0; i<NUMKEYS;i++) {
		_keys[i] = false;
		_keysUp[i] = false;
		_keysDown[i] = false;
	}
}

Input::~Input()
{
	
}

void Input::updateInput(GLFWwindow* w)
{
	_window = w;
	
	glfwPollEvents();

	// 32-97 = ' ' to '`'
	int i;
	for(i=32; i<97;i++) {
		_handleKey(i);
	}
	// Func + arrows + esc, etc
	for(i=255; i<326;i++) {
		_handleKey(i);
	}

	glfwGetCursorPos(_window, &_mouseX, &_mouseY);
}

void Input::_handleKey(int key)
{ 
	if (glfwGetKey( _window, key ) == GLFW_PRESS) {
		if (_keys[key] == false) { // if first time pressed down
			_keys[key] = true;
			_keysDown[key] = true;
			//std::cout << "DOWN: " << key << std::endl;
		} else {
			// not the first time this is pressed
			// keys[key] is still true;
			_keysDown[key] = false;
		}
	}
	if (glfwGetKey( _window, key ) == GLFW_RELEASE) {
		if (_keys[key] == true) { // still pressed
			_keys[key] = false;
			_keysUp[key] = true;
			//std::cout << "UP: " << key << std::endl;
		} else {
			_keysUp[key] = false;
		}
	}
}
