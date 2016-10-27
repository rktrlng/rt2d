/**
 * @file camera.h
 *
 * @brief The Camera header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef CAMERA_H
#define CAMERA_H

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <rt2d/pointx.h>

/**
 * @brief The Camera class handles the concept of having a Camera in your Scene.
 */
class Camera
{
public:
	Camera(); ///< @brief Constructor of the Camera
	virtual ~Camera(); ///< @brief Destructor of the Camera

	Point position; ///< @brief The position of the Camera

	/// @brief updates the viewMatrix and projectionMatrix of the Camera.
	/// @param deltaTime The time that's passed since the last update.
	/// @return void
	virtual void updateCamera(float deltaTime);
	/// @brief get the viewMatrix of the Camera.
	/// @return glm::mat4 _viewMatrix
	glm::mat4 viewMatrix() { return _viewMatrix; };
	/// @brief get the projectionMatrix of the Camera.
	/// @return glm::mat4 _projectionMatrix
	glm::mat4 projectionMatrix() { return _projectionMatrix; };

private:
	glm::mat4 _viewMatrix; ///< @brief The viewMatrix of the Camera
	glm::mat4 _projectionMatrix; ///< @brief The (orthographic) projectionMatrix of the Camera

	Point _offset; ///< @brief The internal offset of the Camera. When Camera is in the middle of the screen, its position is (0,0).
};

#endif
