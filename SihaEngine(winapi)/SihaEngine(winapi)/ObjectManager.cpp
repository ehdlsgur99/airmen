#include "common.h"

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::addObject(GameObject* obj)
{
	// ������Ʈ ���Ϳ� ���� ������Ʈ�� �ִ´�
	ObjectVector.push_back(obj);
}

void ObjectManager::addUi(GameObject* obj)
{
	// Ui ���Ϳ� ���� ������Ʈ�� �ִ´�
	UiVector.push_back(obj);
}

void ObjectManager::release()
{
	 // ������Ʈ ���Ϳ�, Ui ������ ũ�⸸ŭ for���� ������ ����
	for (int i = 0; i < ObjectVector.size(); i++)
	{
		delete ObjectVector[i];
	}
	for (int i = 0; i < UiVector.size(); i++)
	{
		delete UiVector[i];
	}

	// ���� clear.
	ObjectVector.clear();
	UiVector.clear();
}

void ObjectManager::cameraMove(int x, int y)
{
	// ������Ʈ�� ũ�⸸ŭ for���� ����
	for (int i = 0; i < ObjectVector.size(); i++)
	{
		// ������Ʈ ���� ��, Ui�� �ƴ� ������Ʈ���� ���� �̵���Ų��.
		// �׷� Ui�� ������ �ְ� �ٸ� ������Ʈ���� ���� ���ڰ� x, y��ŭ �����δ�.
		ObjectVector[i]->setPos(ObjectVector[i]->getPos().x - x, ObjectVector[i]->getPos().y - y);
	}
}