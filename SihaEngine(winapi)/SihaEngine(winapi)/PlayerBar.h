#pragma once

#include "common.h"

class PlayerBar
{

public:
	GameObject* hpIcon;
	GameObject* mpIcon;
	GameObject* hpBar;
	GameObject* mpBar;
public:
	void init();
	void update();
	void render();
	void release();
};

