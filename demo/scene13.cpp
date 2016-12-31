/**
 * This file is part of a demo that shows how to use RT2D, a 2D OpenGL framework.
 *
 * - Copyright 2016 Rik Teerling <rik@onandoffables.com>
 *     - Initial commit
 */

#include <time.h>
#include "scene13.h"

Scene13::Scene13() : SuperScene()
{
	srand((unsigned)time(NULL));

	text[0]->message("Scene13: Space Invaders");

	timer.start();
	shoottimer.start();

	// create Canvas
	canvas = new Canvas(4); // pixelsize
	layers[0]->addChild(canvas);

	setupEnemyA();
	setupEnemyB();
	setupEnemyC();
	setupEnemyBullet();

	enemycenter = Pointi(canvas->width()/2, canvas->height()/2);
	setupEnemyGrid();

	setupDefenseBlock();
	setupDefenseGrid();

	setupPlayer();
	setupPlayerBullet();
}


Scene13::~Scene13()
{
	layers[0]->removeChild(canvas);
	delete canvas;
}

void Scene13::update(float deltaTime)
{
	// ###############################################################
	// Make SuperScene do what it needs to do (Escape key stops Scene)
	// ###############################################################
	SuperScene::update(deltaTime);

	//text[0]->message(""); // clear title
	//text[1]->message(""); // clear fps message
	text[2]->message(""); // clear [/] next scene
	text[3]->message(""); // clear <esc> to quit
	text[10]->message(""); // clear player click count message

	// player wants to shoot
	if (input()->getKeyDown( GLFW_KEY_SPACE )) {
		if (shoottimer.seconds() > 0.8f) {
			PixelSprite b = player_bullet; // copy sprites etc
			b.position = player.position + Pointi(0,2);
			player_bullets.push_back(b);
			shoottimer.start();
		}
	}
	// ###############################################################
	// Update and draw only when it's time
	// ###############################################################
	float tsec = timer.seconds();
	if (tsec > 0.01 - deltaTime) { // 0.01 is 100 fps
		static int counter=0;

		// enemy bullets
		if (counter%bulletupdate == 0) {
			updateEnemyBullets();
		}

		// player bullets
		if (counter%bulletupdate/2 == 0) {
			updatePlayerBullets();
		}

		// enemies
		if (counter%enemyupdate == 0) {
			updateEnemies();
		}

		updateDefenseGrid();
		updatePlayer();

		// restart frametimer
		counter++;
		timer.start();
	}
}

void Scene13::updateEnemies()
{
	static Pointi velocity = Pointi(1,0);
	static int counter = 0;
	size_t s = enemies.size();
	if (enemiesChangeDirection()) {
		velocity.x *= -1;
		enemycenter.y -= 1;
	}
	enemycenter += velocity;
	for (size_t i = 0; i < s; i++) {
		canvas->clearSprite(enemies[i].frames[0]);
		canvas->clearSprite(enemies[i].frames[1]);
		enemies[i].frames[0].position = enemycenter + enemies[i].position;
		enemies[i].frames[1].position = enemycenter + enemies[i].position;

		// do enemies shoot?
		if (random()%shootfrequency == 1) {
			SI_AnimatedSprite b = si_enemy_bullet; // copy sprites etc
			b.position = enemies[i].frames[0].position + Pointi(0,-2);
			b.velocity = Pointi(0,-1);
			enemy_bullets.push_back(b);
		}

		// draw
		if (counter%8 < 4) {
		//if (counter%2 == 0) {
			canvas->drawSprite(enemies[i].frames[0]);
		} else {
			canvas->drawSprite(enemies[i].frames[1]);
		}
	}
	counter++;
}

void Scene13::updatePlayer()
{
	canvas->clearSprite(player);
	if (input()->getKey( GLFW_KEY_LEFT )) {
		player.position.x -= 1;
	}
	if (input()->getKey( GLFW_KEY_RIGHT )) {
		player.position.x += 1;
	}
	canvas->drawSprite(player);
}

int Scene13::lowestX()
{
	int low = enemies[0].frames[0].position.x;
	size_t s = enemies.size();
	for (size_t i = 0; i < s; i++) {
		if (enemies[i].frames[0].position.x < low) {
			low = enemies[i].frames[0].position.x;
		}
	}
	return low;
}

int Scene13::highestX()
{
	int high = enemies[0].frames[0].position.x;
	size_t s = enemies.size();
	for (size_t i = 0; i < s; i++) {
		if (enemies[i].frames[0].position.x > high) {
			high = enemies[i].frames[0].position.x;
		}
	}
	return high;
}

bool Scene13::enemiesChangeDirection()
{
	if ( highestX() >= (canvas->width()/16)*15 ) {
		return true;
	}
	if ( lowestX() <= canvas->width()/16 ) {
		return true;
	}
	return false;
}

void Scene13::updateEnemyBullets()
{
	static int counter = 0;

	// defense blocks
	int defensewidth = 32;
	int defenseheight = 16;

	std::vector<SI_AnimatedSprite>::iterator it = enemy_bullets.begin();
	while (it != enemy_bullets.end()) {
		int todelete = 0;

		// clear, update, draw
		canvas->clearSprite((*it).frames[0]);
		canvas->clearSprite((*it).frames[1]);
		(*it).position += (*it).velocity;
		(*it).frames[0].position = (*it).position;
		(*it).frames[1].position = (*it).position;

		if (counter%2 == 0) {
			canvas->drawSprite((*it).frames[0]);
		} else {
			canvas->drawSprite((*it).frames[1]);
		}

		// Y-pos below defenseblock area. need to start paying attention.
		if((*it).position.y < defense_blocks[0].position.y + (defenseheight/2) + 1) {
			// check against defense_blocks
			size_t ds = defense_blocks.size();
			for (size_t j = 0; j < ds; j++) {
				int left = defense_blocks[j].position.x - defensewidth/2;
				int right = defense_blocks[j].position.x + defensewidth/2;
				// is this bullet inside block area?
				if ((*it).position.x > left && (*it).position.x < right) {
					// start pixel perfect collisions here
					Pointi dp = damagePoint(defense_blocks[j], (*it).position);
					if (dp != POINT_OF_NO_RETURN) {
						todelete = 1;
						// this means an impact position is found inside defenseblock
						//std::cout << "damagepoint: ("<<dp.x<<","<<dp.y<<")"<<std::endl;
						explosion(defense_blocks[j], dp);
					}
				}
			}
		}
		// below the screen
		if((*it).position.y < 4) {
			todelete = 1;
		}
		// actually delete the bullet
		if (todelete == 1) {
			canvas->clearSprite((*it).frames[0]);
			canvas->clearSprite((*it).frames[1]);
			it = enemy_bullets.erase(it);
		} else {
			++it;
		}
	}
	counter++;
}

Pointi Scene13::damagePoint(PixelSprite& victim, Pointi pos)
{
	Pointi damagepoint = POINT_OF_NO_RETURN;
	std::vector<Pixel>::iterator it = victim.pixels.begin();
	while (it != victim.pixels.end()) {
		if ((*it).position == pos - victim.position) { // each pixel is in local coord system around center pivot
			damagepoint = (*it).position;
			//it = victim.pixels.erase(it); // delete pixel from victim
			(*it).color = RED;
			++it;
		} else {
			++it;
		}
	}

	return damagepoint;
}

void Scene13::explosion(PixelSprite& victim, Pointi pos)
{
	//std::cout << "local damagepoint: ("<<pos.x<<","<<pos.y<<")"<<std::endl;
	std::vector<Pointi> explosionpixels;
	explosionpixels.push_back(Pointi(-1,1)); // leftabove
	explosionpixels.push_back(Pointi(0,1)); // above
	explosionpixels.push_back(Pointi(1,1)); // rightabove

	explosionpixels.push_back(Pointi(-1,0)); // left
	explosionpixels.push_back(Pointi(0,0)); // itself
	explosionpixels.push_back(Pointi(1,0)); // right

	explosionpixels.push_back(Pointi(2,0)); // right right
	explosionpixels.push_back(Pointi(-2,0)); // left left

	explosionpixels.push_back(Pointi(-1,-1)); // leftbelow
	explosionpixels.push_back(Pointi(0,-1)); // below
	explosionpixels.push_back(Pointi(1,-1)); // rightbelow

	//std::cout << "finding " << pos.x << "," << pos.y << std::endl;
	size_t s = explosionpixels.size();
	for (size_t i = 0; i < s; i++) {
		std::vector<Pixel>::iterator it = victim.pixels.begin();
		while (it != victim.pixels.end()) {
			if ((*it).position == pos + explosionpixels[i]) {
				it = victim.pixels.erase(it);
				//std::cout << i << ": " << (*it).position.x << "," << (*it).position.y << std::endl;
				// TODO fix: can't delete pixels further to the left or right?
				//(*it).color = RED;
				//++it;
			} else {
				++it;
			}
		}
	}
}

void Scene13::updatePlayerBullets()
{
	// defense blocks
	int defensewidth = 32;
	int defenseheight = 16;

	std::vector<PixelSprite>::iterator it = player_bullets.begin();
	while (it != player_bullets.end()) {
		int todelete = 0;

		canvas->clearSprite((*it));
		(*it).position.y += 1;
		canvas->drawSprite((*it));

		// Y-pos still below defenseblock area. need to start paying attention.
		if((*it).position.y < defense_blocks[0].position.y + (defenseheight/2) + 1) {
			// check against defense_blocks
			size_t ds = defense_blocks.size();
			for (size_t j = 0; j < ds; j++) {
				int left = defense_blocks[j].position.x - defensewidth/2;
				int right = defense_blocks[j].position.x + defensewidth/2;
				// is this bullet inside block area?
				if ((*it).position.x > left && (*it).position.x < right) {
					// start pixel perfect collisions here
					Pointi dp = damagePoint(defense_blocks[j], (*it).position);
					if (dp != POINT_OF_NO_RETURN) {
						todelete = 1;
						// this means an impact position is found inside defenseblock
						//std::cout << "damagepoint: ("<<dp.x<<","<<dp.y<<")"<<std::endl;
						explosion(defense_blocks[j], dp);
					}
				}
			}
		}
		// above the screen
		if((*it).position.y > canvas->height()) {
			todelete = 1;
		}
		// actually delete the bullet
		if (todelete == 1) {
			canvas->clearSprite((*it));
			it = player_bullets.erase(it);
		} else {
			++it;
		}
	}
}

void Scene13::updateDefenseGrid()
{
	size_t s = defense_blocks.size();
	for (size_t i = 0; i < s; i++) {
		canvas->drawSprite(defense_blocks[i]);
	}
}

void Scene13::setupEnemyGrid()
{
	size_t width = 16;
	for (size_t y = 0; y < 5; y++) {
		for (size_t x = 0; x < width; x++) {
			SI_AnimatedSprite e;
			if (y == 0) { e = si_enemy_a; }
			if (y == 1) { e = si_enemy_b; }
			if (y == 2) { e = si_enemy_b; }
			if (y == 3) { e = si_enemy_c; }
			if (y == 4) { e = si_enemy_c; }

			e.position = Pointi((x*16)-((width/2)*16), 60 - (y*16));
			e.velocity = Pointi(1,0);
			enemies.push_back(e);
		}
	}
}

void Scene13::setupDefenseGrid()
{
	size_t num = 5;
	int spacing = 64;
	for (size_t x = 0; x < num; x++) {
		PixelSprite d = defense_block; // copy sprites etc
		d.position = Pointi((x*spacing)+32, 32);
		defense_blocks.push_back(d);
	}
}










void Scene13::setupEnemyA()
{
	char enemyA0Sprite[64] = { // 8*8
		0,0,0,1,1,0,0,0,
		0,0,1,1,1,1,0,0,
		0,1,1,1,1,1,1,0,
		1,1,0,1,1,0,1,1,
		1,1,1,1,1,1,1,1,
		0,1,0,1,1,0,1,0,
		1,0,0,0,0,0,0,1,
		0,1,0,0,0,0,1,0,
	};

	PixelSprite enemyA0;
	enemyA0.init(enemyA0Sprite, 8, 8);
	enemyA0.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	char enemyA1Sprite[64] = { // 8*8
		0,0,0,1,1,0,0,0,
		0,0,1,1,1,1,0,0,
		0,1,1,1,1,1,1,0,
		1,1,0,1,1,0,1,1,
		1,1,1,1,1,1,1,1,
		0,0,1,0,0,1,0,0,
		0,1,0,1,1,0,1,0,
		1,0,1,0,0,1,0,1,
	};

	PixelSprite enemyA1;
	enemyA1.init(enemyA1Sprite, 8, 8);
	enemyA1.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	si_enemy_a.addPixelSprite(enemyA0);
	si_enemy_a.addPixelSprite(enemyA1);
}

void Scene13::setupEnemyB()
{
	char enemyB0Sprite[88] = { // 11*8
		0,0,1,0,0,0,0,0,1,0,0,
		1,0,0,1,0,0,0,1,0,0,1,
		1,0,1,1,1,1,1,1,1,0,1,
		1,1,1,0,1,1,1,0,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,1,1,1,1,0,
		0,0,1,0,0,0,0,0,1,0,0,
		0,1,0,0,0,0,0,0,0,1,0
	};

	PixelSprite enemyB0;
	enemyB0.init(enemyB0Sprite, 11, 8);
	enemyB0.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	char enemyB1Sprite[88] = { // 11*8
		0,0,1,0,0,0,0,0,1,0,0,
		0,0,0,1,0,0,0,1,0,0,0,
		0,0,1,1,1,1,1,1,1,0,0,
		0,1,1,0,1,1,1,0,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,
		1,0,1,0,0,0,0,0,1,0,1,
		0,0,0,1,1,0,1,1,0,0,0
	};

	PixelSprite enemyB1;
	enemyB1.init(enemyB1Sprite, 11, 8);
	enemyB1.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	si_enemy_b.addPixelSprite(enemyB0);
	si_enemy_b.addPixelSprite(enemyB1);
}

void Scene13::setupEnemyC()
{
	char enemyC0Sprite[96] = { // 12*8
		0,0,0,0,1,1,1,1,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,0,0,1,1,0,0,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		0,0,0,1,1,0,0,1,1,0,0,0,
		0,0,1,1,0,1,1,0,1,1,0,0,
		1,1,0,0,0,0,0,0,0,0,1,1
	};

	PixelSprite enemyC0;
	enemyC0.init(enemyC0Sprite, 12, 8);
	enemyC0.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	char enemyC1Sprite[96] = { // 12*8
		0,0,0,0,1,1,1,1,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,0,0,1,1,0,0,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,
		0,0,1,1,0,0,0,0,1,1,0,0,
		0,1,1,0,0,1,1,0,0,1,1,0,
		0,0,1,1,0,0,0,0,1,1,0,0
	};

	PixelSprite enemyC1;
	enemyC1.init(enemyC1Sprite, 12, 8);
	enemyC1.position = Pointi(canvas->width() / 2, canvas->height() / 2);

	si_enemy_c.addPixelSprite(enemyC0);
	si_enemy_c.addPixelSprite(enemyC1);
}

void Scene13::setupEnemyBullet()
{
	char enemybullet0Sprite[10] = { // 2*5
		0,1,
		1,0,
		0,1,
		1,0,
		0,1
	};

	PixelSprite enemybullet0;
	enemybullet0.init(enemybullet0Sprite, 2, 5);
	//enemybullet0.position = Pointi(canvas->width() / 2, canvas->height() / 3);

	char enemybullet1Sprite[10] = { // 2*5
		1,0,
		0,1,
		1,0,
		0,1,
		1,0
	};

	PixelSprite enemybullet1;
	enemybullet1.init(enemybullet1Sprite, 2, 5);
	//enemybullet1.position = Pointi(canvas->width() / 2 + 10, canvas->height() / 3);

	si_enemy_bullet.addPixelSprite(enemybullet0);
	si_enemy_bullet.addPixelSprite(enemybullet1);
}

void Scene13::setupPlayerBullet()
{
	char playerbulletSprite[6] = { // 2*3
		1,1,
		1,1,
		1,1
	};

	player_bullet.init(playerbulletSprite, 2, 3);
	//player_bullet.position = player.position;
}

void Scene13::setupDefenseBlock()
{
	char defenseBlockSprite[512] = { // 32*16
		0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1
	};

	defense_block.init(defenseBlockSprite, 32, 16);
	defense_block.position = Pointi(canvas->width() / 2, canvas->height() / 3);
}

void Scene13::setupPlayer()
{
	char playerSprite[128] = { // 16*8
		0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
		0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
	};

	player.init(playerSprite, 16, 8);
	player.position = Pointi(canvas->width() / 2, 8);
}
