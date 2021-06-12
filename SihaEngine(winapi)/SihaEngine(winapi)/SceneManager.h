#pragma once
/*
	Scene ���� Ŭ����
*/

#include "common.h"

class Scene;
class SceneManager : public CSingleton<SceneManager>
{
public:
	// Scene ������ enum ���� ����
	enum eType
	{
		eIntro = 0,
		eGame,
		eTest,
		eVillage
	};
public:
	SceneManager();
	~SceneManager();

public:
	// Scene �� ���� �Ѵ�.
	Scene* scene;
	eType sceneType;
	// Scene �� ��ü �Ѵ�.
	void SceneChange(int WhatScene);
};

