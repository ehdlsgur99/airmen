#pragma once

#include "common.h"

class PVPButton
{
public:
	PVPButton();
	~PVPButton();

	void update();
	void render();

	void toggleListUp();
public:
	// pvp ����Ʈ �ҷ����� ��ư
	Button* listButton;

	// ����Ʈ ���
	GameObject* listBG;

	// ����Ʈ�� ����
	bool isListUP;
};

