#pragma once

#include "common.h"

class VillageScene : public Scene
{
public:
	VillageScene();
	~VillageScene();

private:
	void init();
	void update();
	void render();
	void release();
private:
	int groundx = 0;
	GameObject* bg;
	GameObject* mg;
	GameObject *ground[40];
	GameObject* house[3];
	GameObject* box[10];
	GameObject* obj[10];


	
	
};

