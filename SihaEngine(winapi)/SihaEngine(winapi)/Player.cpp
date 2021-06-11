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
	player->setPos(50, 620);
}

void Player::update()
{
	// 캐릭터 애니메이션

	player->animation("Resource/player/idle/player", 4, 200);

	// 캐릭터 이동 예시
	if (InputManager::GetInstance()->getKey(VK_LEFT))
	{
		
		player->pos.x -= 5;
	}
	if (InputManager::GetInstance()->getKey(VK_RIGHT))
	{
		player->animation("Resource/player/run/run", 4, 30);
		player->pos.x += 5;
	}
	if (InputManager::GetInstance()->getKey(VK_SPACE))
	{
		SceneManager::GetInstance()->SceneChange(SceneManager::eVillage);
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
