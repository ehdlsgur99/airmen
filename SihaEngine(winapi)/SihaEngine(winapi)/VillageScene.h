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
	
	GameObject* bg;
	GameObject* mg;
	GameObject *ground[34];
	GameObject* house[3];
	GameObject* box[10];
	GameObject* obj[10];


	
	
};

