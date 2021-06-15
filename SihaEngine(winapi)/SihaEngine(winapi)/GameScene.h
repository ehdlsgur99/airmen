#pragma once

#include "common.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void checkEnd();
	void createPortal();
private:
	void init();
	void update();
	void render();
	void release();
private:
	GameObject* portal;
	GameBG* gameBg;
	Tail* tail;
	MonsterControl *mc;

	bool isChange;
	bool isPortal;

	int startTime;


	// 이번 페이즈 끝나는거 계산 하는 count
	int endCount;
};

