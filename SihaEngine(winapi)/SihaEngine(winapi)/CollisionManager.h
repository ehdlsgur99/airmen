#pragma once

#include "common.h"

/*
	�浹üũ Ŭ����
*/

class CollisionManager : public CSingleton<CollisionManager>
{
public:
	CollisionManager();
	~CollisionManager();

	// �簢�� �浹
	bool RectCollisionCheck(GameObject* obj1, GameObject* obj2);
	bool RectCollisionCheck2(GameObject* obj1, GameObject* obj2,int range);

	// �� �浹
	bool CircleCollisionCheck(float x1, float y1, float x2, float y2, float size);
};

