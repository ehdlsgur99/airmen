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


	// �̹� ������ �����°� ��� �ϴ� count
	int endCount;
};

