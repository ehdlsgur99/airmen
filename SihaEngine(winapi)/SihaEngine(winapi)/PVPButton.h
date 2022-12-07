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
	// pvp 리스트 불러오는 버튼
	Button* listButton;

	// 리스트 배경
	GameObject* listBG;

	// 초대장 배경
	GameObject* pvpBG;
	
	Button* yesBtn;

	Button* noBtn;

	// 닫기 버튼
	Button* closeBtn;


	// 리스트업 상태
	bool isListUP;

	// 유저 리스트
	//std::vector<GameObject*> bgVector;
	std::vector<Button*> btnVector;
};

