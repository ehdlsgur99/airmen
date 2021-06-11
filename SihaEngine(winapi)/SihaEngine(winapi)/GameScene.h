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
	void release();
private:
	GameObject* testObj;
	GameBG* gameBg;

	bool isChange;
};

