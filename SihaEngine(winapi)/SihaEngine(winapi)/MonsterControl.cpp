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
	monster->init(eSlime);
	monsters.push_back(monster);
}

void MonsterControl::checkColiision()
{
	for (int i = 0; i < monsters.size(); i++)
	{
		// �浹
		if(CollisionManager::GetInstance()->RectCollisionCheck(Player::GetInstance()->player, monsters[i]))
		{
			// �÷��̾ ���¿� ���� ��ȭ
			switch (Player::GetInstance()->getPlayerState())
			{
			case eRight:
				monsters[i]->attack();
				break;
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
	}
}