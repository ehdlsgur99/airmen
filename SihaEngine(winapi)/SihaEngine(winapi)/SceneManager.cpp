#include "common.h"

SceneManager::SceneManager()
{
	// Scene 을 초기화
	scene = NULL;
}

SceneManager::~SceneManager()
{

}

void SceneManager::SceneChange(int WhatScene)
{
	// 이전에 Scene이 있을 경우
	// 삭제후 제거
	if (scene)
	{
		scene->release();
		delete scene;
	}

	// Switch 로 내가 원하는 Scene 을 찾음
	switch (WhatScene)
	{
	case eTest:
		scene = new TestScene;
		break;
	case eGame:
		scene = new GameScene;

		break;
	/*case eIntro:
		scene = new IntroScene;
		break;
	case eGame:
		scene = new GScene;
		break;*/

	}

	// 새로 만든 Scene이 있다면 초기화 진행
	if (scene)
	{
		scene->init();
	}
}
