#pragma once

#include "common.h"

class Scene
{
public:
	Scene();
	~Scene();

	// virtual �� �̿��ؼ� ���� scene ����
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void release();

	// objectManager ���� <- scene ���� ������Ʈ ����
	ObjectManager obj;
};

