#pragma once

#include "common.h"

class EndScene : public Scene
{
public:
	EndScene();
	~EndScene();
public:
	void init();
	void update();
	void render();
	void release();
private:
	GameObject* BG;
	GameObject* player;
	GameObject* info;
};

