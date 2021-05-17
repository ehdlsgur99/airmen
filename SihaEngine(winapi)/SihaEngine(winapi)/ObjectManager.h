#pragma once

/*
	������Ʈ ���� Ŭ����
*/

#include "common.h"

class GameObject;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
public:
	// ������Ʈ�� ������ ������Ʈ ���Ϳ�, UI ����
	std::vector<GameObject*> ObjectVector, UiVector;

	// ������Ʈ �߰� �޼���
	void addObject(GameObject* obj);

	// Ui �߰� �޼���
	void addUi(GameObject* obj);

	// ��� ���� ������Ʈ ���� �޼���
	void release();

	// ȭ���� ���ڰ� ��ŭ �̵�ȭ�� �޼���
	// ���� : ���� �߸ŷ� �ٸ� ��ü�� �̵�
	// ���� �����ؾ���
	void cameraMove(int x, int y);
};

