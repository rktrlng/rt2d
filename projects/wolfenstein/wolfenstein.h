#ifndef WOLFENSTEIN_H
#define WOLFENSTEIN_H

#include <rt2d/scene.h>
#include <rt2d/canvas.h>
#include <rt2d/color.h>

// see http://lodev.org/cgtutor/raycasting.html

struct World
{
	std::vector<char> _map;
	int mapWidth;
	int mapHeight;

	void init(char* data, int w, int h) {
		mapWidth = w;
		mapHeight = h;
		size_t size = w*h;
		for (size_t i = 0; i < size; i++) {
			this->_map.push_back( data[i] );
		}
	};

	char map(int x, int y) {
		int index = (this->mapWidth * y) + x;
		return _map[index];
	}
};

class Wolfenstein : public Scene
{
public:
	Wolfenstein();
	virtual ~Wolfenstein();

	virtual void update(float deltaTime);

private:
	void raycastAndDraw();
	void handleInput(float deltaTime);
	Canvas* canvas;
	World world;

	Point2d pos; // x and y start position
	Point2d dir; // initial direction vector
	Point2d plane; // the 2d raycaster version of camera plane
	float aspect; // the camera plane aspect ratio
};

#endif /* WOLFENSTEIN_H */
