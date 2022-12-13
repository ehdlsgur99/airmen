#pragma once

#include "common.h"
#define GROUNDINDEX 40

class PVPScene : public Scene
{
public:
	PVPScene();
	~PVPScene();
	
	int crushPower = 50;

	
	
private:
	void init();
	void update();
	void render();
	void release();
private:
	GameObject* bg;
	GameObject* backbd;
	GameObject* backst;
	GameObject* ground[GROUNDINDEX];



	// tail
	//Tail* tail;


	GameObject* Text;

	bool GameSet;
	bool isWin;
	int c=0;

};

