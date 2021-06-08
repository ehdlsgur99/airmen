#pragma once

#include "common.h"

class Player : public CSingleton<Player>
{
private:
	ePlayer state;
	int hp;
	int mp;
	std::string name;
	GameObject* player;

public:
	Player();
	~Player();

	void init();
	void update();
	void render();
	void release();
};

