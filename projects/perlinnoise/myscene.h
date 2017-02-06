#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <rt2d/text.h>
#include <rt2d/noise.h>
#include <rt2d/util.h>

class BasicEntity: public Entity
{
public:
	BasicEntity(): Entity() { };
	virtual ~BasicEntity() { };

	virtual void update(float deltaTime) { };
};

#define deepwater RGBAColor(5, 0, 130)
#define midwater RGBAColor(65, 60, 175)
#define shallowwater RGBAColor(127, 127, 215)
#define sand RGBAColor(215, 200, 115)
#define darksand RGBAColor(124, 100, 64)
#define grass RGBAColor(100, 185, 90)
#define woods RGBAColor(64, 127, 64)
#define darkwoods RGBAColor(32, 96, 32)
#define highland RGBAColor(85, 85, 50)
#define rock RGBAColor(100, 100, 100)
#define snow RGBAColor(224, 224, 224)

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	Timer t;
	BasicEntity* entity;
	Text* text;

	PerlinNoise* pn;

	bool contrast;
	bool posterize;
	bool colorize;
};

#endif /* MYSCENE_H */
