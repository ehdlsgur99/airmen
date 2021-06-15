#pragma once

#include "common.h"

class Player : public CSingleton<Player>
{
public:
	ePlayer state;
	ePlayer nextState;
	int hp;
	int mp;
	int nowHp;
	int nowMp;

	std::string name;
	int mappos = 0;
	int JumpTime = 0;
	int JumpCount = 0;
	int JumpPower = 1000;

public:
	GameObject* player;
	PlayerBar* playerBar;
	PlayerUI* playerUI;

	bool isUI;
	bool isAttack;
	bool isJump;
public:
	
	int power;

	Player();
	~Player();
	
	int getPlayerState();
	void init();
	void update();
	void render();
	void release();
};

