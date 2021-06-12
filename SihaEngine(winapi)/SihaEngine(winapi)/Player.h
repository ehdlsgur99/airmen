#pragma once

#include "common.h"

class Player : public CSingleton<Player>
{
private:
	ePlayer state;
	int hp;
	int mp;
	std::string name;
	int mappos = 0;

public:
	GameObject* player;
	
	Player();
	~Player();

	void init();
	void update();
	void render();
	void release();
};

