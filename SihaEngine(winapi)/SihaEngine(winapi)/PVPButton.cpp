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

	yesBtn = new Button();
	yesBtn->init("Resource/Button/yesbtn.png", "Resource/Button/yesbtn_.png",
		POINT{ 680, 580 }, SIZE{ 100, 50 }, []() {});

	noBtn = new Button();
	noBtn->init("Resource/Button/nobtn.png", "Resource/Button/nobtn_.png",
		POINT{ 820, 580 }, SIZE{ 100, 50 }, []() {});

	pvpBG = new GameObject();
	pvpBG->loadTexture("Resource/Button/bg.png");
	pvpBG->setPos(500, 400);
	pvpBG->setSrcSize(2035, 2035);
	pvpBG->setSize(600, 200);

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
		Player::GetInstance()->setDataType(eDataType::eRequest);
		
		createList();
	}

	if (isListUP)
	{
		for (int i = 0; i < btnVector.size(); i++)
		{
			btnVector[i]->update();
			if (btnVector[i]->getIsOn())
			{
				Player::GetInstance()->userInfo.DataType = eDataType::eInviteSend;
				Player::GetInstance()->userInfo.PVPID = i + 1;
				listButton->setVisible(true);
				isListUP = false;
				break;
			}
		}
	}

	if (Player::GetInstance()->getUserInfo().DataType == eInviteRecv)
	{
		if (yesBtn->getIsOn())
		{
			Player::GetInstance()->userInfo.isPvP = true;
			Player::GetInstance()->setDataType(eDataType::eGoToPVP);
			pvpBG->isVisible = false;
			yesBtn->setVisible(false);
			noBtn->setVisible(false);
		}
		else if (noBtn->getIsOn())
		{
			Player::GetInstance()->userInfo.isPvP = false;
			pvpBG->isVisible  = false;
			yesBtn->setVisible(false);
			noBtn->setVisible(false);
		}
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
		
		Player::GetInstance()->getUserInfos();
		for (int i = 0; i < btnVector.size(); i++)
		{
			
			std::string str = "ID : " + std::to_string(Player::GetInstance()->userInfos[i].ID) +
				" Power : " + std::to_string(Player::GetInstance()->userInfos[i].power) +
				" HP : " + std::to_string(Player::GetInstance()->userInfos[i].maxhp) +
				" MP : " + std::to_string(Player::GetInstance()->userInfos[i].maxmp);
			
			GraphicManager::GetInstance()->drawText(str, POINT{ 550, 110 + i * 50 }, 10, RGB(255, 255, 255));

			btnVector[i]->render();
		}
	}
	if (Player::GetInstance()->getUserInfo().DataType == eInviteRecv)
	{
		GraphicManager::GetInstance()->render(pvpBG);
		yesBtn->render();
		noBtn->render();
		std::string str = " " + std::to_string(Player::GetInstance()->enemyInfo.PVPID) + "번 님이 PVP를 신청했습니다.";

		GraphicManager::GetInstance()->drawText(str, POINT{ 500, 460 }, 20, RGB(255, 255, 255));

	}
}

void PVPButton::createList()
{
	WaitForSingleObject(Player::GetInstance()->readOtherUserEvent, 1000);

	int userNum = Player::GetInstance()->userInfos.size();
	btnVector.clear();
	btnVector.reserve(userNum);
	// 유저의 숫자 만큼 블록 생성'
	for (int i = 0; i < userNum; i++)
	{
		Button* btn = new Button();
		btn->init("Resource/Button/invitebtn.png", "Resource/Button/invitebtn_.png", POINT{ 1000, 100 + i* 50 },
			SIZE{ 80, 30 }, []() {});
		btnVector.push_back(btn);
	}
	//Player::GetInstance()->userInfo.DataType = eDataType::eNone;

}

void PVPButton::toggleListUp()
{
	isListUP = !isListUP;
}
