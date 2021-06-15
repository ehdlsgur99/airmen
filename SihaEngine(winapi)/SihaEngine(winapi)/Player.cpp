#include "common.h"

Player::Player()
{
	level = 1;

	player = new GameObject;
	player->loadTexture("Resource/player/idle/player1.png");
	player->setSrcSize(50, 37);
	player->setSize(200, 161);
	player->setPos(0, 620);


	playerUI = new PlayerUI;
	playerUI->init();
	playerBar = new PlayerBar;
	playerBar->init();

	smash = new GameObject;
	smash->setSize(150, 120);
	smash->setPos(player->pos.x, player->pos.y);


	nowHp = hp = 100;
	nowMp = mp = 100;
	player->setPos(50, 560);
	power = 10;
	state = eRight;
	
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
	smash = new GameObject;
	smash->setSize(150, 120);
	smash->setPos(player->pos.x, player->pos.y);

	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
	{
		nowHp = hp;
		nowMp = mp ;
		player->setPos(50, 560);
		power = 10;
		state = eRight;
	}

}

// getKey 사용할때
// https://m.blog.naver.com/power2845/50143021565 참고

void Player::update()
{
	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eVillage)
	{
		if (player->pos.y <= 500)
		{
			player->pos.y += 10;
		}

	}
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
		else if (isAttack && state == eAttack1 && player->aniNow >= 5 && nextState != eAttack2)
		{
			if (nowMp >= 10)
			{
				nextState = eAttack2;
				nowMp -= 10;
			}
		}
	
	}
	// JUMP
	if (InputManager::GetInstance()->getKey(VK_UP))
	{

		if (!isJump && state != eJump1)
		{
			state = eJump1;
			isJump = true;
			JumpCount = 0;
		}
		// 점프1중 일때
		if (isJump && state == eJump1 && state != eJump2 && JumpCount > 2)
		{
			if (nowMp >= 10)
			{
				state = eJump2;
				JumpCount = 0;
				nowMp -= 10;
			}
		}
	}

	if (isJump  && GetTickCount64() - JumpTime >= 50 && state == eJump1)
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
			if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
				state = eRight;
			JumpCount = 0;
			isJump = false;
		}
	}
	if (isJump && GetTickCount64() - JumpTime >= 50 && state == eJump2)
	{
		JumpTime = GetTickCount64();
		if (JumpCount < 8)
		{
			player->pos.y -= 15;
			JumpCount++;
		}
		else
		{
			state = eIdle;
			if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
				state = eRight;
			JumpCount = 0;
			isJump = false;
		}
	}

	// 포션 먹기
	// 체력 포션
	if (InputManager::GetInstance()->getKey(0x31))
	{
		if (playerUI->hpPotionNum > 0)
		{
			if (nowHp < 100)
			{
				playerUI->hpPotionNum -= 1;
				nowHp += 20;
				if (nowHp > 100)
					nowHp = 100;
			}
			
		}
	}
	// 마나 포션
	if (InputManager::GetInstance()->getKey(0x32))
	{
		if (playerUI->mpPotionNum > 0)
		{
			if (nowMp < 100)
			{
				playerUI->mpPotionNum -= 1;
				nowMp += 50;
				if (nowMp > 100)
					nowMp = 100;
			}
		}
	}
	// 스매쉬
	if (InputManager::GetInstance()->getKey(0x53))
	{
		if (state == eAttack2 && !isSmash)
		{
			if (nowMp >= 30)
			{
				isSmash = true;
				nowMp -= 30;
				smash->setPos(player->pos.x + 20, player->pos.y + 50);
			}
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
			// 체력이 0 이하면?

		}
	default:
		break;
	}

	// 스매쉬 이동
	if (isSmash)
	{
		smash->animation("Resource/GameScene/smash",4, 100 );
		smash->pos.x += 10;
		if (smash->pos.x >= 2000)
		{
			isSmash = false;
			smash->pos.x = -100;
		}
	}

	if(SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
		playerBar->update();
	if (InputManager::GetInstance()->getKey(0x49)) 
	{
		playerUI->update();
		if (isUI) 
			isUI = false;
		
		else
			isUI = true;
		}
}

void Player::render()
{
	GraphicManager::GetInstance()->render(player);

	if (isSmash)
		GraphicManager::GetInstance()->render(smash);

	if (SceneManager::GetInstance()->sceneType == SceneManager::GetInstance()->eGame)
		playerBar->render(playerUI);


	if (isUI)
	{
		playerUI->render();
	}

}

void Player::release()
{
	GraphicManager::GetInstance()->release();
}

void Player::gravity(Tail *tail)
{
	// 플레이어는 바닥에 붙어 있는게 아니면 중력에 영향 받아야함 ㅇㅇ
	if (state != eJump1 && state != eJump2)
	{
		if (player->pos.y <= 560)
		{
			bool isCrush = false;
			GameObject* tempObject = new GameObject;
			tempObject->size = player->size;
			tempObject->pos = player->pos;
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
				player->pos.y += 10;
		}
	}

}