#pragma once

#include "common.h"

class Monster : public GameObject
{
public:
	void init(eMonsterType type);
	void update();
	void render();
	void release();

	void ani();
	void move();

	void smashAttacked();
	void attacked();
	void attack();
public:
	int hp;
	int speed;
	int power;
	bool isDie;
	bool isAttacked;
	bool isAttack;

	int playerOldState;

	GameObject* hpbar;

	eMonsterType monsterType;
	eMonsterState monsterState;
};

