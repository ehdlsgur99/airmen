#pragma once

#include "common.h"

class PVPButton
{
public:
	PVPButton();
	~PVPButton();

	void update();
	void render();

	void createList();

	void toggleListUp();
public:
	// pvp ����Ʈ �ҷ����� ��ư
	Button* listButton;

	// ����Ʈ ���
	GameObject* listBG;

	// �ʴ��� ���
	GameObject* pvpBG;
	
	Button* yesBtn;

	Button* noBtn;

	// �ݱ� ��ư
	Button* closeBtn;


	// ����Ʈ�� ����
	bool isListUP;

	// ���� ����Ʈ
	//std::vector<GameObject*> bgVector;
	std::vector<Button*> btnVector;
};

