#pragma once

#include "common.h"

class InputManager : public CSingleton<InputManager>
{
private:
	WPARAM wparam;
public:
	// �̷� �͵��� �Լ� ����⵵ ������ �� �ٷ� �޾ƿɽô�
	// ���� �̷����ϸ� �ȵ�..........
	bool isLButtonDonw;
	bool isLButtonUp;
	POINT LButtonPos;

	bool isRButtonDonw;
	bool isRButtonUp;
	POINT RButtonPos;

	bool isKeyDown;
	bool isKeyUp;

	int inputDelay;

public:
	void init();
	// ���� ���ϴ� Ű��, ���� �Էµ� Ű�� ������ true
	bool getKey(int type);
};

