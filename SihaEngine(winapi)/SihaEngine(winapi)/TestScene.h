#pragma once

#include "common.h"

// scene �� ��� ����
// init, update, render �� ��� scene ���� virtual �� �Լ�����
class TestScene : public Scene
{
public:
	TestScene();
	~TestScene();

private:
	void init();
	void update();
	void render();

private:
	GameObject *testObj;
	GameObject* bg;
};
