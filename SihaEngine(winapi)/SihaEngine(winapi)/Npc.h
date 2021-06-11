
#pragma once

#include "common.h"

class Npc : public CSingleton<Npc>
{
private:

public:
	GameObject* npc[4];

	Npc();
	~Npc();

	void init();
	void update();
	void render();
	void release();
};

