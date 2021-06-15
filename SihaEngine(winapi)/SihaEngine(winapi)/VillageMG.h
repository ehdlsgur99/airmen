#pragma once

#include "common.h"

class VillageMG : public GameObject
{
private:
	GameObject* shop;
	GameObject* stuff[3];
	
public:
	void init();
	void update();
	void render();
	void release();
public:
	bool isOpen;
};

