#pragma once

#include "common.h"
#include <functional>

/// <summary>
/// init() ��ư 1, 2 ������ġ, ��ġ, ũ��, �ݹ��Լ�
/// button �� ��� ��� �Ǵٰ� Ŭ���ÿ� button_ ���� ����˴ϴ�. Ŭ���� �ݹ��Լ��� ȣ��˴ϴ�.
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
	// button : ��� ��ư �̹���, button_ : ��ư ������ �� �̹���
	GameObject* button;
	GameObject* button_;
	bool isOn;

	

	std::function<void()> func;
};

