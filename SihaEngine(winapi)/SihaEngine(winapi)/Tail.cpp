#include "common.h"

void Tail::init()
{
	tails.clear();
	tailTime = GetTickCount();
}

void Tail::update()
{
	createTail();
}

void Tail::render()
{
	for (int i = 0; i < tails.size(); i++)
	{
		GraphicManager::GetInstance()->render(tails[i]);
	}
}

void Tail::release()
{

}

void Tail::createTail()
{
	
	// tail 农扁 抄荐 积己
	//int width = rand() % 600 + 200;
	//int height = rand() % 100 + 450;
	//tailTime = GetTickCount();

	// tail 积己
	GameObject* tempTail = new GameObject;
	tempTail->loadTexture("Resource/GameScene/tail.png");
	
	tempTail->setSize(400, 50);
	tempTail->setPos(800, 600);

	tails.push_back(tempTail);
	
}