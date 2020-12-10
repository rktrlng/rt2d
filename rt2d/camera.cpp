/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifdef __APPLE__
/* glEnable first deprecated in MacOS 10.14 */
#define GL_SILENCE_DEPRECATION
#endif

#include <rt2d/rt2dconfig.h>
#include <rt2d/camera.h>

Camera::Camera()
{
	position = Point3( 0, 0, 650 );
	rotation = Point3( 0, PI, 0 );

	_direction = glm::vec3(0, 0, -5);
	_up = glm::vec3(0, 1, 0);
	_right = glm::vec3(1, 0, 0);

	this->orthogonal();
}

Camera::~Camera()
{

}

void Camera::perspective()
{
	// offset is 0,0,0 because in 3D we want 0,0,0 in the middle of the screen
	_offset = Point3(0, 0, 0);
	position = Point3( 0, 0, 650 ) + _offset;

	// FoV, aspectratio, nearclip, farclip
	_projectionMatrix = glm::perspective(45.0f, (float)SWIDTH/(float)SHEIGHT, 0.1f, 10000.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

void Camera::orthogonal()
{
	// to compensate for the camera being not in the correct position
	_offset = Point3(SWIDTH/2, SHEIGHT/2, 0);

	// Initial position : on +Z
	// Unintuitively, this is the centre of the screen, so add _offset
	position = Point3( 0, 0, 650 ) + _offset;

	_projectionMatrix = glm::ortho(0.0f, (float)SWIDTH, (float)SHEIGHT, 0.0f, 0.1f, 1000.0f);

	// Disable depth test (we don't need it in 2D)
	glDisable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

// called from Core::run(Scene* scene)
void Camera::updateCamera(float deltaTime)
{
	// Direction vector: Spherical coordinates to Cartesian coordinates conversion
	_direction = glm::vec3(
		cos(rotation.x) * sin(rotation.y),
		sin(rotation.x),
		cos(rotation.x) * cos(rotation.y)
	);
	//_direction = glm::vec3(0, 0, -5);

	// Right vector
	_right = glm::vec3(
		sin(rotation.y - HALF_PI),
		0,
		cos(rotation.y - HALF_PI)
	);
	_right = glm::rotateZ(_right, rotation.z*(float)RAD_TO_DEG); // rotateZ() in Degrees
	//_right = glm::vec3(1, 0, 0);

	// Up vector
	_up = glm::cross( _right, _direction );
	//_up = glm::vec3(0, 1, 0);

	glm::vec3 pos = glm::vec3(position.x, position.y, position.z);
	glm::vec3 offset = glm::vec3(_offset.x, _offset.y, _offset.z);

	// View matrix
	_viewMatrix = glm::lookAt(
			pos - offset, // Camera is at (xpos,ypos,1), in World Space
			pos - offset + _direction, // and looks towards Z
			_up  // Head is up
	);
}
