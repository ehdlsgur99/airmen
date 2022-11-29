#include "common.h"

void print()
{
	printf("callback test");
}

PVPButton::PVPButton()
{
	isListUP = false;

	listButton = new Button();
	listButton->init("Resource/Button/PVPButton.png", "Resource/Button/PVPButton_.png",
		POINT{ 50, 150 }, SIZE{ 100, 50 }, [](){});

	listBG = new GameObject();
	listBG->loadTexture("Resource/Button/bg.png");
	listBG->setPos(500, 100);
	listBG->setSrcSize(2035, 2035);
	listBG->setSize(600, 600);
}

PVPButton::~PVPButton()
{
}

void PVPButton::update()
{
	listButton->update();
	if (listButton->getIsOn() && !isListUP)
	{
		listButton->setVisible(false);
		isListUP = true;
		// Player ȣ���ؼ� �����κ��� �����͸� �޾ƿ´�.
		Player::GetInstance()->setDataType(eDataType::eRquest);
		
		createList();
	}
}

void PVPButton::render()
{
	listButton->render();
	if (isListUP)
	{
		GraphicManager::GetInstance()->render(listBG);

		//int userNum = Player::GetInstance()->userInfos.size();
		//if (userNum != btnVector.size())
		//	createList();
		
		
		for (int i = 0; i < btnVector.size(); i++)
		{
			std::string str = std::to_string(Player::GetInstance()->userInfos[i]->ID) +
				std::to_string(Player::GetInstance()->userInfos[i]->power) +
				std::to_string(Player::GetInstance()->userInfos[i]->maxhp) +
				std::to_string(Player::GetInstance()->userInfos[i]->maxmp);

			GraphicManager::GetInstance()->drawText(str, POINT{ 0, 100 + i * 50 }, 50, RGB(255, 255, 255));

			btnVector[i]->render();
		}
		

	}
}

void PVPButton::createList()
{
	WaitForSingleObject(Player::GetInstance()->readOtherUserEvent, INFINITE);

	int userNum = Player::GetInstance()->userInfos.size();
	btnVector.clear();
	btnVector.reserve(userNum);
	// ������ ���� ��ŭ ��� ����'
	for (int i = 0; i < userNum; i++)
	{
		Button* btn = new Button();
		btn->init("Resource/Button/invitebtn.png", "Resource/Button/invitebtn_.png", POINT{ 100, 100 + i* 50 },
			SIZE{ 100, 50 }, []() {});
		btnVector.push_back(btn);
	}


}

void PVPButton::toggleListUp()
{
	isListUP = !isListUP;
}
