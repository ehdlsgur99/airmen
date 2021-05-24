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
		delete scene;
	}

	// Switch �� ���� ���ϴ� Scene �� ã��
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

	// ���� ���� Scene�� �ִٸ� �ʱ�ȭ ����
	if (scene)
	{
		scene->init();
	}
}
