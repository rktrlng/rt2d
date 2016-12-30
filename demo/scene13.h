/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#ifndef SCENE13_H
#define SCENE13_H

#include <vector>
#include <rt2d/stringutil.h>
#include <rt2d/timer.h>
#include <rt2d/vectorx.h>
#include "superscene.h"
#include "canvas.h"

struct SI_AnimatedSprite {
	Pointi position;
	Pointi velocity;
	std::vector<PixelSprite> frames;
	void addPixelSprite(PixelSprite ps) {
		frames.push_back(ps);
	}
};

class Scene13: public SuperScene
{
public:
	Scene13();
	virtual ~Scene13();

	virtual void update(float deltaTime);

private:
	int enemyupdate = 15; // 100fps/enemyupdate(20) = 5fps
	int bulletupdate = 4; // 100fps/bulletupdate(10) = 10fps
	int shootfrequency = 100; //random()%shootfrequency every enemy, every updateEnemies()

	std::vector<SI_AnimatedSprite> enemies;
	std::vector<SI_AnimatedSprite> enemy_bullets;
	std::vector<PixelSprite> player_bullets;
	std::vector<PixelSprite> defense_blocks;

	void setupEnemyGrid();
	bool enemiesChangeDirection();
	void setupDefenseGrid();
	void updateDefenseGrid();
	void setupPlayer();

	void updateEnemies();
	void updateEnemyBullets();
	void updatePlayerBullets();
	void updatePlayer();

	void setupEnemyA();
	void setupEnemyB();
	void setupEnemyC();
	void setupEnemyBullet();
	void setupPlayerBullet();
	void setupDefenseBlock();

	SI_AnimatedSprite si_enemy_a;
	SI_AnimatedSprite si_enemy_b;
	SI_AnimatedSprite si_enemy_c;
	SI_AnimatedSprite si_enemy_bullet;
	PixelSprite defense_block;
	PixelSprite player;
	PixelSprite player_bullet;

	int lowestX();
	int highestX();

	Pointi enemycenter;
	Canvas* canvas;
	Timer timer;
};

#endif /* SCENE13_H */
