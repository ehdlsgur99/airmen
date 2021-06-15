#pragma once

#include "common.h"

class PlayerUI
{

public:
	GameObject* bg;
	GameObject* sword;
	GameObject* armor;
	GameObject* ring;

	GameObject* hpPotion;
	GameObject* mpPotion;

	GameObject* coin;

	int swordPower;
	int armorPower;
	int ringPower;

	int hpPotionNum;
	int mpPotionNum;
	int coinNum;
public:

	void init();
	void update();
	void render();
	void release();
};

