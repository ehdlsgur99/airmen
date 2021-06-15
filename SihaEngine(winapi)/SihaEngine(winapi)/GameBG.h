#pragma once

#include "common.h"

class GameBG
{
private:
	GameObject* layer1[10];
	GameObject* layer2[10];

public:
	void init();
	void update();
	void render();
	void release();
public:
	float moveTime;
	int level;
};

