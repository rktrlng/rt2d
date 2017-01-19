#ifndef MYSCENE_H
#define MYSCENE_H

#include "audio/audio.h"
#include "audio/sound.h"

#include <rt2d/scene.h>
#include <rt2d/text.h>

#include "myentity.h"

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	MyEntity* square;
	std::vector<Sound*> sounds;
	std::vector<Text*> text;

	void loadSounds();
};

#endif /* SCENE00_H */
