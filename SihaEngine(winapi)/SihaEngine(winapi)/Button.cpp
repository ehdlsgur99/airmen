#include "common.h"

void Button::init(std::string path1, std::string path2, POINT pos, SIZE size, std::function<void()> func)
{
	button = new GameObject;
	button->loadTexture(path1);
	button->pos = pos;
	button->size = size;

	button_ = new GameObject;
	button_->loadTexture(path2);
	button_->pos = pos;
	button_->size = size;

	this->func = func;

	isOn = false;
}

void Button::update()
{
	// 클릭 확인
	isOn = false;
	POINT LButtonPos = InputManager::GetInstance()->LButtonPos;
	if (LButtonPos.x > button->pos.x && LButtonPos.x < button->pos.x + button->size.cx &&
		LButtonPos.y > button->pos.y && LButtonPos.y < button->pos.y + button->size.cy)
	{
		isOn = true;
	}
	if (InputManager::GetInstance()->isLButtonUp)
	{
		if (isOn)
		{
			// callback 함수 실행
			func();
			isOn = false;
		}
	}
}

void Button::render()
{
	if(isOn)
		GraphicManager::GetInstance()->render(button_);
	else
		GraphicManager::GetInstance()->render(button);

}

void Button::release()
{
}
