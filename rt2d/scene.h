/**
 * @file scene.h
 *
 * @brief The Scene header file.
 *
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#ifndef SCENE_H
#define SCENE_H

#include <rt2d/entity.h>
#include <rt2d/camera.h>

/// @brief The Scene class is the Base class for your own Scenes. It has a Camera and basic on/off state machine.
class Scene: public Entity
{
public:
	Scene(); ///< @brief Constructor of the Scene
	virtual ~Scene(); ///< @brief Destructor of the Scene

	/// @brief whether this Scene is running or not.
	/// @return bool _isRunning
	bool isRunning() { return _isRunning; };
	/// @brief start running the Scene
	/// @return void
	void start() { _isRunning = true; };
	/// @brief stop running the Scene
	/// @return void
	void stop() { _isRunning = false; };

	/// @brief get a pointer to the Camera
	/// @return Texture* a pointer to the Camera
	Camera* camera() { return _camera; };

	/// @brief update this Scene
	/// @param deltaTime the number of seconds since the last update
	/// @return void
	void updateScene(float deltaTime);

private:
	/// @brief Update an Entity
	/// @param entity the Entity to update
	/// @param deltaTime the number of seconds since the last update
	/// @return void
	void _updateEntity(Entity* entity, float deltaTime);

	Camera* _camera; ///< @brief the Camera instance

	bool _isRunning; ///< @brief running or not
};

#endif /* SCENE_H */
