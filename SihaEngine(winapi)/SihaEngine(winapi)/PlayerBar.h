#pragma once

#include "common.h"

class PlayerBar
{

public:
	GameObject* hpIcon;
	GameObject* mpIcon;
	GameObject* hpBar;
	GameObject* mpBar;

	GameObject* hpPotion;
	GameObject* mpPotion;
	GameObject* coin;

public:
	void init();
	void update();
	void render(PlayerUI* ui);
	void release();
};

