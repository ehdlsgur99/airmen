#pragma once

#include "common.h"

class PVPScene : public Scene
{
public:
	PVPScene();
	~PVPScene();

private:
	void init();
	void update();
	void render();
	void release();
private:
	GameObject* bg;
	GameObject* backbd;
	GameObject* backst;
	GameObject* ground[50];
	


};

