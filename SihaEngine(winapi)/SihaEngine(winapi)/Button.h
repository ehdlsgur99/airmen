#pragma once

#include "common.h"
#include <functional>

/// <summary>
/// init() 버튼 1, 2 파일위치, 위치, 크기, 콜백함수
/// button 이 평소 출력 되다가 클릭시에 button_ 으로 변경됩니다. 클릭시 콜백함수가 호출됩니다.
/// </summary>
class Button
{
public:
	void init(std::string path1, std::string path2, POINT pos, SIZE size, std::function<void()> func);
	void update();
	void render();
	void release();

	bool getIsOn();

	void setSrcSize(SIZE srcSize);

	void setVisible(bool isVisible);

	std::string text;
private:
	// button : 평소 버튼 이미지, button_ : 버튼 눌렸을 때 이미지
	GameObject* button;
	GameObject* button_;
	bool isOn;

	

	std::function<void()> func;
};

