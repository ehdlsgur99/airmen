#include "common.h"

void Tail::init()
{
	tails.clear();
	tailTime = GetTickCount();
}

void Tail::update()
{
	createTail();

	// �̵�
	if (Player::GetInstance()->state == eRight)
	{
		for (int i = 0; i < tails.size(); i++)
		{
			tails[i]->pos.x -= 5;
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
		// tail ũ�� ���� ����
		int width = rand() % 600 + 200;
		int height = rand() % 100 + 450;
		tailTime = GetTickCount();

		// tail ����
		GameObject* tempTail = new GameObject;
		tempTail->loadTexture("Resource/GameScene/tail.png");
		tempTail->setSize(width, 50);
		tempTail->setPos(1600, height);

		tails.push_back(tempTail);
	}
}