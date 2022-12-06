#include "common.h"

UserInfo info2;

OtherPlayer::OtherPlayer()
{
	level = 1;

	//userInfo = new UserInfo;
	hpbar = new GameObject;
	hpbar->loadTexture("Resource/monster/hpbar.png");
	hpbar->setSrcSize(200, 20);
	hpbar->setSize(100, 10);

	Oplayer = new GameObject;
	Oplayer->loadTexture("Resource/player/idle/player1.png");
	Oplayer->setSrcSize(50, 37);
	Oplayer->setSize(200, 161);
	Oplayer->setPos(0, 620);

	Osmash = new GameObject;
	Osmash->setSize(150, 120);
	Osmash->setPos(Oplayer->pos.x, Oplayer->pos.y);

	dir = eLeft;
	state = eIdle;

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
	hpbar->setPos(Oplayer->pos.x + 60, Oplayer->pos.y + 15);
	dir = Player::GetInstance()->enemyInfo.dir;
	state = Player::GetInstance()->enemyInfo.state;
	Oplayer->pos.x = Player::GetInstance()->enemyInfo.x;
	Oplayer->pos.y = Player::GetInstance()->enemyInfo.y;
	
	// 캐릭터 애니메이션
	if (dir == eLeft)
	{
		switch (state)
		{
		case eIdle:
			Oplayer->animation("Resource/player/Left State/idle/player", 6, 200);
			break;
		case eWalk:
			if (Oplayer->animation("Resource/player/Left State/left/left", 6, 30))
				state = eIdle;
			break;
		case eJump:

			if (Oplayer->animation("Resource/player/Left State/jump/jump", 4, 200)) {
				//if (nextState == eJump2)
				//	state = eJump2;
				//else
				//{
				//	state = eIdle;
				//	isJump = false;
				//}
			}

			break;
		case eAttack1:
			if (Oplayer->animation("Resource/player/Left State/attack/attack1-", 6, 100))
			{
				if (nextState == eAttack2)
					state = eAttack2;
				else
				{
					nextState = eIdle;
					state = eIdle;
					isAttack = false;
				}
			}
			break;
		case eAttack2:
			if (Oplayer->animation("Resource/player/Left State/attack/attack2-", 6, 100))
			{
				isAttack = false;
				nextState = eIdle;
				state = eIdle;
			}

			break;
		case eAttacked:
			if (Oplayer->animation("Resource/player/Left State/hurt/hurt-", 6, 200))
			{
				nextState = eIdle;
				state = eIdle;

			}
		default:
			break;
		}

	}
	else if (dir == eRight)
	{
		switch (state)
		{
		case eIdle:
			Oplayer->animation("Resource/player/Right State/idle/player", 6, 200);
			break;
		case eWalk:
			if (Oplayer->animation("Resource/player/Right State/right/right", 6, 30))
				state = eIdle;
			break;
		case eJump:
			if (Oplayer->animation("Resource/player/Right State/jump/jump", 4, 200)) {
				//if (nextState == eJump2)
				//	state = eJump2;
				//else
				//{
				//	state = eIdle;
				//	isJump = false;
				//}
			}

			break;
		case eAttack1:
			if (Oplayer->animation("Resource/player/Right State/attack/attack1-", 6, 100))
			{
				if (nextState == eAttack2)
					state = eAttack2;
				else
				{
					nextState = eIdle;
					state = eIdle;
					isAttack = false;
				}
			}
			break;
		case eAttack2:
			if (Oplayer->animation("Resource/player/Right State/attack/attack2-", 6, 100))
			{
				isAttack = false;
				nextState = eIdle;
				state = eIdle;
			}

			break;
		case eAttacked:
			if (Oplayer->animation("Resource/player/Right State/hurt/hurt-", 6, 200))
			{
				nextState = eIdle;
				state = eIdle;
			}
		default:
			break;
		}
	}

	// 스매쉬 이동
	if (isSmash)
	{
		if (dir == eLeft)
		{
			Osmash->animation("Resource/GameScene/smash", 4, 100);
			Osmash->pos.x -= 10;
			if (Osmash->pos.x <= 0)
			{
				isSmash = false;
				Osmash->pos.x = -100;
			}
		}
		else if (dir == eRight)
		{
			Osmash->animation("Resource/GameScene/smash", 4, 100);
			Osmash->pos.x += 10;
			if (Osmash->pos.x >= 2000)
			{
				isSmash = false;
				Osmash->pos.x = -100;
			}
		}

	}
}

void OtherPlayer::render()
{
	GraphicManager::GetInstance()->render(Oplayer);

	if (isSmash)
		GraphicManager::GetInstance()->render(Osmash);
	GraphicManager::GetInstance()->render(hpbar);
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
