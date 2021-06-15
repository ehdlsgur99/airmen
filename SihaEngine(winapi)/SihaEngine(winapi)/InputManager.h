#pragma once

#include "common.h"

class InputManager : public CSingleton<InputManager>
{
private:
	WPARAM wparam;
public:
	// 이런 것들은 함수 만들기도 귀찮고 걍 바로 받아옵시다
	// 원래 이렇게하면 안됨..........
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
	// 내가 원하는 키랑, 현재 입력된 키가 같으면 true
	bool getKey(int type);
};

