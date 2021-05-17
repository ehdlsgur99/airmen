#include "common.h"

void InputManager::init()
{
	isLButtonDonw = false;
	isLButtonUp = true;
	LButtonPos.x = 0;
	LButtonPos.y = 0;

	isRButtonDonw = false;
	isRButtonUp = true;
	RButtonPos.x = 0;
	RButtonPos.y = 0;

	isKeyDown = false;
	isKeyUp = true;
}

bool InputManager::getKey(int type)
{
	//if (isKeyDown == false)
	//	return false;

	if (GetAsyncKeyState(type) & 0x8000)
		return true;
	else
		return false;
}