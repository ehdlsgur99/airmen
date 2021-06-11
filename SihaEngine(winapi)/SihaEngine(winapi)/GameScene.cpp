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

	isChange = false;

	Player::GetInstance()->init();

	// bgm ���
	SoundManager::GetInstance()->PlayBg("Resource/bg.mp3");

	//Camera::GetInstance()->setTarget(testObj);
}

void GameScene::update()
{

	gameBg->update();

	// ĳ���� �ִϸ��̼�
	Player::GetInstance()->update();

	//Camera::GetInstance()->update();
	if(!isChange)
		render();
}

void GameScene::render()
{
	gameBg->render();
	Player::GetInstance()->render();
}

void GameScene::release()
{
	isChange = true;
	delete gameBg;
}
