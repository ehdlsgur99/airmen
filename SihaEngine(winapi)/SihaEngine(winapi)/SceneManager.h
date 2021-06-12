#pragma once
/*
	Scene 관리 클래스
*/

#include "common.h"

class Scene;
class SceneManager : public CSingleton<SceneManager>
{
public:
	// Scene 종류를 enum 으로 선언
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
	// Scene 을 선언 한다.
	Scene* scene;
	eType sceneType;
	// Scene 을 교체 한다.
	void SceneChange(int WhatScene);
};

