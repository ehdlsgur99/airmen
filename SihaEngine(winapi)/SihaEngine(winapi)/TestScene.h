#pragma once

#include "common.h"

// scene 을 상속 받음
// init, update, render 의 경우 scene 에서 virtual 된 함수들임
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
