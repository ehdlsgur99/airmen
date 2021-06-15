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
	GameObject* layer[9];
	
	
	int swordPower;
	int armorPower;
	int ringPower;

	int hpPotionNum;
	int mpPotionNum;
	int coinNum;

	bool Buysword;
	bool Buyarmor;
	bool Buyring;
	bool BuyhpPotion;
	bool BuympPotion;
	
public:

	void init();
	void update();
	void render();
	void release();
};

