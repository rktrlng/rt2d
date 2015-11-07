/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2015 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 * - Copyright 2015 Your Name <you@yourhost.com>
 *     - What you did
 */

#ifndef SCENE00_H
#define SCENE00_H

#include <deque>
#include <rt2d/timer.h>
#include "superscene.h"
#include "basicentity.h"

class Scene00: public SuperScene
{
	public:
		Scene00();
		virtual ~Scene00();

		virtual void update(float deltaTime);

	private:
		BasicEntity* consolecontainer;
		std::vector<Text*> consoletext;
		std::deque<std::string> fulltext;
		unsigned int numlines;
		Timer t;

		void filltext();
};

#endif /* SCENE00_H */
