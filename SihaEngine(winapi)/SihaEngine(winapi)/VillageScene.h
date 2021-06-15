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
	GameObject *ground[70];
	GameObject* house[4];
	GameObject* box[10];
	GameObject* obj[10];
	GameObject* textbox[4];
	
	VillageMG* shop;
	int shoptime = 0;
	bool isOpen;
	
	
};

