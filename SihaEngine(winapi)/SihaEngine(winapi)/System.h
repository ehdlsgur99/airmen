#pragma once

#include "common.h"

class System
{
public:
	System();
	~System();

	// �ʱ�ȭ, �޼�������, ������, �׸��� ���� ������ �̷�����ִ�.
	// ������ ������ ���ư��� �κ��� �޼������� - ���η����̴�.
	void init();
	void msgLoop();
	void release();
	void mainLoop();
};

