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
	player->setPos(0, 620);

	

	playerBar = new PlayerBar;
	playerBar->init();

	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
	{
		nowHp = hp = 100;
		nowMp = mp = 100;
		player->setPos(0, 600);
		power = 10;
		state = eRight;

		
	}

}

// getKey ����Ҷ�
// https://m.blog.naver.com/power2845/50143021565 ����

void Player::update()
{
	// ĳ���� �ִϸ��̼�

	

	// ĳ���� �̵� ����
	if (InputManager::GetInstance()->getKey(VK_LEFT))
	{
		state = eLeft;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{
			if (mappos >= 800 && mappos <= 1000)
				player->pos.x += 20;
			if (mappos >= 0) {
				player->pos.x -= 20;
				ObjectManager::GetInstance()->cameraMove(-20, 0);
				mappos -= 20;
			}
			
		}
	}
	else if (InputManager::GetInstance()->getKey(VK_RIGHT))
	{
		state = eRight;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{

			if(mappos>=800&&mappos<=1000)
				player->pos.x -= 20;
			if (mappos <= 1600) {
				player->pos.x += 20;
				ObjectManager::GetInstance()->cameraMove(20, 0);
				mappos += 20;
			}
		}
			
		}
	else if (InputManager::GetInstance()->getKey(VK_UP))
	{
		state = eJump;
		
	}

	else if (InputManager::GetInstance()->getKey(0x41))
	{
		if (!isAttack || state != eAttack2 && state != eAttack1)
		{
			state = eAttack1;
			isAttack = true;
		}
		else if (isAttack && state == eAttack1 && player->aniNow >= 5)
		{
			nextState = eAttack2;
		}
	
	}
	


	// ĳ���� �ִϸ��̼�
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
		player->animation("Resource/player/jump/jump", 6, 30);
		break;
	case eAttack1:
		if (player->animation("Resource/player/attack/attack1-", 6, 100))
		{
			if (nextState == eAttack2)
				state = eAttack2;
			else
			{
				nextState = eRight;
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

	playerBar->update();
}

void Player::render()
{
	GraphicManager::GetInstance()->render(player);

	playerBar->render();
}

void Player::release()
{
	GraphicManager::GetInstance()->release();
}
