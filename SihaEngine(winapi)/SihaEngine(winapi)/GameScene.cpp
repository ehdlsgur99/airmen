#include "common.h"


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	bg = new GameObject;
	bg->loadTexture("Resource/bg2.png");
	bg->setPos(0, 0);
	bg->setSize(1000, 800);
	bg->setSrcSize(1000, 800);

	testObj = new GameObject;
	testObj->loadTexture("Resource/player1.png");
	testObj->setSize(150, 80);
	testObj->setPos(100, 100);

	// bgm ���
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void GameScene::update()
{

	// ĳ���� �ִϸ��̼�
	testObj->animation("Resource/player", 3, 200);

	// ĳ���� �̵� ����
	if (InputManager::GetInstance()->getKey(VK_LEFT))
	{
		testObj->pos.x -= 1;
	}
	if (InputManager::GetInstance()->getKey(VK_RIGHT))
	{
		testObj->pos.x += 1;
	}
	if (InputManager::GetInstance()->getKey(VK_UP))
	{
		testObj->pos.y -= 1;
	}
	if (InputManager::GetInstance()->getKey(VK_DOWN))
	{
		testObj->pos.y += 1;
	}



	render();
}

void GameScene::render()
{
	GraphicManager::GetInstance()->render(bg);
	GraphicManager::GetInstance()->render(testObj);


}
