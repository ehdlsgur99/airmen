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

// getKey 사용할때
// https://m.blog.naver.com/power2845/50143021565 참고

void Player::update()
{
	// 캐릭터 애니메이션

	

	// 캐릭터 이동 예시
	if (InputManager::GetInstance()->getKey(VK_LEFT))
	{
		if(!isJump)
			state = eLeft;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{
			if (mappos >= 800 && mappos <= 1000)
				player->pos.x += 10;
			if (mappos >= 0) {
				player->pos.x -= 10;
				ObjectManager::GetInstance()->cameraMove(-10, 0);
				mappos -= 10;
			}
			
		}
	}
	else if (InputManager::GetInstance()->getKey(VK_RIGHT))
	{
		if (!isJump)
			state = eRight;
		if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
		{

			if(mappos>=800&&mappos<=1000)
				player->pos.x -= 10;
			if (mappos <= 1600) {
				player->pos.x += 10;
				ObjectManager::GetInstance()->cameraMove(10, 0);
				mappos += 10;
			}
		}
			
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
	if (InputManager::GetInstance()->getKey(VK_UP))
	{
		if (!isJump && state != eJump1)
		{
			state = eJump1;
			isJump = true;
			JumpCount = 0;
		}
	}

	if (isJump  && GetTickCount64() - JumpTime >= 50)
	{
		JumpTime = GetTickCount64();
		if (JumpCount < 16)
		{
			if (JumpCount < 8)
				player->pos.y -= 15;
			else
				player->pos.y += 15;
			JumpCount++;
		}
		else
		{
			state = eIdle;
			JumpCount = 0;
			isJump = false;
		}
		
	}


	// 캐릭터 애니메이션
	switch (state)
	{
	case eIdle:
		player->animation("Resource/player/idle/player", 6, 200);
		break;
	case eLeft:
		if (player->animation("Resource/player/left/left", 6, 30))
			state = eIdle;

		break;
	case eRight:
		if (player->animation("Resource/player/right/right", 6, 30))
		{
			state = eIdle;
			if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
				state = eRight;
		}
		break;
	case eJump1:

		if (player->animation("Resource/player/jump/jump", 4, 200)) {
			//if (nextState == eJump2)
			//	state = eJump2;
			//else
			//{
			//	state = eIdle;
			//	isJump = false;
			//}
		}
			
		break;
	case eJump2:

		if (player->animation("Resource/player/doublejump/doublejump", 4, 100)) {
			isJump = false;
			nextState = eIdle;
			state = eIdle;
		}
			
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

	if(SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
		playerBar->update();
}

void Player::render()
{
	GraphicManager::GetInstance()->render(player);

	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
		playerBar->render();
}

void Player::release()
{
	GraphicManager::GetInstance()->release();
}
