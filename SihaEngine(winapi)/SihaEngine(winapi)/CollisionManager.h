#pragma once

#include "common.h"

/*
	충돌체크 클래스
*/

class CollisionManager : public CSingleton<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();

	// 사각형 충돌
	bool RectCollisionCheck(GameObject* obj1, GameObject* obj2);
	bool RectCollisionCheck2(GameObject* obj1, GameObject* obj2,int range);

	// 원 충돌
	bool CircleCollisionCheck(float x1, float y1, float x2, float y2, float size);
};

