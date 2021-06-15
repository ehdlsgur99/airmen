#include "common.h"

void Tail::init()
{
	tails.clear();
	tailTime = GetTickCount();
}

void Tail::update()
{
	createTail();

	// 捞悼
	if (Player::GetInstance()->state == eRight || Player::GetInstance()->state == eJump1 || Player::GetInstance()->state == eJump2)
	{
		for (int i = 0; i < tails.size(); i++)
		{
			tails[i]->pos.x -= 6;
		}
	}
	else
	{
		tailTime = GetTickCount();
	}
}

void Tail::render()
{
	for (int i = 0; i < tails.size(); i++)
	{
		GraphicManager::GetInstance()->render(tails[i]);
	}
}

void Tail::release()
{

}

void Tail::createTail()
{
	if (GetTickCount() - tailTime >= 5000)
	{
		// tail 农扁 抄荐 积己
		int width = rand() % 600 + 200;
		int height = rand() % 100 + 550;
		tailTime = GetTickCount();

		// tail 积己
		GameObject* tempTail = new GameObject;
		if (Player::GetInstance()->level % 2 == 1)
		{
			tempTail->loadTexture("Resource/GameScene/tail.png");
		}
		else
		{
			tempTail->loadTexture("Resource/GameScene/BG3/tail.png");
		}
	
		tempTail->setSize(width, 50);
		tempTail->setPos(1600, height);

		tails.push_back(tempTail);
	}
}