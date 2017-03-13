/**
 * This class describes Wolfenstein behavior.
 *
 * Copyright 2017 Rik Teerling <rik@onandoffables.com>
 *
 * @see http://lodev.org/cgtutor/raycasting.html
 */

#include <fstream>
#include <sstream>

#include "wolfenstein.h"

Wolfenstein::Wolfenstein() : Scene()
{
	// create Canvas
	canvas = new Canvas(2); // pixelsize
	this->addChild(canvas);

	aspect = 0.85f;
	pos = Point2d(22, 12); // x and y start position
	dir = Point2d(-1, 0); // initial direction vector
	plane = Point2d(0.0, aspect); // the 2d raycaster version of camera plane

	char level[576] = { // 24 * 24
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
		1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1,
		1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0,5,0,0,0,1,
		1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,5,0,0,0,5,0,0,0,1,
		1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,5,0,5,0,5,0,0,0,1,
		1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};
	world.init(level, 24, 24);
}


Wolfenstein::~Wolfenstein()
{
	this->removeChild(canvas);
	delete canvas;

}

void Wolfenstein::update(float deltaTime)
{
	// Escape key stops the Scene
	if (input()->getKeyUp(KeyCode::Escape)) {
		this->stop();
	}

	// draw world
	this->raycastAndDraw();

	// handle Input: Up Down Left Right / QWEASD
	this->handleInput(deltaTime);
}

void Wolfenstein::raycastAndDraw()
{
	// Raycast every x. Draw vertical line. Height depending on distance
	for(int x = 0; x < canvas->width(); x++) {
		//calculate ray position and direction
		double cameraX = 2 * x / double(canvas->width()) - 1; //x-coordinate in camera space
		double rayPosX = pos.x;
		double rayPosY = pos.y;
		double rayDirX = dir.x + plane.x * cameraX;
		double rayDirY = dir.y + plane.y * cameraX;
		//which box of the map we're in
		int mapX = int(rayPosX);
		int mapY = int(rayPosY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0) {
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (world.map(mapX, mapY) > 0) { hit = 1; }
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0) {
			perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
		} else {
			perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
		}

		//Calculate height of line to draw on screen
		int lineHeight = (int)(canvas->height() / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + canvas->height() / 2;
		if(drawStart < 0) { drawStart = 0; };
		int drawEnd = lineHeight / 2 + canvas->height() / 2;
		if(drawEnd >= canvas->height()) { drawEnd = canvas->height() - 1; }

		//choose wall color
		RGBAColor color = WHITE;
		switch( world.map(mapX, mapY) ) {
			case 1:	color = RED; break;
			case 2:	color = GREEN; break;
			case 3:	color = BLUE; break;
			case 4:	color = CYAN; break;
			case 5:	color = YELLOW; break;
			case 6:	color = MAGENTA; break;
			default: color = WHITE; break;
		}

		// Shading. Walls far away are darker.
		float tintfactor = lineHeight / 25.0f; // higher magic number = darker sooner
		if (tintfactor <= 1) { tintfactor = 1; } // clamp colors to 0
		color.r -= color.r / tintfactor;
		color.g -= color.g / tintfactor;
		color.b -= color.b / tintfactor;
		//give x and y sides different brightness
		if (side == 1) {
			color.r /= 2;
			color.g /= 2;
			color.b /= 2;
		}

		//draw pixels of y (vertical line) for this x. Bottom to top.
		int ceiltint = 64;
		int floortint = 96;
		for (int y = 0; y < canvas->height(); y++) {
			if (y < drawStart) { // floor
				canvas->setPixel(x, y, RGBAColor(floortint-y/2, floortint-y/2, floortint-y/2, 255));
			} else if (y >= drawStart && y < drawEnd) { // wall
				canvas->setPixel(x, y, color);
			} else { // ceiling
				canvas->setPixel(x, y, RGBAColor(y/2-ceiltint, y/2-ceiltint, y/2-ceiltint, 255));
			}
		}
	} // end for x loop
}

void Wolfenstein::handleInput(float deltaTime)
{
	//speed modifiers
	double moveSpeed = deltaTime * 5.0; //the constant value is in squares/second
	double rotSpeed = deltaTime * 1.5; //the constant value is in radians/second

	//move forward if no wall in front of you
	if ( input()->getKey(KeyCode::W) || input()->getKey(KeyCode::Up) ) {
		if(world.map(int(pos.x + dir.x * moveSpeed), int(pos.y)) == 0) { pos.x += dir.x * moveSpeed; }
		if(world.map(int(pos.x), int(pos.y + dir.y * moveSpeed)) == 0) { pos.y += dir.y * moveSpeed; }
	}
	//move backwards if no wall behind you
	if ( input()->getKey(KeyCode::S) || input()->getKey(KeyCode::Down) ) {
		if(world.map(int(pos.x - dir.x * moveSpeed), int(pos.y)) == 0) { pos.x -= dir.x * moveSpeed; }
		if(world.map(int(pos.x), int(pos.y - dir.y * moveSpeed)) == 0) { pos.y -= dir.y * moveSpeed; }
	}
	//Strafe right (this can get you stuck, just rotate and walk forwards or backwards)
	if ( input()->getKey(KeyCode::D) ) {
		if(world.map(int(pos.x + plane.x * moveSpeed), int(pos.y)) == 0) { pos.x += plane.x * moveSpeed; }
		if(world.map(int(pos.x), int(pos.y + plane.y * moveSpeed)) == 0) { pos.y += plane.y * moveSpeed; }
	}
	//Strafe left (this can get you stuck, just rotate and walk forwards or backwards)
	if ( input()->getKey(KeyCode::A) ) {
		if(world.map(int(pos.x + plane.x * moveSpeed), int(pos.y)) == 0) { pos.x -= plane.x * moveSpeed; }
		if(world.map(int(pos.x), int(pos.y + plane.y * moveSpeed)) == 0) { pos.y -= plane.y * moveSpeed; }
	}
	//rotate to the right
	if ( input()->getKey(KeyCode::E) || input()->getKey(KeyCode::Right) ) {
		//both camera direction and camera plane must be rotated
		double oldDirX = dir.x;
		dir.x = dir.x * cos(-rotSpeed) - dir.y * sin(-rotSpeed);
		dir.y = oldDirX * sin(-rotSpeed) + dir.y * cos(-rotSpeed);
		double oldPlaneX = plane.x;
		plane.x = plane.x * cos(-rotSpeed) - plane.y * sin(-rotSpeed);
		plane.y = oldPlaneX * sin(-rotSpeed) + plane.y * cos(-rotSpeed);
	}
	//rotate to the left
	if ( input()->getKey(KeyCode::Q) || input()->getKey(KeyCode::Left) ) {
		//both camera direction and camera plane must be rotated
		double oldDirX = dir.x;
		dir.x = dir.x * cos(rotSpeed) - dir.y * sin(rotSpeed);
		dir.y = oldDirX * sin(rotSpeed) + dir.y * cos(rotSpeed);
		double oldPlaneX = plane.x;
		plane.x = plane.x * cos(rotSpeed) - plane.y * sin(rotSpeed);
		plane.y = oldPlaneX * sin(rotSpeed) + plane.y * cos(rotSpeed);
	}
}
