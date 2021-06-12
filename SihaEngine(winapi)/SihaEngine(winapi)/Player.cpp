#include "common.h"

Player::Player()
{

}

Player::~Player()
{

}

int Player::getPlayerState()
{
	return state;
}

void Player::init()
{
	player = new GameObject;
	player->loadTexture("Resource/player/idle/player1.png");
	player->setSrcSize(50, 37);
	player->setSize(200, 161);
	player->setPos(50, 620);

	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
	{
		power = 100;
		state = eRight;
	}
}

// getKey 사용할때
// https://m.blog.naver.com/power2845/50143021565 참고

void Player::update()
{
	// 캐릭터 애니메이션

	

	// 캐릭터 이동 예시
	if (InputManager::GetInstance()->getKey(VK_LEFT))
	{
		state = eLeft;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{
			player->pos.x -= 5;
		}
	}
	else if (InputManager::GetInstance()->getKey(VK_RIGHT))
	{
		state = eRight;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{
			player->pos.x += 5;
		}
	}
	else if (InputManager::GetInstance()->getKey(0x41))
	{
		if (!isAttack || state != eAttack2)
		{
			state = eAttack1;
			isAttack = true;
		}
		if (isAttack && state == eAttack1 && player->aniNow >= 4)
		{
			nextState = eAttack2;
		}
	
	}
	


	// 캐릭터 애니메이션
	switch (state)
	{
	case eIdle:
		player->animation("Resource/player/idle/player", 6, 200);
		break;
	case eLeft:
		if (player->animation("Resource/player/left/left", 6, 100))
			state = eIdle;

		break;
	case eRight:
		if (player->animation("Resource/player/right/right", 6, 100))
		{
			state = eIdle;
			if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
				state = eRight;
		}
		break;
	case eJump:
		break;
	case eAttack1:
		if (player->animation("Resource/player/attack/attack1-", 6, 100))
		{
			if (nextState == eAttack2)
				state = eAttack2;
			else
			{
				state = eRight;
				isAttack = false;
			}		
		}
		break;
	case eAttack2:
		if (player->animation("Resource/player/attack/attack2-", 6, 100))
		{
			isAttack = false;
			nextState = eRight;
			state = eRight;
		}
			
		break;
	case eAttacked:
		if (player->animation("Resource/player/hurt/hurt-", 6, 200))
		{
			nextState = eRight;
			state = eRight;
		}
	default:
		break;
	}
}

void Player::render()
{
	GraphicManager::GetInstance()->render(player);
}

void Player::release()
{
	GraphicManager::GetInstance()->release();
}
