#pragma once

/*
	오브젝트 관리 클래스
*/

#include "common.h"

class GameObject;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
public:
	// 오브젝트를 관리할 오브젝트 벡터와, UI 벡터
	std::vector<GameObject*> ObjectVector, UiVector;

	// 오브젝트 추가 메서드
	void addObject(GameObject* obj);

	// Ui 추가 메서드
	void addUi(GameObject* obj);

	// 모든 게임 오브젝트 해제 메서드
	void release();

	// 화면을 인자값 만큼 이동화는 메서드
	// 주의 : 현재 야매로 다른 객체가 이동
	// 차후 수정해야함
	void cameraMove(int x, int y);
};

