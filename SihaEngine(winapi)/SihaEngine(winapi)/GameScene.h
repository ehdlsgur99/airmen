#pragma once

#include "common.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

private:
	void init();
	void update();
	void render();

private:
	GameObject* testObj;
	GameObject* bg;
	GameObject* bg2;
};

