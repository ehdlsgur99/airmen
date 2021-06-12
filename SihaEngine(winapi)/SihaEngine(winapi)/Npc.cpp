#include "common.h"

Npc::Npc()
{

}

Npc::~Npc()
{

}

void Npc::init()
{
	npc[0] = new GameObject;
	npc[0]->loadTexture("Resource/npc/grocer/idle/oldman-idle-1.png");
	npc[0]->setSrcSize(34, 42);
	npc[0]->setSize(102,126);
	npc[0]->setPos(2400, 635);

	npc[1] = new GameObject;
	npc[1]->loadTexture("Resource/npc/men/idle/NPC1.png");
	npc[1]->setSrcSize(40, 47);
	npc[1]->setSize(120, 141);
	npc[1]->setPos(330, 635);

	npc[2] = new GameObject;
	npc[2]->loadTexture("Resource/npc/porter/idle/hat-man-idle-1.png");
	npc[2]->setSrcSize(39, 52);
	npc[2]->setSize(117, 156);
	npc[2]->setPos(3100, 620);

	npc[3] = new GameObject;
	npc[3]->loadTexture("Resource/npc/woman/idle/woman-idle-1.png");
	npc[3]->setSrcSize(37, 46);
	npc[3]->setSize(111, 138);
	npc[3]->setPos(800, 635);
	ObjectManager::GetInstance()->addObject(npc[0]);
	ObjectManager::GetInstance()->addObject(npc[1]);
	ObjectManager::GetInstance()->addObject(npc[2]);
	ObjectManager::GetInstance()->addObject(npc[3]);
}

void Npc::update()
{
	// 캐릭터 애니메이션

	npc[0]->animation("Resource/npc/grocer/idle/oldman-idle-", 8, 200);
	npc[1]->animation("Resource/npc/men/idle/NPC", 5, 200);
	npc[2]->animation("Resource/npc/porter/idle/hat-man-idle-", 4, 200);
	npc[3]->animation("Resource/npc/woman/idle/woman-idle-", 7, 200);

	
}

void Npc::render()
{
	GraphicManager::GetInstance()->render(npc[0]);
	GraphicManager::GetInstance()->render(npc[1]);
	GraphicManager::GetInstance()->render(npc[2]);
	GraphicManager::GetInstance()->render(npc[3]);
}

void Npc::release()
{
	GraphicManager::GetInstance()->release();
}
