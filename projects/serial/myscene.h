#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include <rt2d/text.h>
#include <rs232/rs232.h>

class MyScene : public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltaTime);

private:
	Timer t;
	Text* text;

	std::vector<int> transceive(unsigned char c);
	int connected;
	int CPORT_NR;
	int BDRATE;
};

#endif /* MYSCENE_H */
