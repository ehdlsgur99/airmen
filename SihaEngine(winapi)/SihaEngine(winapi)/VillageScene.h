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
	GameObject* ground[27];

	GameObject* house1;
	GameObject* house2;
	//GameObject* house3;
	
};

