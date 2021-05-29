#pragma once

#include "common.h"

class Player : public GameObject
{
private:
	ePlayer state;
	int hp;
	int mp;
	std::string name;

public:
	Player();
	~Player();

	void init();
	void update();
	void render();
	void release();
};

