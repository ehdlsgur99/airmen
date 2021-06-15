#pragma once

#include "common.h"

class IntroScene : public Scene
{
public:
	IntroScene();
	~IntroScene();


private:
	void init();
	void update();
	void render();
	void release();
private:
	GameObject* main;
	GameObject* pressAnyKey;
	bool alpha;

};
