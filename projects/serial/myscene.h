#ifndef MYSCENE_H
#define MYSCENE_H

#include <deque>

#include <rt2d/scene.h>
#include <rt2d/canvas.h>
#include <rt2d/text.h>
#include <rt2d/util.h>
#include <rs232/rs232.h>

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	Timer t;
	Canvas* canvas;
	Text* text;

	std::deque<int> history;
	void clearHistory();
	void drawHistory();

	std::vector<int> transceive(unsigned char c);
	int connected;
	int CPORT_NR;
	int BDRATE;
};

#endif /* MYSCENE_H */
