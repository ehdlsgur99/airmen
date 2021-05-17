#pragma once

#include "common.h"

class Scene
{
public:
	Scene();
	~Scene();

	// virtual 를 이용해서 차후 scene 구성
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void release();

	// objectManager 생성 <- scene 내의 오브젝트 관리
	ObjectManager obj;
};

