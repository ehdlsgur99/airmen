#include "common.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

bool CollisionManager::RectCollisionCheck(GameObject* obj1, GameObject* obj2)
{
	// 체크할 사각형 2개 선언
	RECT rect1;
	RECT rect2;

	// 사각형의 왼쪽, 오른쪽, 위, 아래의 값을 지정해준다.
	rect1.left = obj1->getPos().x - obj1->getSize().cx / 2;
	rect1.right = obj1->getPos().x + obj1->getSize().cx / 2;
	rect1.top = obj1->getPos().y - obj1->getSize().cy / 2;
	rect1.bottom = obj1->getPos().y + obj1->getSize().cy / 2;

	rect2.left = obj2->getPos().x - obj2->getSize().cx / 2;
	rect2.right = obj2->getPos().x + obj2->getSize().cx / 2;
	rect2.top = obj2->getPos().y - obj2->getSize().cy / 2;
	rect2.bottom = obj2->getPos().y + obj2->getSize().cy / 2;

	// 그리고 체크이후
	if (rect1.left < rect2.right &&
		rect1.top < rect2.bottom &&
		rect1.right > rect2.left &&
		rect1.bottom > rect2.top)
	{
		// 충돌 일시 true를 리턴
		return true;
	}

	// 충돌이 아닐시 false 리턴
	return false;

}

bool CollisionManager::CircleCollisionCheck(float x1, float y1, float x2, float y2, float size)
{
	// 점과 점사이의 거리, 원의 방정식을 이용한다.

	if ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) <= size * size)
	{
		// 충돌 일시 true를 리턴
		return true;
	}

	// 충돌이 아닐시 false 리턴
	return false;
}