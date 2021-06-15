#include "common.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::addObject(GameObject* obj)
{
	// 오브젝트 벡터에 게임 오브젝트를 넣는다
	ObjectVector.push_back(obj);
}

void ObjectManager::addUi(GameObject* obj)
{
	// Ui 벡터에 게임 오브젝트를 넣는다
	UiVector.push_back(obj);
}

void ObjectManager::release()
{
	 // 오브젝트 벡터와, Ui 벡터의 크기만큼 for문을 돌려서 삭제
	for (int i = 0; i < ObjectVector.size(); i++)
	{
		delete ObjectVector[i];
	}
	for (int i = 0; i < UiVector.size(); i++)
	{
		delete UiVector[i];
	}

	// 벡터 clear.
	ObjectVector.clear();
	UiVector.clear();
}

void ObjectManager::cameraMove(int x, int y)
{
	// 오브젝트의 크기만큼 for문을 돌림
	for (int i = 0; i < ObjectVector.size(); i++)
	{
		// 오브젝트 벡터 즉, Ui가 아닌 오브젝트들을 전부 이동시킨다.
		// 그럼 Ui는 가만히 있고 다른 오브젝트들은 전부 인자값 x, y만큼 움직인다.
		ObjectVector[i]->setPos(ObjectVector[i]->getPos().x - x, ObjectVector[i]->getPos().y - y);
	}
}