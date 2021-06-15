#include "common.h"

void MonsterControl::init()
{
	spawnTime = 0.0f;
	spawnDelay = 10000;
}

void MonsterControl::update()
{
	if (GetTickCount() - spawnTime >= spawnDelay)
	{
		spawnTime = GetTickCount();
		spawnMonser();
	}

	// 몬스터들 업데이트
	for (int i = 0; i < monsters.size(); i++)
	{
		monsters[i]->update();
		if (monsters[i]->isDie)
		{
			monsters[i]->release();
			monsters.erase(monsters.begin() + i);
			break;
		}
	}

	// 충돌체크
	checkColiision();

	
}

void MonsterControl::render()
{
	for (int i = 0; i < monsters.size(); i++)
		monsters[i]->render();
}

void MonsterControl::release()
{

}

void MonsterControl::spawnMonser()
{
	// 현재는 슬라임만 스폰
	Monster* monster = new Monster;
	if (Player::GetInstance()->level%2)
	{
		monster->init(eSlime);
	}
	else
	{
		monster->init(eSkeleton);
	}

	monsters.push_back(monster);
}

void MonsterControl::checkColiision()
{
	// 공격 충돌용 오브젝트
	GameObject* tempPlayer = new GameObject;
	tempPlayer->pos = Player::GetInstance()->player->pos;
	tempPlayer->size = Player::GetInstance()->player->size;
	tempPlayer->size.cx += 50;
	for (int i = 0; i < monsters.size(); i++)
	{
		// 몸통 충돌
		if(CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, monsters[i]))
		{
			// 플레이어가 상태에 따른 변화
			switch (Player::GetInstance()->getPlayerState())
			{
			case eRight:
				monsters[i]->attack();
				break;
			default:
				break;
			}
		}
		// 공격 충돌
		if (CollisionManager::GetInstance()->RectCollisionCheck(tempPlayer, monsters[i]))
		{
			// 플레이어가 상태에 따른 변화
			switch (Player::GetInstance()->getPlayerState())
			{
			case eAttack1:
				monsters[i]->attacked();
				break;
			case eAttack2:
				monsters[i]->attacked();
				break;
			default:
				break;
			}
		}
		// 스매시 충돌
		if (CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->smash, monsters[i]))
		{

			monsters[i]->smashAttacked();

		}
	}
}