#include "common.h"

SceneManager::SceneManager()
{
	// Scene �� �ʱ�ȭ
	scene = NULL;
}

SceneManager::~SceneManager()
{

}

void SceneManager::SceneChange(int WhatScene)
{
	// ������ Scene�� ���� ���
	// ������ ����
	if (scene)
	{
		scene->release();
		//delete scene;
	}

	// Switch �� ���� ���ϴ� Scene �� ã��
	switch (WhatScene)
	{
	case eIntro:
		scene = new IntroScene;
		scene->init();
		sceneType = eIntro;
		break;
	case eTest:
		scene = new TestScene;
		scene->init();
		sceneType = eTest;
		break;
	case eGame:
		scene = new GameScene;
		scene->init();
		sceneType = eGame;
		break;
	case eVillage:
		scene = new VillageScene;
		scene->init();
		sceneType = eVillage;
		break;
	/*case eIntro:
		scene = new IntroScene;
		break;
	case eGame:
		scene = new GScene;
		break;*/

	}

	// ���� ���� Scene�� �ִٸ� �ʱ�ȭ ����
	if (scene)
	{
		scene->init();
	}
}
