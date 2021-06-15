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

	// ���͵� ������Ʈ
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

	// �浹üũ
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
	// ����� �����Ӹ� ����
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
	// ���� �浹�� ������Ʈ
	GameObject* tempPlayer = new GameObject;
	tempPlayer->pos = Player::GetInstance()->player->pos;
	tempPlayer->size = Player::GetInstance()->player->size;
	tempPlayer->size.cx += 50;
	for (int i = 0; i < monsters.size(); i++)
	{
		// ���� �浹
		if(CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, monsters[i]))
		{
			// �÷��̾ ���¿� ���� ��ȭ
			switch (Player::GetInstance()->getPlayerState())
			{
			case eRight:
				monsters[i]->attack();
				break;
			default:
				break;
			}
		}
		// ���� �浹
		if (CollisionManager::GetInstance()->RectCollisionCheck(tempPlayer, monsters[i]))
		{
			// �÷��̾ ���¿� ���� ��ȭ
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
		// ���Ž� �浹
		if (CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->smash, monsters[i]))
		{

			monsters[i]->smashAttacked();

		}
	}
}