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
		// Player 호출해서 서버로부터 데이터를 받아온다.
		//Player::GetInstance()
	}
}

void PVPButton::render()
{
	listButton->render();
	if (isListUP)
	{
		GraphicManager::GetInstance()->render(listBG);

	}
}

void PVPButton::toggleListUp()
{
	isListUP = !isListUP;
}
