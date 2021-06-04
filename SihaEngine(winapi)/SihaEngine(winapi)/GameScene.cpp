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
	bg->loadTexture("Resource/village.png");
	bg->setPos(0, 0);
	bg->setSrcSize(1280, 1024);
	bg->setSize(1280, 1024);

	bg2 = new GameObject;
	bg2->loadTexture("Resource/village.png");
	bg2->setPos(-1280,0);
	bg2->setSrcSize(1280, 1024);
	bg2->setSize(1280, 1024);



	testObj = new GameObject;
	testObj->loadTexture("Resource/player1.png");
	testObj->setSize(150, 80);
	testObj->setSrcSize(150, 80);
	testObj->setPos(100, 100);

	// bgm 재생
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");

	/*Camera::GetInstance()->setTarget(testObj);*/
}

void GameScene::update()
{

	// 캐릭터 애니메이션
	testObj->animation("Resource/player", 3, 200);

	// 캐릭터 이동 예시
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


	//Camera::GetInstance()->update();
	render();
}

void GameScene::render()
{
	GraphicManager::GetInstance()->render(bg);
	GraphicManager::GetInstance()->render(bg2);
	GraphicManager::GetInstance()->render(testObj);


}
