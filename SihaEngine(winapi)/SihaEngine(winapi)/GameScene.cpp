#include "common.h"


GameScene::GameScene()
{

}

GameScene::~GameScene()
{
}

void GameScene::init()
{
	gameBg = new GameBG;
	gameBg->init();

	testObj = new GameObject;
	testObj->loadTexture("Resource/GameScene/Player/adventurer-run-00.png");
	testObj->setSize(200, 148);
	testObj->setSrcSize(50, 37);
	testObj->setPos(100, 600);

	// bgm 재생
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");

	/*Camera::GetInstance()->setTarget(testObj);*/
}

void GameScene::update()
{

	gameBg->update();

	// 캐릭터 애니메이션
	testObj->animation("Resource/GameScene/Player/adventurer-run-0", 5, 200);



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
	gameBg->render();
	GraphicManager::GetInstance()->render(testObj);


}
