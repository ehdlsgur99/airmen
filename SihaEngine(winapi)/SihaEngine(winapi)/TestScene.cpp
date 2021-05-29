#include "common.h"

TestScene::TestScene()
{

}

TestScene::~TestScene()
{
}

void TestScene::init()
{
	bg = new GameObject;
	bg->loadTexture("Resource/bg.png");
	bg->setPos(0,0 );
	bg->setSize(1000, 800);

	testObj = new GameObject;
	testObj->loadTexture("Resource/player1.png");
	testObj->setSize(150, 80);
	testObj->setPos(100, 100);

	// bgm ���
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");
}

void TestScene::update()
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

	 if (InputManager::GetInstance()->getKey(VK_SPACE))
	 {
		 SceneManager::GetInstance()->SceneChange(SceneManager::eGame);
		 return;
	 }


	render();
}

void TestScene::render()
{
	GraphicManager::GetInstance()->render(bg);
	GraphicManager::GetInstance()->render(testObj);


}
