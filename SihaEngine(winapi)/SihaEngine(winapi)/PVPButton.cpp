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

	closeBtn = new Button();
	closeBtn->init("Resource/Button/close.png", "Resource/Button/close.png",
		POINT{ 770, 680 }, SIZE{ 50, 50 }, []() {});
	closeBtn->setSrcSize(SIZE{ 578, 578 });

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
		closeBtn->update();
		if (closeBtn->getIsOn())
		{
			listButton->setVisible(true);
			isListUP = false;
			Player::GetInstance()->userInfo.DataType = eDataType::eNone;
		}
		for (int i = 0; i < btnVector.size(); i++)
		{
			btnVector[i]->update();
			if (btnVector[i]->getIsOn())
			{
				Player::GetInstance()->userInfo.DataType = eDataType::eInviteSend;
				Player::GetInstance()->userInfo.PVPID = btnVector[i]->index;
				listButton->setVisible(true);
				isListUP = false;
				break;
			}
		}
	}

	if (Player::GetInstance()->getUserInfo().DataType == eInviteRecv)
	{
		yesBtn->update();
		noBtn->update();
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
			GraphicManager::GetInstance()->drawText(btnVector[i]->text, POINT{ 550, 110 + i * 50 }, 10, RGB(255, 255, 255));

			btnVector[i]->render();
		}
		closeBtn->render();
	}
	if (Player::GetInstance()->getUserInfo().DataType == eInviteRecv)
	{
		GraphicManager::GetInstance()->render(pvpBG);
		yesBtn->render();
		noBtn->render();
		std::string str = " " + std::to_string(Player::GetInstance()->userInfo.PVPID) + "번 님이 PVP를 신청했습니다.";

		GraphicManager::GetInstance()->drawText(str, POINT{ 500, 460 }, 20, RGB(255, 255, 255));

	}
}

void PVPButton::createList()
{
	WaitForSingleObject(Player::GetInstance()->readOtherUserEvent, 1000);

	int userNum = Player::GetInstance()->userInfos.size();
	btnVector.clear();
	btnVector.reserve(userNum);

	int realUserNum = 0;

	// 유저의 숫자 만큼 블록 생성'
	for (int i = 0; i < userNum; i++)
	{
		// in pvp, 본인, 종료 제외
		if (Player::GetInstance()->userInfos[i].DataType == eDataType::eInPVP)
			continue;
		if (Player::GetInstance()->userInfos[i].ID == Player::GetInstance()->userInfo.ID)
			continue;
		if (Player::GetInstance()->userInfos[i].DataType == eDataType::eExit)
			continue;
		
		Button* btn = new Button();
		btn->init("Resource/Button/invitebtn.png", "Resource/Button/invitebtn_.png", POINT{ 1000, 100 + realUserNum* 50 },
			SIZE{ 80, 30 }, []() {});
		std::string str = "ID : " + std::to_string(Player::GetInstance()->userInfos[i].ID) +
			" Power : " + std::to_string(Player::GetInstance()->userInfos[i].power) +
			" HP : " + std::to_string(Player::GetInstance()->userInfos[i].maxhp) +
			" MP : " + std::to_string(Player::GetInstance()->userInfos[i].maxmp);
		btn->text = str;
		// 유저는 누구인가?
		btn->index = Player::GetInstance()->userInfos[i].ID;
		realUserNum += 1;
		

		btnVector.push_back(btn);
	}
	//btnVector.reserve(realUserNum);
	//Player::GetInstance()->userInfo.DataType = eDataType::eNone;

}

void PVPButton::toggleListUp()
{
	isListUP = !isListUP;
}
