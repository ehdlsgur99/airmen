#pragma once

#include "common.h"

class Tail
{
public:
	// ���ϵ��� ������ vector
	std::vector<GameObject* >tails;
	// ���� ���� ����
	float tailTime;
public:
	void init();
	void update();
	void render();
	void release();

	void createTail();
};

