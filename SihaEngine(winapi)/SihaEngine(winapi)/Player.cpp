#include "common.h"

Player::Player()
{

}

Player::~Player()
{

}

void Player::init()
{
	player = new GameObject;
	player->loadTexture("Resource/player/idle/player1.png");
	player->setSrcSize(50, 37);
	player->setSize(200, 161);
	player->setPos(0, 620);
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
		state = eAttack1;
	}
	else
	{
		state = eIdle;
	}


	// 캐릭터 애니메이션
	switch (state)
	{
	case eIdle:
		player->animation("Resource/player/idle/player", 6, 200);
		break;
	case eLeft:
		player->animation("Resource/player/left/left", 6, 30);
		break;
	case eRight:
		player->animation("Resource/player/right/right", 6, 30);
		break;
	case eJump:
		player->animation("Resource/player/jump/jump", 6, 30);
		break;
	case eAttack1:

		break;
	case eAttack2:

		break;
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
