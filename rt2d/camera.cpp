/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <rt2d/rt2dconfig.h>
#include <rt2d/camera.h>

Camera::Camera()
{
	// to compensate for the camera being not in the correct position
	_offset = Point(SWIDTH/2, SHEIGHT/2, 0);

	// Initial position : on +Z
	// Unintuitively, this is the centre of the screen, so add _offset
	position = Point( 0, 0, 1 ) + _offset;

	_projectionMatrix = glm::ortho(0.0f, (float)SWIDTH, (float)SHEIGHT, 0.0f, 0.1f, 100.0f);
}

Camera::~Camera()
{

}

// called from Core::run(Scene* scene)
void Camera::updateCamera(float deltaTime)
{
	glm::vec3 up = glm::vec3(0, 1, 0); // +Y
	glm::vec3 direction = glm::vec3(0, 0, -1); // -Z

	glm::vec3 pos = glm::vec3(position.x, position.y, position.z);
	glm::vec3 offset = glm::vec3(_offset.x, _offset.y, _offset.z);

	// View matrix
	_viewMatrix = glm::lookAt(
			pos - offset, // Camera is at (xpos,ypos,1), in World Space
			pos - offset + direction, // and looks towards Z
			up  // Head is up
	);
}
