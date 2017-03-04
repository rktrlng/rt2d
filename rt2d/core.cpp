/**
 * This file is part of RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *   - Initial commit
 */

#include <rt2d/core.h>

Core::Core()
{
	_deltaTime = 0;
}

Core::~Core()
{

}

void Core::run(Scene* scene)
{
	// update our _deltaTime
	_calculateDeltaTime();

	// Update Input singleton instance
	Singleton<Input>::instance()->updateInput(_renderer.window());

	// Update camera instance in Scene
	scene->camera()->updateCamera((float)_deltaTime);

	// Update Scene (and recursively all children)
	scene->updateScene((float)_deltaTime);

	// Render Scene
	_renderer.renderScene(scene);

	// user clicked the 'close' button in the window
	if (glfwWindowShouldClose(_renderer.window()) == 1) { scene->stop(); }
}

void Core::showFrameRate(float numsecs)
{
	static int frames = 0;
	static double time = 0;

	frames++;
	time += _deltaTime;
	if (time >= numsecs) {
		printf("%f ms/frame (%f FPS)\n", (numsecs*1000)/double(frames), frames/numsecs);
		frames = 0;
		time = 0;
	}
}

double Core::_calculateDeltaTime()
{
	static double lastTime = glfwGetTime();
	double startTime = glfwGetTime();
	_deltaTime = startTime - lastTime;
	lastTime = startTime;

	return _deltaTime;
}

void Core::cleanup()
{
	_renderer.cleanup();
}
