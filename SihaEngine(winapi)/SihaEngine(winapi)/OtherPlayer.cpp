#include "common.h"

UserInfo info2;

OtherPlayer::OtherPlayer()
{
	level = 1;

	//userInfo = new UserInfo;

	Oplayer = new GameObject;
	Oplayer->loadTexture("Resource/player/idle/player1.png");
	Oplayer->setSrcSize(50, 37);
	Oplayer->setSize(200, 161);
	Oplayer->setPos(0, 620);

	Osmash = new GameObject;
	Osmash->setSize(150, 120);
	Osmash->setPos(Oplayer->pos.x, Oplayer->pos.y);


	nowHp = hp = 100;
	nowMp = mp = 100;
	Oplayer->setPos(50, 560);
	power = 10;
	state = eRight;

	getUserInfo2();
}

OtherPlayer::~OtherPlayer()
{
}

UserInfo OtherPlayer::getUserInfo2()
{
	return userInfo;
}

int OtherPlayer::get2PlayerState()
{
	return state;
}

void OtherPlayer::init()
{
	Osmash = new GameObject;
	Osmash->setSize(150, 120);
	Osmash->setPos(-1000, Oplayer->pos.y);

}

void OtherPlayer::update()
{

	// 캐릭터 애니메이션
	switch (state)
	{
	case eIdle:
		Oplayer->animation("Resource/player/idle/player", 6, 200);
		break;
	}
}

void OtherPlayer::render()
{
	GraphicManager::GetInstance()->render(Oplayer);

	if (isSmash)
		GraphicManager::GetInstance()->render(Osmash);
}

void OtherPlayer::release()
{
	GraphicManager::GetInstance()->release();
}

void OtherPlayer::gravity(Tail* tail)
{
	// 플레이어는 바닥에 붙어 있는게 아니면 중력에 영향 받아야함 ㅇㅇ
	if (state != eJump)
	{
		if (Oplayer->pos.y <= 560)
		{
			bool isCrush = false;
			GameObject* tempObject = new GameObject;
			tempObject->size = Oplayer->size;
			tempObject->pos = Oplayer->pos;
			tempObject->size.cy = 20;
			tempObject->pos.y += 130;
			for (int i = 0; i < tail->tails.size(); i++)
			{
				if (CollisionManager::GetInstance()->RectCollisionCheck(tempObject, tail->tails[i]))
				{
					isCrush = true;
				}
			}
			if (!isCrush)
				Oplayer->pos.y += 10;
		}
	}
}
