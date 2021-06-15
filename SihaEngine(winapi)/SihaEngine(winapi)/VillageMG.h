#pragma once

#include "common.h"

class VillageMG : public GameObject
{
private:
	
	
public:
	GameObject* shop;
	GameObject* stuff[5];
	GameObject* layer[9];

	void init();
	void update();
	void render();
	void release();
public:
	int randbox[3];
	
	bool isOpen;
};

