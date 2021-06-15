#pragma once

#include "common.h"

class Tail
{
public:
	// 테일들을 관리할 vector
	std::vector<GameObject* >tails;
	// 테일 생성 나눗
	float tailTime;
public:
	void init();
	void update();
	void render();
	void release();

	void createTail();
};

