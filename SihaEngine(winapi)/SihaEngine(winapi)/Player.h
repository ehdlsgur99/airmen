#pragma once

#include "common.h"

class Player : public CSingleton<Player>
{
public:
	ePlayer state;
	ePlayer nextState;
	int hp;
	int mp;

	std::string name;
	bool isAttack;

public:
	GameObject* player;
	int power;
	Player();
	~Player();
	
	int getPlayerState();

	void init();
	void update();
	void render();
	void release();
};

