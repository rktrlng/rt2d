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
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include <rt2d/vectorx.h>

/**
 * @brief The Camera class handles the concept of having a Camera in your Scene.
 */
class Camera
{
public:
	Camera(); ///< @brief Constructor of the Camera
	virtual ~Camera(); ///< @brief Destructor of the Camera

	Point3 position; ///< @brief The position of the Camera
	Point3 rotation; ///< @brief The rotation of the Camera

	/// @brief tilt the Camera (look up/down)
	/// @param amount the amount to tilt
	/// @return void
	void tilt(float amount)		{ rotation.x += amount; };
	/// @brief pan the Camera (look left/right)
	/// @param amount the amount to pan
	/// @return void
	void pan(float amount)		{ rotation.y += amount; };
	/// @brief roll the Camera (around Z)
	/// @param amount the amount to roll in radians
	/// @return void
	void roll(float amount)		{ rotation.z += amount; };
	/// @brief dolly the Camera (walk forward/backward)
	/// @param amount the amount to dolly
	/// @return void
	void dolly(float amount)	{ position += (Point3(_direction.x, _direction.y, _direction.z) * amount); };
	/// @brief track the Camera (walk sideways / strafe)
	/// @param amount the amount to track
	/// @return void
	void track(float amount)	{ position += (Point3(_right.x, _right.y, _right.z) * amount); };
	/// @brief boom the Camera (walk up/down)
	/// @param amount the amount to boom
	/// @return void
	void boom(float amount)		{ position += (Point3(_up.x, _up.y, _up.z) * amount); };

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

	/// @brief set the projectionMatrix in 'perspective mode'.
	/// @return void
	void perspective();
	/// @brief set the projectionMatrix in 'orthogonal mode'.
	/// @return void
	void orthogonal();

private:
	glm::mat4 _viewMatrix; ///< @brief The viewMatrix of the Camera
	glm::mat4 _projectionMatrix; ///< @brief The (orthographic) projectionMatrix of the Camera

	Point3 _offset; ///< @brief The internal offset of the Camera. When Camera is in the middle of the screen, its position is (0,0,0).

	glm::vec3 _up; ///< @brief The up vector of the Camera.
	glm::vec3 _right; ///< @brief The right vector of the Camera.
	glm::vec3 _direction; ///< @brief The vector where the Camera is looking.
};

#endif
