#pragma once

#include "common.h"

class MonsterControl
{
public:
	void init();
	void update();
	void render();
	void release();

	void spawnMonser();
	// �浹 üũ
	void checkColiision();
public:
	float spawnDelay;
	float spawnTime;
	std::vector<Monster*> monsters;
};

